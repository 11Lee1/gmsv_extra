//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//===========================================================================//

#ifndef PLAYER_H
#define PLAYER_H
#ifdef _WIN32
#pragma once
#endif

#include "basecombatcharacter.h"
#include "../usercmd.h"
#include "playerlocaldata.h"
#include "../PlayerState.h"
#include "iplayerinfo.h"
#include "../hintsystem.h"
#include "../SoundEmitterSystem/isoundemittersystembase.h"
#include "../util_shared.h"

#if defined USES_ECON_ITEMS
#include "game_item_schema.h"
#include "econ_item_view.h"
#endif


// PlayerUse defines
#define	PLAYER_USE_RADIUS	80.f
#define CONE_45_DEGREES		0.707f
#define CONE_15_DEGREES		0.9659258f
#define CONE_90_DEGREES		0

#define TRAIN_ACTIVE	0x80 
#define TRAIN_NEW		0xc0
#define TRAIN_OFF		0x00
#define TRAIN_NEUTRAL	0x01
#define TRAIN_SLOW		0x02
#define TRAIN_MEDIUM	0x03
#define TRAIN_FAST		0x04 
#define TRAIN_BACK		0x05

// entity messages
#define PLAY_PLAYER_JINGLE	1
#define UPDATE_PLAYER_RADAR	2

#define DEATH_ANIMATION_TIME	3.0f

typedef struct
{
	Vector		m_vecAutoAimDir;		// The direction autoaim wishes to point.
	Vector		m_vecAutoAimPoint;		// The point (world space) that autoaim is aiming at.
	EHANDLE		m_hAutoAimEntity;		// The entity that autoaim is aiming at.
	bool		m_bAutoAimAssisting;	// If this is true, autoaim is aiming at the target. If false, the player is naturally aiming.
	bool		m_bOnTargetNatural;
	float		m_fScale;
	float		m_fMaxDist;
} autoaim_params_t;

enum stepsoundtimes_t
{
	STEPSOUNDTIME_NORMAL = 0,
	STEPSOUNDTIME_ON_LADDER,
	STEPSOUNDTIME_WATER_KNEE,
	STEPSOUNDTIME_WATER_FOOT,
};

enum
{
	itbd_Paralyze = 0,
	itbd_NerveGas,
	itbd_PoisonRecover,
	itbd_Radiation,
	itbd_DrownRecover,
	itbd_Acid,
	itbd_SlowBurn,
	itbd_SlowFreeze,

	// Must be last!
	CDMG_TIMEBASED
};

// For queuing and processing usercmds
class CCommandContext
{
public:
	CUtlVector< CUserCmd > cmds;

	int				numcmds;
	int				totalcmds;
	int				dropped_packets;
	bool			paused;
};

// Info about last 20 or so updates to the
class CPlayerCmdInfo
{
public:
	CPlayerCmdInfo() :
		m_flTime(0.0f), m_nNumCmds(0), m_nDroppedPackets(0)
	{
	}

	// realtime of sample
	float		m_flTime;
	// # of CUserCmds in this update
	int			m_nNumCmds;
	// # of dropped packets on the link
	int			m_nDroppedPackets;
};

class CPlayerSimInfo
{
public:
	CPlayerSimInfo() :
		m_flTime(0.0f), m_nNumCmds(0), m_nTicksCorrected(0), m_flFinalSimulationTime(0.0f), m_flGameSimulationTime(0.0f), m_flServerFrameTime(0.0f), m_vecAbsOrigin(0, 0, 0)
	{
	}

	// realtime of sample
	float		m_flTime;
	// # of CUserCmds in this update
	int			m_nNumCmds;
	// If clock needed correction, # of ticks added/removed
	int			m_nTicksCorrected; // +ve or -ve
	// player's m_flSimulationTime at end of frame
	float		m_flFinalSimulationTime;
	float		m_flGameSimulationTime;
	// estimate of server perf
	float		m_flServerFrameTime;
	Vector		m_vecAbsOrigin;
};
//-----------------------------------------------------------------------------
// Forward declarations: 
//-----------------------------------------------------------------------------
class CBaseCombatWeapon;
class CBaseViewModel;
class CTeam;
class IPhysicsPlayerController;
class IServerVehicle;
class CUserCmd;
class CFuncLadder;
class CNavArea;
class CHintSystem;
class CAI_Expresser;

