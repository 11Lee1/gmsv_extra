#ifndef CLUAINTERFACE_H
#define CLUAINTERFACE_H
#include "ILuaInterface.h"

struct lua_State;
class CLuaGameCallback;
class GarrysMod::Lua::CLuaObject;
class CLuaInterface : public ILuaInterface
{
public:
	CBaseEntity*		GetEntity(int iStackPos);
	void				PushEntity(CBaseEntity* Entity);
public:
#ifdef _WIN32
	lua_State*			m_LuaState;				// 0x4  -  functions from the lua interface use functions from the LuaAPI using this pointer.
	unsigned int        m_uiUNK_000;			// 0x8
	char*				m_UNK_000;				// 0xC
	unsigned int        m_uiUNK_001;			// 0x10
	char                PAD_UNK_000[0x8];		// 0x14       
	char*				m_UNK_001;				// 0x1C
	void*				m_pUNK_000;				// 0x20
	char                PAD_UNK_001[0x4];		// 0x24
	GarrysMod::Lua::CLuaObject*			m_LuaObjUNK_000;		// 0x28
	GarrysMod::Lua::CLuaObject*			m_LuaObjUNK_001;		// 0x2C
	char                PAD_UNK_002[0x8];		// 0x30
	GarrysMod::Lua::CLuaObject*			m_LuaObjUNK_002[32];	// 0x38
	char                m_cLuaState;			// 0xB8  -  uses the enums Client, Server, Menu.
	CLuaGameCallback*	m_LuaCBUNK_000;			// 0xBC
	unsigned int        m_uiUNK_002;			// 0xC0
	char                PAD_UNK_003[0x1C];		// 0xC4
	unsigned int        m_uiUNK_003;			// 0xE0
	GarrysMod::Lua::CLuaObject*			m_LuaObjUNK_003;		// 0xE4
	GarrysMod::Lua::CLuaObject*			m_LuaObjUNK_004;		// 0xE8
	int                 m_iNumMetaTables;		// 0xEC
	GarrysMod::Lua::CLuaObject*			m_MetaTables[0xFF];		// 0xF0->0x4FC  -  Referenced in PushMetaTable.
	// size - 0x500
#endif
};

#endif