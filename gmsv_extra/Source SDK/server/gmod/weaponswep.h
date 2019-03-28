#ifndef WEAPONSWEP_H
#define WEAPONSWEP_H

#include "../../hl2mp/weapon_hl2mpbasehlmpcombatweapon.h"
#include "../../../GLUA/CScriptedEntity.h"


class CWeaponSWEP : public CBaseHL2MPCombatWeapon
{
public:
	virtual ~CWeaponSWEP();

	/*436*/virtual void		DoKeyValue(char const*, char const*);
	/*437*/virtual void		UpdateLuaData(bool);
	/*438*/virtual bool		LuaEntityInitialized();
	/*439*/virtual bool		GetPrimaryAutomatic();
	/*440*/virtual bool		GetSecondaryAutomatic();
	/*441*/virtual void		UpdateHoldType();
public:
	BYTE pad_unk06[0x4];

	CScriptedEntity		m_ScriptedEntity;
	char				m_WorldModel[0x50];		// SWEP.WorldModel
	char				m_ViewModel[0x50];		// SWEP.ViewModel
	char				m_PrintName[0x50];		// SWEP.PrintName 
	char				HoldType[0x50];			// SWEP.HoldType
	char				HoldType2[0x50];		// copy of above?
	char const*			m_LuaClassName;
	int					PrimaryClipSize;		// SWEP.Primary.ClipSize
	int					PrimaryDefaultClip;		// SWEP.Primary.DefaultClip
	int					PrimaryAutomatic;		// SWEP.Primary.Automatic
	int					SecondaryClipSize;		// SWEP.Secondary.ClipSize
	int					SecondaryDefaultClip;	// SWEP.Secondary.DefaultClip
	int					SecondaryAutomatic;		// SWEP.Secondary.Automatic
	int					Weight;					// SWEP.Weight
	int					AutoSwitchTo;			// SWEP.AutoSwitchTo
	int					AutoSwitchFrom;			// SWEP.AutoSwitchFrom
	int					idk00;
	int					idk01;
	int					idk02;
	int					idk03;
	CBaseEntity*		m_pOwner;
};
#endif