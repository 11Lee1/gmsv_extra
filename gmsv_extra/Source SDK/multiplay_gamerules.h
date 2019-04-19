//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef MULTIPLAY_GAMERULES_H
#define MULTIPLAY_GAMERULES_H
#ifdef _WIN32
#pragma once
#endif


#include "gamerules.h"

#ifdef CLIENT_DLL

#define CMultiplayRules C_MultiplayRules

#else

extern ConVar mp_restartgame;
extern ConVar mp_restartgame_immediate;
extern ConVar mp_waitingforplayers_time;
extern ConVar mp_waitingforplayers_restart;
extern ConVar mp_waitingforplayers_cancel;
extern ConVar mp_clan_readyrestart;
extern ConVar mp_clan_ready_signal;
extern ConVar nextlevel;
extern INetworkStringTable *g_pStringTableServerMapCycle;

#if defined ( TF_DLL ) || defined ( TF_CLIENT_DLL )
extern INetworkStringTable *g_pStringTableServerPopFiles;
extern INetworkStringTable *g_pStringTableServerMapCycleMvM;
#endif

#define VOICE_COMMAND_MAX_SUBTITLE_DIST	1900

class CBaseMultiplayerPlayer;

#endif

extern ConVar mp_show_voice_icons;

#define MAX_SPEAK_CONCEPT_LEN 64
#define MAX_VOICE_COMMAND_SUBTITLE	256

typedef struct
{
#ifndef CLIENT_DLL
	// concept to speak
	int	 m_iConcept;

	// play subtitle?
	bool m_bShowSubtitle;
	bool m_bDistanceBasedSubtitle;

	char m_szGestureActivity[64];

#else
	// localizable subtitle
	char m_szSubtitle[MAX_VOICE_COMMAND_SUBTITLE];

	// localizable string for menu
	char m_szMenuLabel[MAX_VOICE_COMMAND_SUBTITLE];
#endif

} VoiceCommandMenuItem_t;

extern ConVar mp_timelimit;

//=========================================================
// CMultiplayRules - rules for the basic half life multiplayer
// competition
//=========================================================
class CMultiplayRules : public CGameRules
{
public:
	DECLARE_CLASS(CMultiplayRules, CGameRules);

	// Functions to verify the single/multiplayer status of a game
	/*34 - 136*/virtual bool	IsMultiplayer(void);

	/*1 - 4*/virtual	bool	Init();

	// Damage query implementations.
	/*17 - 68*/virtual bool	Damage_IsTimeBased(int iDmgType);			// Damage types that are time-based.
	/*18 - 72*/virtual bool	Damage_ShouldGibCorpse(int iDmgType);		// Damage types that gib the corpse.
	/*19 - 76*/virtual bool	Damage_ShowOnHUD(int iDmgType);				// Damage types that have client HUD art.
	/*20 - 80*/virtual bool	Damage_NoPhysicsForce(int iDmgType);		// Damage types that don't have to supply a physics force & position.
	/*21 - 84*/virtual bool	Damage_ShouldNotBleed(int iDmgType);			// Damage types that don't make the player bleed.
	// TEMP: These will go away once DamageTypes become enums.
	/*22 - 88*/virtual int		Damage_GetTimeBased(void);
	/*23 - 92*/virtual int		Damage_GetShouldGibCorpse(void);
	/*24 - 96*/virtual int		Damage_GetShowOnHud(void);
	/*25 - 100*/virtual int		Damage_GetNoPhysicsForce(void);
	/*26 - 104*/virtual int		Damage_GetShouldNotBleed(void);

	CMultiplayRules();
	/*13 - 52*/virtual ~CMultiplayRules() {}

	void LoadVoiceCommandScript(void);

	/*134 - 536*/virtual bool ShouldDrawHeadLabels()
	{
		if (mp_show_voice_icons.GetBool() == false)
			return false;

		return BaseClass::ShouldDrawHeadLabels();
	}

#ifndef CLIENT_DLL
	/*
	doesn't exist on vmt
	virtual void FrameUpdatePostEntityThink();
	*/
	// GR_Think
	/*44 - 176*/virtual void Think(void);
	/*43 - 172*/virtual void RefreshSkillData(bool forceUpdate);
	/*45 - 180*/virtual bool IsAllowedToSpawn(CBaseEntity *pEntity);
	/*51 - 204*/virtual bool FAllowFlashlight(void);

