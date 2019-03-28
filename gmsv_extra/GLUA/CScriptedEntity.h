#ifndef CSCRIPTEDENTITY_H
#define CSCRIPTEDENTITY_H

#include "IScriptedEntity.h"
class CBaseEntity;
class CScriptedEntity : public IScriptedEntity
{
public:
	virtual void NetworkStateChanged() { }
	virtual void NetworkStateChanged(void*) { }
	char const* GetScriptName() { return m_ScriptName; }
	char const* GetModuleName() { return m_ModuleName; }
	char const* GetSelfName() { return m_SelfName; }
private:
	// dont use.
	void SetScriptName(char const* Name) {
		V_strncpy(m_ScriptName, Name, 0x40);
		V_strlower(m_ScriptName);
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
};

#endif