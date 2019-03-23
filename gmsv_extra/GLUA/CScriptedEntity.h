#ifndef CSCRIPTEDENTITY_H
#define CSCRIPTEDENTITY_H

#include "IScriptedEntity.h"
class CBaseEntity;
class CScriptedEntity : public IScriptedEntity		// know this works for weapons.  I'll test other entities.
{
public:
	virtual void NetworkStateChanged() { }
	virtual void NetworkStateChanged(void*) { }
	char const* GetScriptName() { return m_ScriptName; }
	char const* GetModuleName() { return m_ModuleName; }
	char const* GetSelfName() { return m_SelfName; }
	void SetScriptName(char const* Name) {
		char Holder[0x40];
		V_strncpy(Holder, Name, 0x40);
		V_strlower(Holder);
		V_strncpy(m_ScriptName, Holder, 0x40);
	}
	void SetModuleName(char const* Name) { V_strncpy(m_ModuleName, Name, 0x40); }
	void SetSelfName(char const* Name) { V_strncpy(m_SelfName, Name, 0x40); }
public:
	/*0x4*/bool				m_bIDK;		
	/*0x8*/int				m_iType;		// 1 Sent, 2 Weapon 
	/*0xC*/CBaseEntity*		m_pEntity;		// the entity it's attached to.
	/*0x10*/char			m_ScriptName[0x40/*64*/];	// example m9k_val
	/*0x50*/char const*		m_pScriptName;
	/*0x54*/char			m_ModuleName[0x40/*64*/];
	/*0x94*/char			m_SelfName[0x40/*64*/];

	/*
	CWeaponSwep stuff.
	char			m_cWorldModel[0x50];
	char			m_cViewModel[0x50];
	char			m_cPrintName[0x50];
	char			m_cIDK[0x50]; // returns ar2 on weapons.
	char			m_cIDK2[0x50]; // returns ar2 on weapons.
	char const*		m_cpClassName2; // returns pointer to m_cClassName
	int				m_iIDK0;
	int				m_iIDK1;
	int				m_iIDK2;
	int				m_iIDK3;
	int				m_iIDK4;
	int				m_iIDK5;
	int				m_iIDK6;
	int				m_iIDK7;
	int				m_iIDK8;
	int				m_iIDK9;
	int				m_iIDK10;
	int				m_iIDK11;
	int				m_iIDK12;
	CBaseEntity*	m_pOwnerEntity;
	*/
};

#endif