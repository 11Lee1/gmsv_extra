//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef PLAYERLOCALDATA_H
#define PLAYERLOCALDATA_H
#ifdef _WIN32
#pragma once
#endif

#include "../playernet_vars.h"
#include "fogcontroller.h"

//-----------------------------------------------------------------------------
// Purpose: Player specific data ( sent only to local player, too )
//-----------------------------------------------------------------------------
class CPlayerLocalData
{
public:
	// Save/restore
	DECLARE_SIMPLE_DATADESC();
	// Prediction data copying
	DECLARE_CLASS_NOBASE(CPlayerLocalData);
	DECLARE_EMBEDDED_NETWORKVAR();

	CPlayerLocalData();

	void UpdateAreaBits(CBasePlayer *pl, unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]);


public:

	unsigned char		m_chAreaBits[MAX_AREA_STATE_BYTES];								// Which areas are potentially visible to the client?
	unsigned char		m_chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES];	// Which area portals are open?

	int					m_iHideHUD;		// bitfields containing sections of the HUD to hide
	float				m_flFOVRate;		// rate at which the FOV changes (defaults to 0)

	Vector				m_vecOverViewpoint;			// Viewpoint overriding the real player's viewpoint

	// Fully ducked
	bool				m_bDucked;
	// In process of ducking
	bool				m_bDucking;
	// In process of duck-jumping
	bool				m_bInDuckJump;
	// During ducking process, amount of time before full duc
	float				m_flDucktime;
	float				m_flDuckJumpTime;
	// Jump time, time to auto unduck (since we auto crouch jump now).
	float				m_flJumpTime;
	// Step sound side flip/flip
	int					m_nStepside;;
	// Velocity at time when we hit ground
	float				m_flFallVelocity;
	// Previous button state
	int m_nOldButtons;
	class CSkyCamera *m_pOldSkyCamera;
	// Base velocity that was passed in to server physics so 
	//  client can predict conveyors correctly.  Server zeroes it, so we need to store here, too.
	// auto-decaying view angle adjustment
	QAngle				m_vecPunchAngle;
	QAngle				m_vecPunchAngleVel;
	// Draw view model for the player
	bool				m_bDrawViewmodel;

	// Is the player wearing the HEV suit
	bool				m_bWearingSuit;
	bool				m_bPoisoned;
	float				m_flStepSize;
	bool				m_bAllowAutoMovement;

	// 3d skybox
	sky3dparams_t		m_skybox3d;
	// world fog
	fogplayerparams_t	m_PlayerFog;
	fogparams_t			m_fog;
	// audio environment
	audioparams_t		m_audio;

	bool				m_bSlowMovement;
};


#endif // PLAYERLOCALDATA_H