#if defined USES_ECON_ITEMS
class CEconWearable;
#endif // USES_ECON_ITEMS

// for step sounds
struct surfacedata_t;

// !!!set this bit on guns and stuff that should never respawn.
#define	SF_NORESPAWN	( 1 << 30 )

//
// Player PHYSICS FLAGS bits
//
enum PlayerPhysFlag_e
{
	PFLAG_DIROVERRIDE = (1 << 0),		// override the player's directional control (trains, physics gun, etc.)
	PFLAG_DUCKING = (1 << 1),		// In the process of ducking, but totally squatted yet
	PFLAG_USING = (1 << 2),		// Using a continuous entity
	PFLAG_OBSERVER = (1 << 3),		// player is locked in stationary cam mode. Spectators can move, observers can't.
	PFLAG_VPHYSICS_MOTIONCONTROLLER = (1 << 4),	// player is physically attached to a motion controller
	PFLAG_GAMEPHYSICS_ROTPUSH = (1 << 5), // game physics did a rotating push that we may want to override with vphysics

	// If you add another flag here check that you aren't 
	// overwriting phys flags in the HL2 of TF2 player classes
};

//
// generic player
//
//-----------------------------------------------------
//This is Half-Life player entity
//-----------------------------------------------------
#define CSUITPLAYLIST	4		// max of 4 suit sentences queued up at any time
#define	SUIT_REPEAT_OK		0

#define SUIT_NEXT_IN_30SEC	30
#define SUIT_NEXT_IN_1MIN	60
#define SUIT_NEXT_IN_5MIN	300
#define SUIT_NEXT_IN_10MIN	600
#define SUIT_NEXT_IN_30MIN	1800
#define SUIT_NEXT_IN_1HOUR	3600

#define CSUITNOREPEAT		32

#define TEAM_NAME_LENGTH	16

// constant items
#define ITEM_HEALTHKIT		1
#define ITEM_BATTERY		4

#define AUTOAIM_2DEGREES  0.0348994967025
#define AUTOAIM_5DEGREES  0.08715574274766
#define AUTOAIM_8DEGREES  0.1391731009601
#define AUTOAIM_10DEGREES 0.1736481776669
#define AUTOAIM_20DEGREES 0.3490658503989

// useful cosines
#define DOT_1DEGREE   0.9998476951564
#define DOT_2DEGREE   0.9993908270191
#define DOT_3DEGREE   0.9986295347546
#define DOT_4DEGREE   0.9975640502598
#define DOT_5DEGREE   0.9961946980917
#define DOT_6DEGREE   0.9945218953683
#define DOT_7DEGREE   0.9925461516413
#define DOT_8DEGREE   0.9902680687416
#define DOT_9DEGREE   0.9876883405951
#define DOT_10DEGREE  0.9848077530122
#define DOT_15DEGREE  0.9659258262891
#define DOT_20DEGREE  0.9396926207859
#define DOT_25DEGREE  0.9063077870367
#define DOT_30DEGREE  0.866025403784
#define DOT_45DEGREE  0.707106781187
enum
{
	VPHYS_WALK = 0,
	VPHYS_CROUCH,
	VPHYS_NOCLIP,
};


enum PlayerConnectedState
{
	PlayerConnected,
	PlayerDisconnecting,
	PlayerDisconnected,
};

extern bool gInitHUD;
extern ConVar *sv_cheats;

class CBasePlayer;
class CPlayerInfo : public IBotController, public IPlayerInfo
{
public:
	CPlayerInfo() { m_pParent = NULL; }
	~CPlayerInfo() {}
	void SetParent(CBasePlayer *parent) { m_pParent = parent; }

	// IPlayerInfo interface
	virtual const char *GetName();
	virtual int			GetUserID();
	virtual const char *GetNetworkIDString();
	virtual int			GetTeamIndex();
	virtual void		ChangeTeam(int iTeamNum);
	virtual int			GetFragCount();
	virtual int			GetDeathCount();
	virtual bool		IsConnected();
	virtual int			GetArmorValue();

