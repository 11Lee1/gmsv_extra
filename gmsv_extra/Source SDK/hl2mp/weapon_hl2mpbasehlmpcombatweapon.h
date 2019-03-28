//========= Copyright Valve Corporation, All rights reserved. ============//
#ifndef WEAPON_BASEHL2MPCOMBATWEAPON_SHARED_H
#define WEAPON_BASEHL2MPCOMBATWEAPON_SHARED_H
#ifdef _WIN32
#pragma once
#endif


#include "../server/hl2mp/hl2mp_player.h"
#include "weapon_hl2mpbase.h"


class CBaseHL2MPCombatWeapon : public CWeaponHL2MPBase
{
public:
	DECLARE_DATADESC();
	DECLARE_CLASS(CBaseHL2MPCombatWeapon, CWeaponHL2MPBase);
	DECLARE_NETWORKCLASS();

	CBaseHL2MPCombatWeapon();
	CBaseHL2MPCombatWeapon(const CBaseHL2MPCombatWeapon &);

public:
	virtual bool	WeaponShouldBeLowered();

public:
	bool			m_bLowered;			// Whether the viewmodel is raised or lowered
	float			m_flRaiseTime;		// If lowered, the time we should raise the viewmodel
	float			m_flHolsterTime;	// When the weapon was holstered
};

#endif // WEAPON_BASEHL2MPCOMBATWEAPON_SHARED_H