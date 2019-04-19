//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef GAMERULES_H
#define GAMERULES_H
#ifdef _WIN32
#pragma once
#endif

// Debug history should be disabled in release builds
//#define DISABLE_DEBUG_HISTORY	

#ifdef CLIENT_DLL

	#include "c_baseentity.h"
	
	#define CGameRules C_GameRules
	#define CGameRulesProxy C_GameRulesProxy

#else
	
	#include "server/baseentity.h"
	#include "recipientfilter.h"

#endif

#include "igamesystem.h"
#include "gamerules_register.h"


//#include "items.h"
class CBaseCombatWeapon;
class CBaseCombatCharacter;
class CBasePlayer;
class CItem;
class CAmmoDef;
class CTacticalMissionManager;

extern ConVar sk_autoaim_mode;

// Autoaiming modes
enum
{
	AUTOAIM_NONE = 0,		// No autoaim at all.
	AUTOAIM_ON,				// Autoaim is on.
	AUTOAIM_ON_CONSOLE,		// Autoaim is on, including enhanced features for Console gaming (more assistance, etc)
};

// weapon respawning return codes
enum
{	
	GR_NONE = 0,
	
	GR_WEAPON_RESPAWN_YES,
	GR_WEAPON_RESPAWN_NO,
	
	GR_AMMO_RESPAWN_YES,
	GR_AMMO_RESPAWN_NO,
	
	GR_ITEM_RESPAWN_YES,
	GR_ITEM_RESPAWN_NO,

	GR_PLR_DROP_GUN_ALL,
	GR_PLR_DROP_GUN_ACTIVE,
	GR_PLR_DROP_GUN_NO,

	GR_PLR_DROP_AMMO_ALL,
	GR_PLR_DROP_AMMO_ACTIVE,
	GR_PLR_DROP_AMMO_NO,
};

// Player relationship return codes
enum
{
	GR_NOTTEAMMATE = 0,
	GR_TEAMMATE,
	GR_ENEMY,
	GR_ALLY,
	GR_NEUTRAL,
};


// This class has the data tables and gets the CGameRules data to the client.
class CGameRulesProxy : public CBaseEntity
{
public:
	DECLARE_CLASS( CGameRulesProxy, CBaseEntity );
	DECLARE_SERVERCLASS();

	CGameRulesProxy();
	~CGameRulesProxy();