	virtual bool IsHLTV();
	virtual bool IsReplay();
	virtual bool IsPlayer();
	virtual bool IsFakeClient();
	virtual bool IsDead();
	virtual bool IsInAVehicle();
	virtual bool IsObserver();
	virtual const Vector GetAbsOrigin();
	virtual const QAngle GetAbsAngles();
	virtual const Vector GetPlayerMins();
	virtual const Vector GetPlayerMaxs();
	virtual const char *GetWeaponName();
	virtual const char *GetModelName();
	virtual const int GetHealth();
	virtual const int GetMaxHealth();

	// bot specific functions	
	virtual void SetAbsOrigin(Vector & vec);
	virtual void SetAbsAngles(QAngle & ang);
	virtual void RemoveAllItems(bool removeSuit);
	virtual void SetActiveWeapon(const char *WeaponName);
	virtual void SetLocalOrigin(const Vector& origin);
	virtual const Vector GetLocalOrigin(void);
	virtual void SetLocalAngles(const QAngle& angles);
	virtual const QAngle GetLocalAngles(void);
	virtual bool IsEFlagSet(int nEFlagMask);

	virtual void RunPlayerMove(CBotCmd *ucmd);
	virtual void SetLastUserCommand(const CBotCmd &cmd);

	virtual CBotCmd GetLastUserCommand();

private:
	CBasePlayer *m_pParent;
};


class CBasePlayer : public CBaseCombatCharacter
{
public:
	DECLARE_CLASS(CBasePlayer, CBaseCombatCharacter);

public:
	virtual void			CreateViewModel(int viewmodelindex = 0);


	// Networking is about to update this entity, let it override and specify it's own pvs
	virtual void			SetupVisibility(CBaseEntity *pViewEntity, unsigned char *pvs, int pvssize);

	// Returns true if this player wants pPlayer to be moved back in time when this player runs usercmds.
	// Saves a lot of overhead on the server if we can cull out entities that don't need to lag compensate
	// (like team members, entities out of our PVS, etc).
	virtual bool			WantsLagCompensationOnEntity(const CBasePlayer	*pPlayer, const CUserCmd *pCmd, const CBitVec<MAX_EDICTS> *pEntityTransmitBits) const;

	virtual void			SharedSpawn(); // Shared between client and server.
	virtual void			ForceRespawn(void);

	virtual void			InitialSpawn(void);
	virtual void			InitHUD(void) {}
	virtual void			ShowViewPortPanel(const char * name, bool bShow = true, KeyValues *data = NULL);

	virtual void			PlayerDeathThink(void);

	virtual void			Jump(void);
	virtual void			Duck(void);


	virtual void			PreThink(void);
	virtual void			PostThink(void);
	virtual void			DamageEffect(float flDamage, int fDamageType);

	virtual void			OnDamagedByExplosion(const CTakeDamageInfo &info);

	virtual bool			ShouldFadeOnDeath(void) { return FALSE; }

	virtual bool			IsFakeClient(void) const;

	virtual const Vector	GetPlayerMins(void) const; // uses local player
	virtual const Vector	GetPlayerMaxs(void) const; // uses local player

	virtual float			CalcRoll(const QAngle& angles, const Vector& velocity, float rollangle, float rollspeed);

	virtual void			PackDeadPlayerItems(void);
	virtual void			RemoveAllItems(bool removeSuit);


	virtual void			Weapon_SetLast(CBaseCombatWeapon *pWeapon);
	virtual bool			Weapon_ShouldSetLast(CBaseCombatWeapon *pOldWeapon, CBaseCombatWeapon *pNewWeapon) { return true; }
	virtual bool			Weapon_ShouldSelectItem(CBaseCombatWeapon *pWeapon);


	virtual void			OnMyWeaponFired(CBaseCombatWeapon *weapon);	// call this when this player fires a weapon to allow other systems to react
	virtual float			GetTimeSinceWeaponFired(void) const;			// returns the time, in seconds, since this player fired a weapon
	virtual bool			IsFiringWeapon(void) const;					// return true if this player is currently firing their weapon

	// JOHN:  sends custom messages if player HUD data has changed  (eg health, ammo)
	virtual void			UpdateClientData(void);

