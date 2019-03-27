//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef HL2_PLAYERLOCALDATA_H
#define HL2_PLAYERLOCALDATA_H
#ifdef _WIN32
#pragma once
#endif

#include "../../networkvar.h"

#include "../../hl2/hl_movedata.h"

//-----------------------------------------------------------------------------
// Purpose: Player specific data for HL2 ( sent only to local player, too )
//-----------------------------------------------------------------------------
class CHL2PlayerLocalData
{
public:
	// Save/restore
	DECLARE_SIMPLE_DATADESC();
	DECLARE_CLASS_NOBASE(CHL2PlayerLocalData);
	DECLARE_EMBEDDED_NETWORKVAR();

	CHL2PlayerLocalData();

	float				m_flSuitPower;
	bool				m_bZooming;
	int					m_bitsActiveDevices;
	int					m_iSquadMemberCount;
	int					m_iSquadMedicCount;
	bool				m_fSquadInFollowMode;
	bool				m_bWeaponLowered;
	EHANDLE				m_hAutoAimTarget;
	Vector				m_vecAutoAimPoint;
	bool				m_bDisplayReticle;
	bool				m_bStickyAutoAim;
	bool				m_bAutoAimTarget;
#ifdef HL2_EPISODIC
	CNetworkVar(float, m_flFlashBattery);
	CNetworkVar(Vector, m_vecLocatorOrigin);
#endif

	// Ladder related data
	EHANDLE				m_hLadder;
	LadderMove_t		m_LadderMove;
};


#endif // HL2_PLAYERLOCALDATA_H