	/*52 - 208*/virtual bool FShouldSwitchWeapon(CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon);
	/*28 - 112*/virtual CBaseCombatWeapon *GetNextBestWeapon(CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon);
	/*27 - 108*/virtual bool SwitchToNextBestWeapon(CBaseCombatCharacter *pPlayer, CBaseCombatWeapon *pCurrentWeapon);

	// Functions to verify the single/multiplayer status of a game
	/*53 - 212*/virtual bool IsDeathmatch(void);
	/*55 - 220*/virtual bool IsCoOp(void);

	// Client connection/disconnection
		// If ClientConnected returns FALSE, the connection is rejected and the user is provided the reason specified in
		//  svRejectReason
		// Only the client's name and remote address are provided to the dll for verification.
	/*57 - 228*/virtual bool ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen);
	/*58 - 232*/virtual void InitHUD(CBasePlayer *pl);		// the client dll is ready for updating
	/*59 - 236*/virtual void ClientDisconnected(edict_t *pClient);

	// Client damage rules
	/*60 - 240*/virtual float FlPlayerFallDamage(CBasePlayer *pPlayer);
	/*61 - 244*/virtual bool  FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker, const CTakeDamageInfo &info);
	/*68 - 272*/virtual bool AllowDamage(CBaseEntity *pVictim, const CTakeDamageInfo &info);

	// Client spawn/respawn control
	/*69 - 276*/virtual void PlayerSpawn(CBasePlayer *pPlayer);
	/*70 - 280*/virtual void PlayerThink(CBasePlayer *pPlayer);
	/*71 - 284*/virtual bool FPlayerCanRespawn(CBasePlayer *pPlayer);
	/*72 - 288*/virtual float FlPlayerSpawnTime(CBasePlayer *pPlayer);
	/*73 - 292*/virtual CBaseEntity *GetPlayerSpawnSpot(CBasePlayer *pPlayer);

	/*75 - 300*/virtual bool AllowAutoTargetCrosshair(void);

	// Client kills/scoring
	/*78 - 312*/virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	/*79 - 316*/virtual void PlayerKilled(CBasePlayer *pVictim, const CTakeDamageInfo &info);
	/*80 - 320*/virtual void DeathNotice(CBasePlayer *pVictim, const CTakeDamageInfo &info);
	CBasePlayer *GetDeathScorer(CBaseEntity *pKiller, CBaseEntity *pInflictor);									// old version of method - kept for backward compat
	/*138 - 552*/virtual CBasePlayer *GetDeathScorer(CBaseEntity *pKiller, CBaseEntity *pInflictor, CBaseEntity *pVictim);		// new version of method

// Weapon retrieval
	/*84 - 336*/virtual bool CanHavePlayerItem(CBasePlayer *pPlayer, CBaseCombatWeapon *pWeapon);// The player is touching an CBaseCombatWeapon, do I give it to him?