	virtual void			ExitLadder() {}
	virtual surfacedata_t*	GetLadderSurface(const Vector &origin);

	virtual void			SetFlashlightEnabled(bool bState) { };
	virtual int				FlashlightIsOn(void) { return false; }
	virtual void			FlashlightTurnOn(void) { };
	virtual void			FlashlightTurnOff(void) { };
	virtual bool			IsIlluminatedByFlashlight(CBaseEntity *pEntity, float *flReturnDot) { return false; }

	virtual void			UpdateStepSound(surfacedata_t *psurface, const Vector &vecOrigin, const Vector &vecVelocity);
	virtual void			PlayStepSound(Vector &vecOrigin, surfacedata_t *psurface, float fvol, bool force);
	virtual const char*		GetOverrideStepSound(const char *pszBaseStepSoundName) { return pszBaseStepSoundName; }
	virtual void			GetStepSoundVelocities(float *velwalk, float *velrun);
	virtual void			SetStepSoundTime(stepsoundtimes_t iStepSoundTime, bool bWalking);
	virtual void			DeathSound(const CTakeDamageInfo &info);
	virtual const char*		GetSceneSoundToken(void) { return ""; }

	virtual void			OnEmitFootstepSound(const CSoundParameters& params, const Vector& vecOrigin, float fVolume) {}

	virtual void			SetAnimation(PLAYER_ANIM playerAnim);

	// custom player functions
	virtual void			ImpulseCommands(void);
	virtual void			CheatImpulseCommands(int iImpulse);
	virtual bool			ClientCommand(const CCommand &args);

	// Observer functions
	virtual bool			StartObserverMode(int mode); // true, if successful
	virtual void			StopObserverMode(void);	// stop spectator mode
	virtual bool			ModeWantsSpectatorGUI(int iMode) { return true; }
	virtual bool			SetObserverMode(int mode); // sets new observer mode, returns true if successful
	virtual int				GetObserverMode(void); // returns observer mode or OBS_NONE
	virtual bool			SetObserverTarget(CBaseEntity * target);
	virtual void			ObserverUse(bool bIsPressed); // observer pressed use
	virtual CBaseEntity*	GetObserverTarget(void); // returns players targer or NULL
	virtual CBaseEntity*	FindNextObserverTarget(bool bReverse); // returns next/prev player to follow or NULL
	virtual int				GetNextObserverSearchStartPoint(bool bReverse); // Where we should start looping the player list in a FindNextObserverTarget call
	virtual bool			IsValidObserverTarget(CBaseEntity * target); // true, if player is allowed to see this target
	virtual void			CheckObserverSettings(); // checks, if target still valid (didn't die etc)
	virtual void			JumptoPosition(const Vector &origin, const QAngle &angles);
	virtual void			ForceObserverMode(int mode); // sets a temporary mode, force because of invalid targets
	virtual void			ResetObserverMode(); // resets all observer related settings
	virtual void			ValidateCurrentObserverTarget(void); // Checks the current observer target, and moves on if it's not valid anymore
	virtual void			AttemptToExitFreezeCam(void);

	virtual bool			StartReplayMode(float fDelay, float fDuration, int iEntity);
	virtual void			StopReplayMode();
	virtual int				GetDelayTicks();
	virtual int				GetReplayEntity();

	virtual void			CreateCorpse(void) { }
	virtual CBaseEntity*	EntSelectSpawnPoint(void);

	// Vehicles
	virtual bool			GetInVehicle(IServerVehicle *pVehicle, int nRole);
	virtual void			LeaveVehicle(const Vector &vecExitPoint = vec3_origin, const QAngle &vecExitAngles = vec3_angle);

	// override these for 
	virtual void			OnVehicleStart() {}
	virtual void			OnVehicleEnd(Vector &playerDestPosition) {}


	virtual bool			BumpWeapon(CBaseCombatWeapon *pWeapon);
	virtual void			SelectLastItem(void);
	virtual void			SelectItem(const char *pstr, int iSubType = 0);
	virtual void			ItemPostFrame(void);
	virtual CBaseEntity*	GiveNamedItem(const char *szName, int iSubType = 0);
	virtual void			CheckTrainUpdate(void);

	virtual void			SetPlayerUnderwater(bool state);

