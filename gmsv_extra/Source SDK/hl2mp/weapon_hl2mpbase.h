//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef WEAPON_HL2MPBASE_H
#define WEAPON_HL2MPBASE_H
#ifdef _WIN32
#pragma once
#endif

#include "hl2mp_player_shared.h"
#include "../basecombatweapon_shared.h"
#include "hl2mp_weapon_parse.h"

#if defined( CLIENT_DLL )
#define CWeaponHL2MPBase C_WeaponHL2MPBase
void UTIL_ClipPunchAngleOffset(QAngle &in, const QAngle &punch, const QAngle &clip);
#endif

class CHL2MP_Player;

// These are the names of the ammo types that go in the CAmmoDefs and that the 
// weapon script files reference.

// Given an ammo type (like from a weapon's GetPrimaryAmmoType()), this compares it
// against the ammo name you specify.
// MIKETODO: this should use indexing instead of searching and strcmp()'ing all the time.
bool IsAmmoType(int iAmmoType, const char *pAmmoName);

class CWeaponHL2MPBase : public CBaseCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponHL2MPBase, CBaseCombatWeapon);
	DECLARE_NETWORKCLASS();

	CWeaponHL2MPBase();



public:
	float		m_flPrevAnimTime;
	float		m_flNextResetCheckTime;

	Vector		m_vOriginalSpawnOrigin;
	QAngle		m_vOriginalSpawnAngles;
};


#endif // WEAPON_HL2MPBASE_H