// Weapon spawn/respawn control
	/*85 - 340*/virtual int WeaponShouldRespawn(CBaseCombatWeapon *pWeapon);
	/*86 - 344*/virtual float FlWeaponRespawnTime(CBaseCombatWeapon *pWeapon);
	/*87 - 348*/virtual float FlWeaponTryRespawn(CBaseCombatWeapon *pWeapon);
	/*88 - 352*/virtual Vector VecWeaponRespawnSpot(CBaseCombatWeapon *pWeapon);

	// Item retrieval
	/*89 - 356*/virtual bool CanHaveItem(CBasePlayer *pPlayer, CItem *pItem);
	/*90 - 360*/virtual void PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem);

	// Item spawn/respawn control
	/*91 - 364*/virtual int ItemShouldRespawn(CItem *pItem);
	/*92 - 368*/virtual float FlItemRespawnTime(CItem *pItem);
	/*93 - 372*/virtual Vector VecItemRespawnSpot(CItem *pItem);
	/*94 - 376*/virtual QAngle VecItemRespawnAngles(CItem *pItem);

	// Ammo retrieval
	/*97 - 388*/virtual void PlayerGotAmmo(CBaseCombatCharacter *pPlayer, char *szName, int iCount);

	// Healthcharger respawn control
	/*101 - 404*/virtual float FlHealthChargerRechargeTime(void);
	/*102 - 408*/virtual float FlHEVChargerRechargeTime(void);

	// What happens to a dead player's weapons
	/*103 - 412*/virtual int DeadPlayerWeapons(CBasePlayer *pPlayer);

	// What happens to a dead player's ammo	
	/*104 - 416*/virtual int DeadPlayerAmmo(CBasePlayer *pPlayer);

	// Teamplay stuff	
	/*105 - 420*/virtual const char *GetTeamID(CBaseEntity *pEntity) { return ""; }
	/*106 - 424*/virtual int PlayerRelationship(CBaseEntity *pPlayer, CBaseEntity *pTarget);
	/*107 - 428*/ virtual bool PlayerCanHearChat(CBasePlayer *pListener, CBasePlayer *pSpeaker);

	/*115 - 460*/virtual bool PlayTextureSounds(void) { return FALSE; }
	/*116 - 464*/virtual bool PlayFootstepSounds(CBasePlayer *pl);

	// NPCs
	/*117 - 468*/virtual bool FAllowNPCs(void);

	// Immediately end a multiplayer game
	/*118 - 472*/virtual void EndMultiplayerGame(void) { GoToIntermission(); }

	// Voice commands
	/*76 - 304*/virtual bool ClientCommand(CBaseEntity *pEdict, const CCommand &args);
	/*139 - 556*/virtual VoiceCommandMenuItem_t *VoiceCommand(CBaseMultiplayerPlayer *pPlayer, int iMenu, int iItem);

	// Bugbait report	
	bool IsLoadingBugBaitReport(void);

	/*128 - 512*/virtual void ResetMapCycleTimeStamp(void) { m_nMapCycleTimeStamp = 0; }

	/*140 - 560*/virtual void HandleTimeLimitChange(void) { return; }

	void IncrementMapCycleIndex();

	void HaveAllPlayersSpeakConceptIfAllowed(int iConcept, int iTeam = TEAM_UNASSIGNED, const char *modifiers = NULL);
	void RandomPlayersSpeakConceptIfAllowed(int iConcept, int iNumRandomPlayer = 1, int iTeam = TEAM_UNASSIGNED, const char *modifiers = NULL);

	/*39 - 156*/virtual void GetTaggedConVarList(KeyValues *pCvarTagList);

	void SkipNextMapInCycle();

	/*38 - 152*/virtual void	ClientCommandKeyValues(edict_t *pEntity, KeyValues *pKeyValues);

public:

	struct ResponseRules_t
	{
		CUtlVector<IResponseSystem*> m_ResponseSystems;
	};
	CUtlVector<ResponseRules_t>	m_ResponseRules;

	/*141 - 564*/virtual void InitCustomResponseRulesDicts() {}
	/*142 - 568*/virtual void ShutdownCustomResponseRulesDicts() {}

	// NVNT virtual to check for haptic device 
	/*77 - 308*/virtual void ClientSettingsChanged(CBasePlayer *pPlayer);
	/*143 - 572*/virtual void GetNextLevelName(char *szNextMap, int bufsize, bool bRandom = false);

	static void DetermineMapCycleFilename(char *pszResult, int nSizeResult, bool bForceSpew);
	/*
	not on vmt
	virtual void LoadMapCycleFileIntoVector(const char *pszMapCycleFile, CUtlVector<char *> &mapList);
	*/
	static void FreeMapCycleFileVector(CUtlVector<char *> &mapList);

	// LoadMapCycleFileIntoVector without the fixups inherited versions of gamerules may provide
	static void RawLoadMapCycleFileIntoVector(const char *pszMapCycleFile, CUtlVector<char *> &mapList);

	bool IsMapInMapCycle(const char *pszName);

	/*
	not on vmt
	virtual bool IsManualMapChangeOkay(const char **pszReason) OVERRIDE;
	*/
protected:
	/*144 - 576*/virtual bool UseSuicidePenalty() { return true; }		// apply point penalty for suicide?
	/*
	not on vmt
	virtual float GetLastMajorEventTime(void) { return -1.0f; }
	*/
public:
	/*145 - 580*/virtual void ChangeLevel(void);

protected:
	/*146 - 584*/virtual void GoToIntermission(void);
	
	/*
	not on vmt
	virtual void LoadMapCycleFile(void);
	*/
	void ChangeLevelToMap(const char *pszMap);

	/*0x28?*/float m_flIntermissionEndTime;
	static int m_nMapCycleTimeStamp;
	static int m_nMapCycleindex;
	static CUtlVector<char*> m_MapList;

	float m_flTimeLastMapChangeOrPlayerWasConnected;

#else

public:
	const char *GetVoiceCommandSubtitle(int iMenu, int iItem);
	bool GetVoiceMenuLabels(int iMenu, KeyValues *pKV);

#endif

private:
	/*0x2C?*/CUtlVector< CUtlVector< VoiceCommandMenuItem_t > > m_VoiceCommandMenus;
};

#endif // MULTIPLAY_GAMERULES_H