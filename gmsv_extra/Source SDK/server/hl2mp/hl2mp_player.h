//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#ifndef HL2MP_PLAYER_H
#define HL2MP_PLAYER_H
#pragma once

class CHL2MP_Player;

#include "../basemultiplayerplayer.h"
#include "../hl2/hl2_playerlocaldata.h"
#include "../hl2/hl2_player.h"
#include "../../simtimer.h"
#include "../../soundenvelope.h"
#include "../../hl2mp/hl2mp_player_shared.h"
#include "../../hl2mp/hl2mp_gamerules.h"
#include "../../tier1/utldict.h"

//=============================================================================
// >> HL2MP_Player
//=============================================================================
class CHL2MPPlayerStateInfo
{
public:
	HL2MPPlayerState m_iPlayerState;
	const char *m_pStateName;

	void (CHL2MP_Player::*pfnEnterState)();	// Init and deinit the state.
	void (CHL2MP_Player::*pfnLeaveState)();

	void (CHL2MP_Player::*pfnPreThink)();	// Do a PreThink() in this state.
};

class CHL2MP_Player : public CHL2_Player
{
public:
	DECLARE_CLASS(CHL2MP_Player, CHL2_Player);

	CHL2MP_Player();
	~CHL2MP_Player(void);

	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

public:
	Vector				m_vecTotalBulletForce;	//Accumulator for bullet force in a single frame

	// Tracks our ragdoll entity.
	EHANDLE				m_hRagdoll;	// networked entity handle 

	QAngle				m_angEyeAngles;
	CPlayerAnimState*	m_PlayerAnimState;

	int					m_iLastWeaponFireUsercmd;
	int					m_iModelType;
	int					m_iSpawnInterpCounter;
	int					m_iPlayerSoundType;

	float				m_flNextModelChangeTime;
	float				m_flNextTeamChangeTime;

	float				m_flSlamProtectTime;

	HL2MPPlayerState	m_iPlayerState;
	CHL2MPPlayerStateInfo *m_pCurStateInfo;

	// This lets us rate limit the commands the players can execute so they don't overflow things like reliable buffers.
	CUtlDict<float, int>	m_RateLimitLastCommandTimes;

	bool				m_bEnterObserver;
	bool				m_bReady;
};
#endif //HL2MP_PLAYER_H