	virtual bool			CanBreatheUnderwater() const { return false; }
	virtual void			PlayerUse(void);
	virtual void			PlayUseDenySound() {}

	virtual CBaseEntity*	FindUseEntity(void);
	virtual bool			IsUseableEntity(CBaseEntity *pEntity, unsigned int requiredCaps);

	// physics interactions
	// mass/size limit set to zero for none
	virtual void			PickupObject(CBaseEntity *pObject, bool bLimitMassAndSize = true) {}
	virtual void			ForceDropOfCarriedPhysObjects(CBaseEntity *pOnlyIfHoldindThis = NULL) {}
	virtual float			GetHeldObjectMass(IPhysicsObject *pHeldObject);

	virtual void			UpdateGeigerCounter(void);

	virtual Vector			GetAutoaimVector(float flScale);
	virtual Vector			GetAutoaimVector(float flScale, float flMaxDist);
	virtual void			GetAutoaimVector(autoaim_params_t &params);

	virtual bool			ShouldAutoaim(void);

	virtual void			ForceClientDllUpdate(void);  // Forces all client .dll specific data to be resent to client.
	virtual void			ProcessUsercmds(CUserCmd *cmds, int numcmds, int totalcmds, int dropped_packets, bool paused);

	// Run a user command. The default implementation calls ::PlayerRunCommand. In TF, this controls a vehicle if
	// the player is in one.
	virtual void			PlayerRunCommand(CUserCmd *ucmd, IMoveHelper *moveHelper);

	virtual void			ChangeTeam(int iTeamNum, bool bAutoTeam, bool bSilent);

	// say/sayteam allowed?
	virtual bool			CanHearAndReadChatFrom(CBasePlayer *pPlayer) { return true; }
	virtual bool			CanSpeak(void) { return true; }

	virtual void 			ModifyOrAppendPlayerCriteria(AI_CriteriaSet& set);

	virtual void			CheckChatText(char *p, int bufsize) {}

	virtual void			CreateRagdollEntity(void) { return; }

	virtual bool			ShouldAnnounceAchievement(void);

	virtual bool			IsFollowingPhysics(void) { return false; }

	virtual void			InitVCollision(const Vector &vecAbsOrigin, const Vector &vecAbsVelocity);
	virtual void			UpdatePhysicsShadowToCurrentPosition();

	// Hint system
	virtual CHintSystem*	Hints(void) { return NULL; }

	// Round gamerules
	virtual bool			IsReadyToPlay(void) { return true; }
	virtual bool			IsReadyToSpawn(void) { return true; }
	virtual bool			ShouldGainInstantSpawn(void) { return false; }
	virtual void			ResetPerRoundStats(void) { return; }


	virtual void			ResetScores(void);

	virtual void			EquipSuit(bool bPlayEffects = true);
	virtual void			RemoveSuit(void);

	virtual float			GetPlayerMaxSpeed();

	// Suicide...
	virtual void			CommitSuicide(bool bExplode = false, bool bForce = false);
	virtual void			CommitSuicide(const Vector &vecForce, bool bExplode = false, bool bForce = false);

	virtual bool			IsBot() const;		// IMPORTANT: This returns true for ANY type of bot. If your game uses different, incompatible types of bots check your specific bot type before casting
	virtual bool			IsBotOfType(int botType) const;	// return true if this player is a bot of the specific type (zero is invalid)
	virtual int				GetBotType(void) const;			// return a unique int representing the type of bot instance this is

	virtual CAI_Expresser *GetExpresser() { return NULL; }; // dont use will break.


	virtual void			UpdateButtonState(int nUserCmdButtonMask);

	virtual int				SpawnArmorValue(void) const { return 0; }

	virtual void			NetworkStateChanged_m_ArmorValue(void);
	virtual void			NetworkStateChanged_m_ArmorValue(void*);

	// NVNT returns true if user has a haptic device
	virtual bool			HasHaptics() { return m_bhasHaptics; }
	// NVNT sets weather a user should receive haptic device messages.
	virtual void			SetHaptics(bool has) { m_bhasHaptics = has; }
	virtual unsigned int	PlayerSolidMask(bool brushOnly = false) const;	// returns the solid mask for the given player, so bots can have a more-restrictive set


