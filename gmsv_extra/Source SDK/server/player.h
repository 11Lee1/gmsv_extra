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
protected:
	// HACK FOR BOTS
	friend class CBotManager;
	static edict_t *s_PlayerEdict; // must be set before calling constructor
public:
	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

};

typedef CHandle<CBasePlayer> CBasePlayerHandle;


// finish


#endif // PLAYER_H