	// UNDONE: Is this correct, Mike?
	// Don't carry these across a transition, they are recreated.
	virtual int	ObjectCaps( void ) { return BaseClass::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

	// ALWAYS transmit to all clients.
	virtual int UpdateTransmitState( void );

	// CGameRules chains its NetworkStateChanged calls to here, since this
	// is the actual entity that will send the data.
	static void NotifyNetworkStateChanged();

private:
	
	static CGameRulesProxy *s_pGameRulesProxy;
};


abstract_class CGameRules : public CAutoGameSystemPerFrame
{
public:
	DECLARE_CLASS_GAMEROOT( CGameRules, CAutoGameSystemPerFrame );

	/*0 - 0*/virtual char const *Name() { return "CGameRules"; }

	// Stuff shared between client and server.

	CGameRules(void);
	/*13 - 52*/virtual ~CGameRules( void );

	// Damage Queries - these need to be implemented by the various subclasses (single-player, multi-player, etc).
	// The queries represent queries against damage types and properties.
	/*17 - 68*/virtual bool	Damage_IsTimeBased( int iDmgType ) = 0;			// Damage types that are time-based.
	/*18 - 72*/virtual bool	Damage_ShouldGibCorpse( int iDmgType ) = 0;		// Damage types that gib the corpse.
	/*19 - 76*/virtual bool	Damage_ShowOnHUD( int iDmgType ) = 0;			// Damage types that have client HUD art.
	/*20 - 80*/virtual bool	Damage_NoPhysicsForce( int iDmgType ) = 0;		// Damage types that don't have to supply a physics force & position.
	/*21 - 84*/virtual bool	Damage_ShouldNotBleed( int iDmgType ) = 0;		// Damage types that don't make the player bleed.
	//Temp: These will go away once DamageTypes become enums.
	/*22 - 88*/virtual int		Damage_GetTimeBased( void ) = 0;				// Actual bit-fields.
	/*23 - 92*/virtual int		Damage_GetShouldGibCorpse( void ) = 0;
	/*24 - 96*/virtual int		Damage_GetShowOnHud( void ) = 0;
	/*25 - 100*/virtual int		Damage_GetNoPhysicsForce( void )= 0;
	/*26 - 104*/virtual int		Damage_GetShouldNotBleed( void ) = 0;

// Ammo Definitions
	//CAmmoDef* GetAmmoDef();

	/*27 - 108*/virtual bool SwitchToNextBestWeapon( CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon ); // Switch to the next best weapon
	/*28 - 112*/virtual CBaseCombatWeapon *GetNextBestWeapon( CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon ); // I can't use this weapon anymore, get me the next best one.
	/*29 - 116*/virtual bool ShouldCollide( int collisionGroup0, int collisionGroup1 );

	/*30 - 120*/virtual int DefaultFOV( void ) { return 90; }

	// This function is here for our CNetworkVars.
	inline void NetworkStateChanged()
	{
		// Forward the call to the entity that will send the data.
		CGameRulesProxy::NotifyNetworkStateChanged();
	}

	inline void NetworkStateChanged( void *pVar )
	{
		// Forward the call to the entity that will send the data.
		CGameRulesProxy::NotifyNetworkStateChanged();
	}

	// Get the view vectors for this mod.
	/*31 - 124*/virtual const CViewVectors* GetViewVectors() const;

// Damage rules for ammo types
	/*32 - 128*/virtual float GetAmmoDamage( CBaseEntity *pAttacker, CBaseEntity *pVictim, int nAmmoType );
	/*33 - 132*/virtual float GetDamageMultiplier( void ) { return 1.0f; }

// Functions to verify the single/multiplayer status of a game
	/*34 - 136*/virtual bool IsMultiplayer( void ) = 0;// is this a multiplayer game? (either coop or deathmatch)

	/*35 - 140*/virtual const unsigned char *GetEncryptionKey() { return NULL; }

	/*36 - 144*/virtual bool InRoundRestart( void ) { return false; }

	//Allow thirdperson camera.
	/*37 - 148*/virtual bool AllowThirdPersonCamera( void ) { return false; }

	/*38 - 152*/virtual void ClientCommandKeyValues( edict_t *pEntity, KeyValues *pKeyValues ) {}

	/*
	doesn't exist on vmt

	// IsConnectedUserInfoChangeAllowed allows the clients to change
	// cvars with the FCVAR_NOT_CONNECTED rule if it returns true
	virtual bool IsConnectedUserInfoChangeAllowed( CBasePlayer *pPlayer )
	{ 
		return true; 
	}

	*/

#ifdef CLIENT_DLL

	virtual bool IsBonusChallengeTimeBased( void );

	virtual bool AllowMapParticleEffect( const char *pszParticleEffect ) { return true; }

	virtual bool AllowWeatherParticles( void ) { return true; }

	virtual bool AllowMapVisionFilterShaders( void ) { return false; }
	virtual const char* TranslateEffectForVisionFilter( const char *pchEffectType, const char *pchEffectName ) { return pchEffectName; }

	virtual bool IsLocalPlayer( int nEntIndex );

	virtual void ModifySentChat( char *pBuf, int iBufSize ) { return; }

	virtual bool ShouldWarnOfAbandonOnQuit() { return false; }
	
#else
	/*
	doesn't exist on vmt
	virtual void Status( void (*print) (const char *fmt, ...) ) {}
	*/
	/*39 - 156*/virtual void GetTaggedConVarList( KeyValues *pCvarTagList ) {}

	// NVNT see if the client of the player entered is using a haptic device.
	/*40 - 160*/virtual void CheckHaptics(CBasePlayer* pPlayer);

// CBaseEntity overrides.
public:

// Setup
	
	// Called when game rules are destroyed by CWorld
	/*41 - 164*/virtual void LevelShutdown( void ) { return; };

	/*42 - 168*/virtual void Precache( void ) { return; };

	/*43 - 172*/virtual void RefreshSkillData( bool forceUpdate );// fill skill data struct with proper values
	
	/*
	doesn't exist on vmt
	// Called each frame. This just forwards the call to Think().
	virtual void FrameUpdatePostEntityThink();
	*/

	/*44 - 176*/virtual void Think( void ) = 0;// GR_Think - runs every server frame, should handle any timer tasks, periodic events, etc.
	/*45 - 180*/virtual bool IsAllowedToSpawn( CBaseEntity *pEntity ) = 0;  // Can this item spawn (eg NPCs don't spawn in deathmatch).

	// Called at the end of GameFrame (i.e. after all game logic has run this frame)
	/*46 - 184*/virtual void EndGameFrame( void );

	/*47 - 188*/virtual bool IsSkillLevel( int iLevel ) { return GetSkillLevel() == iLevel; }
	/*48 - 192*/virtual int	GetSkillLevel() { return 0; }
	/*49 - 196*/virtual void OnSkillLevelChanged( int iNewLevel ) {};
	/*50 - 200*/virtual void SetSkillLevel( int iLevel )
	{
	}

	/*51 - 204*/virtual bool FAllowFlashlight( void ) = 0;// Are players allowed to switch on their flashlight?
	/*52 - 208*/virtual bool FShouldSwitchWeapon( CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon ) = 0;// should the player switch to this weapon?

// Functions to verify the single/multiplayer status of a game
	/*53 - 212*/virtual bool IsDeathmatch( void ) = 0;//is this a deathmatch game?
	/*54 - 216*/virtual bool IsTeamplay( void ) { return FALSE; };// is this deathmatch game being played with team rules?
	/*55 - 220*/virtual bool IsCoOp( void ) = 0;// is this a coop game?
	/*56 - 224*/virtual const char *GetGameDescription( void ) { return "Half-Life 2"; }  // this is the game name that gets seen in the server browser
	
// Client connection/disconnection
	/*57 - 228*/virtual bool ClientConnected( edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen ) = 0;// a client just connected to the server (player hasn't spawned yet)
	/*58 - 232*/virtual void InitHUD( CBasePlayer *pl ) = 0;		// the client dll is ready for updating
	/*59 - 236*/virtual void ClientDisconnected( edict_t *pClient ) = 0;// a client just disconnected from the server
	
// Client damage rules
	/*60 - 240*/virtual float FlPlayerFallDamage( CBasePlayer *pPlayer ) = 0;// this client just hit the ground after a fall. How much damage?
	/*61 - 244*/virtual bool  FPlayerCanTakeDamage( CBasePlayer *pPlayer, CBaseEntity *pAttacker, const CTakeDamageInfo &info ) {return TRUE;};// can this player take damage from this attacker?
	/*62 - 248*/virtual bool ShouldAutoAim( CBasePlayer *pPlayer, edict_t *target ) { return TRUE; }
	/*63 - 252*/virtual float GetAutoAimScale( CBasePlayer *pPlayer ) { return 1.0f; }
	/*64 - 256*/virtual int	GetAutoAimMode()	{ return AUTOAIM_ON; }

	/*65 - 260*/virtual bool ShouldUseRobustRadiusDamage(CBaseEntity *pEntity) { return false; }
	/*66 - 264*/virtual void  RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrc, float flRadius, int iClassIgnore, CBaseEntity *pEntityIgnore );
	// Let the game rules specify if fall death should fade screen to black
	/*67 - 268*/virtual bool  FlPlayerFallDeathDoesScreenFade( CBasePlayer *pl ) { return TRUE; }