	virtual void			OnPlayerSay(char const*msg);
	virtual void			RestrictPlayerPitch();
	virtual float			GetSprintSpeed();
	virtual float			GetWalkSpeed();
	virtual float			GetCrouchedWalkSpeed();
	virtual float			GetDuckSpeed();
	virtual float			GetUnDuckSpeed();
	virtual void			SetSprintSpeed(float speed);
	virtual void			SetWalkSpeed(float speed);
	virtual void			SetCrouchedWalkSpeed(float speed);
	virtual void			SetDuckSpeed(float speed);
	virtual void			SetUnDuckSpeed(float speed);
	virtual bool			CanAttack(void);
	virtual void			MouseWheel();
	virtual void			SetMouseWheel(int);
public:
	BYTE	pad_unk05[0x4];
	// How much of a movement time buffer can we process from this user?
	float				m_flMovementTimeForUserCmdProcessingRemaining;
	// Used by gamemovement to check if the entity is stuck.
	int					m_StuckLast;
	CPlayerLocalData	m_Local;

	BYTE	pad_unk06[0x14];
	// Used by env_soundscape_triggerable to manage when the player is touching multiple
	// soundscape triggers simultaneously.
	// The one at the HEAD of the list is always the current soundscape for the player.
	CUtlVector<EHANDLE> m_hTriggerSoundscapeList;
	// Player data that's sometimes needed by the engine
	CPlayerState		pl;

	int					m_nButtons;
	int					m_afButtonPressed;
	int					m_afButtonReleased;
	int					m_afButtonLast;
	int					m_afButtonDisabled;	// A mask of input flags that are cleared automatically
	int					m_afButtonForced; // 
	int					m_keyboardbutton;  // see what buttons are pressed on their keyboard, kinda scarry. - lee

	bool				m_fOnTarget; //Is the crosshair on a target?
	bool				m_bNoIdea0; // dunno

	char				m_szAnimExtension[32];
	int					m_nUpdateRate; // user snapshot rate cl_updaterate

	float				m_fLerpTime;		// users cl_interp
	bool				m_bLagCompensation;	// user wants lag compenstation
	bool				m_bPredictWeapons; //  user has client side predicted weapons

	//Activity			m_Activity; // it's either: m_Activity or m_flLastObjectiveTime dunno, gonna go with m_flLastObjectiveTime.
	float				m_flLastObjectiveTime; // Last curtime player touched/killed something the gamemode considers an objective

	// Secondary point to derive PVS from when zoomed in with binoculars/sniper rifle.  The PVS is 
	//  a merge of the standing origin and this additional origin
	Vector				m_vecAdditionalPVSOrigin;
	// Extra PVS origin if we are using a camera object
	Vector				m_vecCameraPVSOrigin;

	EHANDLE				m_hUseEntity; // the player is currently controlling this entity because of +USE latched, NULL if no entity
	int					m_iTrain; // Train control position

	float				m_iRespawnFrames;	// used in PlayerDeathThink() to make sure players can always respawn
	unsigned int		m_afPhysicsFlags;	// physics flags - set when 'normal' physics should be revisited or overriden

	EHANDLE				m_hVehicle;
	int					m_iVehicleAnalogBias;

	bool				m_bPauseBonusProgress;
	int					m_iBonusProgress;
	int					m_iBonusChallenge;

	int					m_lastDamageAmount;		// Last damage taken

	Vector				m_DmgOrigin;
	float				m_DmgTake;
	float				m_DmgSave;
	int					m_bitsDamageType;	// what types of damage has player taken
	int					m_bitsHUDDamage;	// Damage bits for the current fame. These get sent to the hud via gmsgDamage

	float				m_flDeathTime;		// the time at which the player died  (used in PlayerDeathThink())
	float				m_flDeathAnimTime;	// the time at which the player finished their death anim (used in PlayerDeathThink() and ShouldTransmit())

	int					m_iObserverMode;	// if in spectator mode != 0
	float				m_iFOV;			// field of view
	float				m_iDefaultFOV;	// default field of view
	float				m_iFOVStart;		// What our FOV started at
	float				m_flFOVTime; // Time our FOV change started

