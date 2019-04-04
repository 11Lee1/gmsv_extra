#ifndef LUANETWORKEDVARS_H
#define LUANETWORKEDVARS_H

#include "../LUA/LuaInterface.h"
#include "LuaObject/CLuaGameObject.h"
#include "../../Source SDK/server/baseentity.h"
#include "../../Source SDK/tier1/utlrbtree.h"
#include "../../Source SDK/tier1/utlmap.h"

class CLuaNetworkedVars
{
public:
	struct LuaNetworkedVar_t
	{
		GarrysMod::Lua::CLuaGameObject m_LuaGameObject;
		float m_flLastUpdate	= 0;
		int m_iNetworkStringID	= -1;
	};

	struct LuaNetworkedVarEnts_t
	{
		CBaseHandle EntityRefHandle;
		CUtlRBTree<CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t, unsigned short, CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::CKeyLess, CUtlMemory<UtlRBTreeNode_t<CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t, unsigned short>, unsigned short>> NetVars;
	};

public:
	bool		GetNWBool(CBaseEntity* Ent, char const* VarName);
	int			GetNWInt(CBaseEntity* Ent, char const* VarName);
	float		GetNWFloat(CBaseEntity* Ent, char const* VarName);
	char const*	GetNWString(CBaseEntity* Ent, char const* VarName);
	CBaseEntity*GetNWEntity(CBaseEntity* Ent, char const* VarName);
	Vector		GetNWVector(CBaseEntity* Ent, char const* VarName);
	QAngle		GetNWAngle(CBaseEntity* Ent, char const* VarName);


	bool		SetNWBool(CBaseEntity* Ent, char const* Key, bool val);
	bool		SetNWInt(CBaseEntity* Ent, char const* Key, int val);
	bool		SetNWFloat(CBaseEntity* Ent, char const* key, float val);
	bool		SetNWString(CBaseEntity* Ent, char const* key, char const* string);
	bool		SetNWEntity(CBaseEntity* Ent, char const* Key, CBaseEntity* val);
	bool		SetNWVector(CBaseEntity* Ent, char const* Key, Vector val);
	bool		SetNWAngle(CBaseEntity* Ent, char const* Key, QAngle val);
protected:
	int			FindNetWorkedVar(CBaseEntity* Ent, char const* Key, int TypeID, bool CreateNewIfNotFound = false);
	int			AddNetworkedVar(CBaseEntity* Ent, char const* Key);


	LuaNetworkedVarEnts_t m_Ents[ENT_ENTRY_MASK];
};
#endif