	/*68 - 272*/virtual bool AllowDamage( CBaseEntity *pVictim, const CTakeDamageInfo &info ) = 0;


// Client spawn/respawn control
	/*69 - 276*/virtual void PlayerSpawn( CBasePlayer *pPlayer ) = 0;// called by CBasePlayer::Spawn just before releasing player into the game
	/*70 - 280*/virtual void PlayerThink( CBasePlayer *pPlayer ) = 0; // called by CBasePlayer::PreThink every frame, before physics are run and after keys are accepted
	/*71 - 284*/virtual bool FPlayerCanRespawn( CBasePlayer *pPlayer ) = 0;// is this player allowed to respawn now?
	/*72 - 288*/virtual float FlPlayerSpawnTime( CBasePlayer *pPlayer ) = 0;// When in the future will this player be able to spawn?
	/*73 - 292*/virtual CBaseEntity *GetPlayerSpawnSpot( CBasePlayer *pPlayer );// Place this player on their spawnspot and face them the proper direction.
	/*74 - 296*/virtual bool IsSpawnPointValid( CBaseEntity *pSpot, CBasePlayer *pPlayer );

	/*75 - 300*/virtual bool AllowAutoTargetCrosshair( void ) { return TRUE; };
	/*76 - 304*/virtual bool ClientCommand( CBaseEntity *pEdict, const CCommand &args );  // handles the user commands;  returns TRUE if command handled properly
	/*77 - 308*/virtual void ClientSettingsChanged( CBasePlayer *pPlayer );		 // the player has changed cvars

// Client kills/scoring
	/*78 - 312*/virtual int IPointsForKill( CBasePlayer *pAttacker, CBasePlayer *pKilled ) = 0;// how many points do I award whoever kills this player?
	/*79 - 316*/virtual void PlayerKilled( CBasePlayer *pVictim, const CTakeDamageInfo &info ) = 0;// Called each time a player dies
	/*80 - 320*/virtual void DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info )=  0;// Call this from within a GameRules class to report an obituary.
	/*81 - 324*/virtual const char *GetDamageCustomString( const CTakeDamageInfo &info ) { return NULL; }