	int					m_iObserverLastMode; // last used observer mode
	EHANDLE				m_hObserverTarget;	// entity handle to m_iObserverTarget
	bool				m_bForcedObserverMode; // true, player was forced by invalid targets to switch mode

	EHANDLE				m_hZoomOwner;	//This is a pointer to the entity currently controlling the player's zoom
													//Only this entity can change the zoom state once it has ownership

	float				m_tbdPrev;				// Time-based damage timer
	int					m_idrowndmg;			// track drowning damage taken
	int					m_idrownrestored;		// track drowning damage restored
	int					m_nPoisonDmg;			// track recoverable poison damage taken
	int					m_nPoisonRestored; // track poison damage restored

	// NOTE: bits damage type appears to only be used for time-based damage
	BYTE				m_rgbTimeBasedDamage[CDMG_TIMEBASED];

	// Player Physics Shadow
	int					m_vphysicsCollisionState;

	float				m_fNextSuicideTime; // the time after which the player can next use the suicide command
	int					m_iSuicideCustomKillFlags;

	// Replay mode	
	float				m_fDelay;			// replay delay in seconds
	float				m_fReplayEnd;		// time to stop replay mode
	int					m_iReplayEntity; // follow this entity in replay

	CUtlVector< CCommandContext > m_CommandContext;

	IPhysicsPlayerController*m_pPhysicsController;
	IPhysicsObject*		m_pShadowStand;
	IPhysicsObject*		m_pShadowCrouch;
	Vector				m_oldOrigin;
	Vector				m_vecSmoothedVelocity;
	bool				m_touchedPhysObject;
	bool				m_bPhysicsWasFrozen;

	int					m_iPlayerSound;// the index of the sound list slot reserved for this player
	int					m_iTargetVolume;// ideal sound volume. 

	int					m_rgItems[MAX_ITEMS];

	// these are time-sensitive things that we keep track of
	float				m_flSwimTime;		// how long player has been underwater
	float				m_flDuckTime;		// how long we've been ducking
	float				m_flDuckJumpTime;

	float				m_flSuitUpdate;					// when to play next suit update
	int					m_rgSuitPlayList[CSUITPLAYLIST];// next sentencenum to play for suit update
	int					m_iSuitPlayNext;				// next sentence slot for queue storage;
	int					m_rgiSuitNoRepeat[CSUITNOREPEAT];		// suit sentence no repeat list
	float				m_rgflSuitNoRepeatTime[CSUITNOREPEAT];	// how long to wait before allowing repeat

	float				m_flgeigerRange;		// range to nearest radiation source
	float				m_flgeigerDelay;		// delay per update of range msg to client
	int					m_igeigerRangePrev;

	bool				m_fInitHUD;				// True when deferred HUD restart msg needs to be sent
	bool				m_fGameHUDInitialized;
	bool				m_fWeapon;				// Set this to FALSE to force a reset of the current weapon HUD info

	int					m_iUpdateTime;		// stores the number of frame ticks before sending HUD update messages
	int					m_iClientBattery;	// the Battery currently known by the client.  If this changes, send a new

	// Autoaim data
	QAngle				m_vecAutoAim;
	int					m_lastx, m_lasty;	// These are the previous update's crosshair angles, DON"T SAVE/RESTORE

	int					m_iFrags;
	int					m_iDeaths;

	float				m_flNextDecalTime;// next time this player can spray a decal

	// Team Handling
	// char					m_szTeamName[TEAM_NAME_LENGTH];

	// Multiplayer handling
	PlayerConnectedState	m_iConnected;

	// from edict_t
	// CBasePlayer doesn't send this but CCSPlayer does.
	int					m_ArmorValue;
	float				m_AirFinished;
	float				m_PainFinished;

	// player locking
	int					m_iPlayerLocked;
	EHANDLE				m_hViewModel[MAX_VIEWMODELS];

	// Last received usercmd (in case we drop a lot of packets )
	CUserCmd			m_LastCmd;
	CUserCmd			*m_pCurrentCommand;
	int					m_iLockViewanglesTickNumber;
	QAngle				m_qangLockViewangles;

	float				m_flStepSoundTime;	// time to check for next footstep sound

	bool				m_bAllowInstantSpawn;

