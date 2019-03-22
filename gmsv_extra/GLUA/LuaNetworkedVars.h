#ifndef LUANETWORKEDVARS_H
#define LUANETWORKEDVARS_H

#include "../LUA/LuaInterface.h"
#include "LuaObject/ILuaObject.h"
#include "LuaObject/CLuaObject.h"
#include "LuaObject/CLuaGameObject.h"
#include "../Source SDK/server/baseentity.h"
#include "../Source SDK/tier1/utlrbtree.h"
#include "../Source SDK/tier1/utlmap.h"

class CLuaNetworkedVars
{
public:
	struct LuaNetworkedVar_t
	{
		GarrysMod::Lua::CLuaGameObject m_LuaGameObject;
		BYTE pad_unk00[0x8];
	};

	struct LuaNetworkedVarEnts_t
	{
		CBaseHandle EntityRefHandle;
		CUtlRBTree<CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t, unsigned short, CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::CKeyLess, CUtlMemory<UtlRBTreeNode_t<CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t, unsigned short>, unsigned short>> NetVars;
	};

public:
	// I'd use a template and make all these like accessor functions,
	// but i'd have to do a weird hack for that.
	// fyi these are quite expensive to use if there are many variables set on the entity
	bool		GetNWBool(CBaseEntity* Ent, char const* VarName);
	int			GetNWInt(CBaseEntity* Ent, char const* VarName);
	float		GetNWFloat(CBaseEntity* Ent, char const* VarName);
	char const*	GetNWString(CBaseEntity* Ent, char const* VarName);
	CBaseEntity*GetNWEntity(CBaseEntity* Ent, char const* VarName);
	Vector		GetNWVector(CBaseEntity* Ent, char const* VarName);
	QAngle		GetNWAngle(CBaseEntity* Ent, char const* VarName);
private:
	LuaNetworkedVarEnts_t m_Ents[0xFFFF];
};
#endif