// Weapon Damage
	// Determines how much damage Player's attacks inflict, based on skill level.
	/*82 - 328*/virtual float AdjustPlayerDamageInflicted( float damage ) { return damage; }
	/*83 - 332*/virtual void  AdjustPlayerDamageTaken( CTakeDamageInfo *pInfo ) {}; // Base class does nothing.

// Weapon retrieval
	/*84 - 336*/virtual bool CanHavePlayerItem( CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon );// The player is touching an CBaseCombatWeapon, do I give it to him?

// Weapon spawn/respawn control
	/*85 - 340*/virtual int WeaponShouldRespawn( CBaseCombatWeapon *pWeapon ) = 0;// should this weapon respawn?
	/*86 - 344*/virtual float FlWeaponRespawnTime( CBaseCombatWeapon *pWeapon ) = 0;// when may this weapon respawn?
	/*87 - 348*/virtual float FlWeaponTryRespawn( CBaseCombatWeapon *pWeapon ) = 0; // can i respawn now,  and if not, when should i try again?
	/*88 - 352*/virtual Vector VecWeaponRespawnSpot( CBaseCombatWeapon *pWeapon ) = 0;// where in the world should this weapon respawn?

// Item retrieval
	/*89 - 356*/virtual bool CanHaveItem( CBasePlayer *pPlayer, CItem *pItem ) = 0;// is this player allowed to take this item?
	/*90 - 360*/virtual void PlayerGotItem( CBasePlayer *pPlayer, CItem *pItem ) = 0;// call each time a player picks up an item (battery, healthkit)

// Item spawn/respawn control
	/*91 - 364*/virtual int ItemShouldRespawn( CItem *pItem ) = 0;// Should this item respawn?
	/*92 - 368*/virtual float FlItemRespawnTime( CItem *pItem ) = 0;// when may this item respawn?
	/*93 - 372*/virtual Vector VecItemRespawnSpot( CItem *pItem ) = 0;// where in the world should this item respawn?
	/*94 - 376*/virtual QAngle VecItemRespawnAngles( CItem *pItem ) = 0;// what angles should this item use when respawing?

// Ammo retrieval
	/*95 - 380*/virtual bool CanHaveAmmo( CBaseCombatCharacter *pPlayer, int iAmmoIndex ); // can this player take more of this ammo?
	/*96 - 384*/virtual bool CanHaveAmmo( CBaseCombatCharacter *pPlayer, const char *szName );
	/*97 - 388*/virtual void PlayerGotAmmo( CBaseCombatCharacter *pPlayer, char *szName, int iCount ) = 0;// called each time a player picks up some ammo in the world
	/*98 - 392*/virtual float GetAmmoQuantityScale( int iAmmoIndex ) { return 1.0f; }

// AI Definitions
	/*99 - 396*/virtual void			InitDefaultAIRelationships( void ) { return; }
	/*100 - 400*/virtual const char*		AIClassText(int classType) { return NULL; }

// Healthcharger respawn control
	/*101 - 404*/virtual float FlHealthChargerRechargeTime( void ) = 0;// how long until a depleted HealthCharger recharges itself?
	/*102 - 408*/virtual float FlHEVChargerRechargeTime( void ) { return 0; }// how long until a depleted HealthCharger recharges itself?

// What happens to a dead player's weapons
	/*103 - 412*/virtual int DeadPlayerWeapons( CBasePlayer *pPlayer ) = 0;// what do I do with a player's weapons when he's killed?

// What happens to a dead player's ammo	
	/*104 - 416*/virtual int DeadPlayerAmmo( CBasePlayer *pPlayer ) = 0;// Do I drop ammo when the player dies? How much?