	// Replicated to all clients
	float				m_flMaxSpeed;

	// Not transmitted
	float				m_flWaterJumpTime;  // used to be called teleport_time
	Vector				m_vecWaterJumpVel;
	int					m_nImpulse;
	float				m_flSwimSoundTime;
	Vector				m_vecLadderNormal;

	float				m_flFlashTime;
	int					m_nDrownDmgRate;		// Drowning damage in points per second without air.

	int					m_nNumCrouches;			// Number of times we've crouched (for hinting)
	bool				m_bDuckToggled;		// If true, the player is crouching via a toggle


	float				m_flForwardMove;
	float				m_flSideMove;
	int					m_nNumCrateHudHints;

	// Used in test code to teleport the player to random locations in the map.
	Vector				m_vForcedOrigin;
	bool				m_bForceOrigin;

	// Clients try to run on their own realtime clock, this is this client's clock
	int					m_nTickBase;

	bool				m_bGamePaused;
	float				m_fLastPlayerTalkTime;

	EHANDLE				m_hLastWeapon;

	CUtlVector< CHandle< CBaseEntity > > m_SimulatedByThisPlayer;

	float				m_flOldPlayerZ;
	float				m_flOldPlayerViewOffsetZ;

	bool				m_bPlayerUnderwater;

	EHANDLE				m_hViewEntity;

	BYTE		pad_unk07[0x4];

	// Movement constraints
	EHANDLE				m_hConstraintEntity;
	Vector				m_vecConstraintCenter;
	float				m_flConstraintRadius;
	float				m_flConstraintWidth;
	float				m_flConstraintSpeedFactor;

	// Player name
	char				m_szNetname[MAX_PLAYER_NAME_LENGTH];

	float				m_flLaggedMovementValue;

	// These are generated while running usercmds, then given to UpdateVPhysicsPosition after running all queued commands.
	Vector				m_vNewVPhysicsPosition;
	Vector				m_vNewVPhysicsVelocity;

	Vector				m_vecVehicleViewOrigin;		// Used to store the calculated view of the player while riding in a vehicle
	QAngle				m_vecVehicleViewAngles;		// Vehicle angles
	float				m_flVehicleViewFOV;			// FOV of the vehicle driver
	int					m_nVehicleViewSavedFrame;	// Used to mark which frame was the last one the view was calculated for

	Vector				m_vecPreviouslyPredictedOrigin; // Used to determine if non-gamemovement game code has teleported, or tweaked the player's origin
	int					m_nBodyPitchPoseParam;

	char				m_szLastPlaceName[MAX_PLACE_NAME_LENGTH];

	char				m_szNetworkIDString[MAX_NETWORKID_LENGTH]; // steamid
	CPlayerInfo			m_PlayerInfo;

	// Texture names and surface data, used by CGameMovement
	int					m_surfaceProps;
	surfacedata_t*		m_pSurfaceData;
	float				m_surfaceFriction;
	char				m_chTextureType;
	char				m_chPreviousTextureType;	// Separate from m_chTextureType. This is cleared if the player's not on the ground.

	bool				m_bSinglePlayerGameEnding;

	// NVNT member variable holding if this user is using a haptic device.
	bool				m_bhasHaptics;

	bool				m_autoKickDisabled;

	struct StepSoundCache_t
	{
		StepSoundCache_t() : m_usSoundNameIndex(0) {}
		CSoundParameters	m_SoundParameters;
		unsigned short		m_usSoundNameIndex;
	};
	// One for left and one for right side of step
	StepSoundCache_t	m_StepSoundCache[2];

	CUtlLinkedList< CPlayerSimInfo >  m_vecPlayerSimInfo;
	CUtlLinkedList< CPlayerCmdInfo >  m_vecPlayerCmdInfo;

	IntervalTimer		m_weaponFiredTimer;

	// Store the last time we successfully processed a usercommand
	float				m_flLastUserCommandTime;

	Vector				m_vecBBStanding[2]; // 0 mins 1 maxs
	Vector				m_vecBBCrouching[2]; // 0 mins 1 maxs

	BYTE	pad_unk08[0x24];

public:
	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

};

typedef CHandle<CBasePlayer> CBasePlayerHandle;


// finish


#endif // PLAYER_H
