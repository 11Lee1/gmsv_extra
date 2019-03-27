//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		Player for HL2.
//
// $NoKeywords: $
//=============================================================================//

#ifndef HL2_PLAYER_H
#define HL2_PLAYER_H
#pragma once


#include "../basemultiplayerplayer.h"
#include "hl2_playerlocaldata.h"
#include "../../simtimer.h"
#include "../../soundenvelope.h"

class CAI_Squad;
class CPropCombineBall;

extern int TrainSpeed(int iSpeed, int iMax);
extern void CopyToBodyQue(CBaseAnimating *pCorpse);

#define ARMOR_DECAY_TIME 3.5f

enum HL2PlayerPhysFlag_e
{
	// 1 -- 5 are used by enum PlayerPhysFlag_e in player.h

	PFLAG_ONBARNACLE = (1 << 6)		// player is hangning from the barnalce
};

class IPhysicsPlayerController;
class CLogicPlayerProxy;

struct commandgoal_t
{
	Vector		m_vecGoalLocation;
	CBaseEntity	*m_pGoalEntity;
};

// Time between checks to determine whether NPCs are illuminated by the flashlight
#define FLASHLIGHT_NPC_CHECK_INTERVAL	0.4

//----------------------------------------------------
// Definitions for weapon slots
//----------------------------------------------------
#define	WEAPON_MELEE_SLOT			0
#define	WEAPON_SECONDARY_SLOT		1
#define	WEAPON_PRIMARY_SLOT			2
#define	WEAPON_EXPLOSIVE_SLOT		3
#define	WEAPON_TOOL_SLOT			4

//=============================================================================
//=============================================================================
class CSuitPowerDevice
{
public:
	CSuitPowerDevice(int bitsID, float flDrainRate) { m_bitsDeviceID = bitsID; m_flDrainRate = flDrainRate; }
private:
	int		m_bitsDeviceID;	// tells what the device is. DEVICE_SPRINT, DEVICE_FLASHLIGHT, etc. BITMASK!!!!!
	float	m_flDrainRate;	// how quickly does this device deplete suit power? ( percent per second )

public:
	int		GetDeviceID(void) const { return m_bitsDeviceID; }
	float	GetDeviceDrainRate(void) const;
};

//=============================================================================
// >> HL2_PLAYER
//=============================================================================
class CHL2_Player : public CBaseMultiplayerPlayer
{
public:
	DECLARE_CLASS(CHL2_Player, CBaseMultiplayerPlayer);

	CHL2_Player();
	~CHL2_Player(void);

	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

public:
	// Commander Mode for controller NPCs
	enum CommanderCommand_t
	{
		_CC_NONE,
		_CC_TOGGLE,
		_CC_FOLLOW,
		_CC_SEND,
	};

	virtual void		SuspendUse(float flDuration);
	virtual void		CommanderMode();

	// Sprint Device
	virtual void		StartAutoSprint(void);
	virtual void		StartSprinting(void);
	virtual void		StopSprinting(void);
	virtual void		InitSprinting(void);
	virtual bool		CanSprint(void);
	virtual void		EnableSprint(bool bEnable);

	// Aiming heuristics accessors
	virtual float		GetIdleTime(void) const;
	virtual float		GetMoveTime(void) const;
	virtual float		GetLastDamageTime(void) const;
	virtual bool		IsDucking(void) const;

	virtual bool		Weapon_Lower(void);
	virtual bool		Weapon_Ready(void);


	virtual	bool		IsHoldingEntity(CBaseEntity *pEnt);
	virtual void		HandleSpeedChanges(void);
	virtual void		UpdateWeaponPosture(void);

	virtual void	NetworkStateChanged_m_fIsWalking(void);
	virtual void	NetworkStateChanged_m_fIsWalking(void*);


public:
	CSoundPatch*		m_sndLeeches;
	CSoundPatch*		m_sndWaterSplashes;

	Class_T				m_nControlClass;			// Class when player is controlling another entity
	// This player's HL2 specific data that should only be replicated to 
	//  the player and not to other players.
	CHL2PlayerLocalData m_HL2Local;

	float				m_flTimeAllSuitDevicesOff;

	bool				m_bSprintEnabled;		// Used to disable sprint temporarily
	bool				m_bIsAutoSprinting;		// A proxy for holding down the sprint key.
	float				m_fAutoSprintMinTime;	// Minimum time to maintain autosprint regardless of player speed. 

	bool				m_fIsSprinting;
	bool				m_fIsWalking;

protected:	// Jeep: Portal_Player needs access to this variable to overload PlayerUse for picking up objects through portals
	bool				m_bPlayUseDenySound;		// Signaled by PlayerUse, but can be unset by HL2 ladder code...

private:

	CAI_Squad *			m_pPlayerAISquad;
	CSimpleSimTimer		m_CommanderUpdateTimer;
	float				m_RealTimeLastSquadCommand;
	CommanderCommand_t	m_QueuedCommand;

	Vector				m_vecMissPositions[16];
	int					m_nNumMissPositions;

	float				m_flTimeIgnoreFallDamage;
	bool				m_bIgnoreFallDamageResetAfterImpact;

	// Suit power fields
	float				m_flSuitPowerLoad;	// net suit power drain (total of all device's drainrates)
	float				m_flAdmireGlovesAnimTime;

	float				m_flNextFlashlightCheckTime;
	float				m_flFlashlightPowerDrainScale;

	// Aiming heuristics code
	float				m_flIdleTime;		//Amount of time we've been motionless
	float				m_flMoveTime;		//Amount of time we've been in motion
	float				m_flLastDamageTime;	//Last time we took damage
	float				m_flTargetFindTime;

	EHANDLE				m_hPlayerProxy;

	bool				m_bFlashlightDisabled;
	bool				m_bUseCappedPhysicsDamageTable;

	float				m_flArmorReductionTime;
	int					m_iArmorReductionFrom;

	float				m_flTimeUseSuspended;

	CSimpleSimTimer		m_LowerWeaponTimer;
	CSimpleSimTimer		m_AutoaimTimer;

	EHANDLE				m_hLockedAutoAimEntity;

	EHANDLE				m_hLocatorTargetEntity; // The entity that's being tracked by the suit locator.

	float				m_flTimeNextLadderHint;	// Next time we're eligible to display a HUD hint about a ladder.

	friend class CHL2GameMovement;
};

#endif	//HL2_PLAYER_H