// Teamplay stuff
	/*105 - 420*/virtual const char *GetTeamID( CBaseEntity *pEntity ) = 0;// what team is this entity on?
	/*106 - 424*/virtual int PlayerRelationship( CBaseEntity *pPlayer, CBaseEntity *pTarget ) = 0;// What is the player's relationship with this entity?
	/*107 - 428*/virtual bool PlayerCanHearChat( CBasePlayer *pListener, CBasePlayer *pSpeaker ) = 0;
	/*108 - 432*/virtual void CheckChatText( CBasePlayer *pPlayer, char *pText ) { return; }

	/*109 - 436*/virtual int GetTeamIndex( const char *pTeamName ) { return -1; }
	/*110 - 440*/virtual const char *GetIndexedTeamName( int teamIndex ) { return ""; }
	/*111 - 444*/virtual bool IsValidTeam( const char *pTeamName ) { return true; }
	/*112 - 448*/virtual void ChangePlayerTeam( CBasePlayer *pPlayer, const char *pTeamName, bool bKill, bool bGib ) {}
	/*113 - 452*/virtual const char *SetDefaultPlayerTeam( CBasePlayer *pPlayer ) { return ""; }
	/*114 - 456*/virtual void UpdateClientData( CBasePlayer *pPlayer ) { };

// Sounds
	/*115 - 460*/virtual bool PlayTextureSounds( void ) { return TRUE; }
	/*116 - 464*/virtual bool PlayFootstepSounds( CBasePlayer *pl ) { return TRUE; }

// NPCs
	/*117 - 468*/virtual bool FAllowNPCs( void ) = 0;//are NPCs allowed

	// Immediately end a multiplayer game
	/*118 - 472*/virtual void EndMultiplayerGame( void ) {}
				    
	// trace line rules
	/*119 - 476*/virtual float WeaponTraceEntity( CBaseEntity *pEntity, const Vector &vecStart, const Vector &vecEnd, unsigned int mask, trace_t *ptr );

	// Setup g_pPlayerResource (some mods use a different entity type here).
	/*120 - 480*/virtual void CreateStandardEntities();

	// Team name, etc shown in chat and dedicated server console
	/*121 - 484*/virtual const char *GetChatPrefix( bool bTeamOnly, CBasePlayer *pPlayer );

	// Location name shown in chat
	/*122 - 488*/virtual const char *GetChatLocation( bool bTeamOnly, CBasePlayer *pPlayer ) { return NULL; }

	// VGUI format string for chat, if desired
	/*123 - 492*/virtual const char *GetChatFormat( bool bTeamOnly, CBasePlayer *pPlayer ) { return NULL; }

	// Whether props that are on fire should get a DLIGHT.
	/*124 - 496*/virtual bool ShouldBurningPropsEmitLight() { return false; }

	/*125 - 500*/virtual bool CanEntityBeUsePushed( CBaseEntity *pEnt ) { return true; }

	/*126 - 504*/virtual void CreateCustomNetworkStringTables( void ) { }

	// Game Achievements (server version)
	/*127 - 508*/virtual void MarkAchievement ( IRecipientFilter& filter, char const *pchAchievementName );

	/*128 - 512*/virtual void ResetMapCycleTimeStamp( void ){ return; }

	/*129 - 516*/virtual void OnNavMeshLoad( void ) { return; }

	// game-specific factories
	/*130 - 520*/virtual CTacticalMissionManager *TacticalMissionManagerFactory( void );

	/*131 - 524*/virtual void ProcessVerboseLogOutput( void ){}

#endif

	/*132 - 528*/virtual const char *GetGameTypeName( void ){ return NULL; }
	/*133 - 532*/virtual int GetGameType( void ){ return 0; }

	/*134 - 536*/virtual bool ShouldDrawHeadLabels(){ return true; }

	/*135 - 540*/virtual void ClientSpawned( edict_t * pPlayer ) { return; }

	/*136 - 544*/virtual void OnFileReceived( const char * fileName, unsigned int transferID ) { return; }

	/*137 - 548*/virtual bool IsHolidayActive( /*EHoliday*/ int eHoliday ) const { return false; }

	/*
	doesn't exist on vmt
	virtual bool IsManualMapChangeOkay( const char **pszReason ){ return true; }
	*/
#ifndef CLIENT_DLL
private:
	float m_flNextVerboseLogOutput;
#endif // CLIENT_DLL
};

#endif // GAMERULES_H