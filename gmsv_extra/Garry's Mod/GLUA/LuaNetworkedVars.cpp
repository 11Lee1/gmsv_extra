#include "LuaNetworkedVars.h"
#include "LuaObject/CLuaGameObject.h"

int CLuaNetworkedVars::FindNetWorkedVar(CBaseEntity* Ent, char const* Key, int TypeID, bool CreateNewIfNotFound) {
	if (!Ent)
		return -1;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();


	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		if (m_Ents[entindex].NetVars[i].elem.m_LuaGameObject.m_iLUA_TYPE != TypeID)
			continue;

		if (V_stricmp(m_Ents[entindex].NetVars[i].key, Key))
			continue;

		return i;
	}
	if (CreateNewIfNotFound) {
		return AddNetworkedVar(Ent, Key);
	}
	return -1;
}

int CLuaNetworkedVars::AddNetworkedVar(CBaseEntity* Ent, char const* Key) {
	if (!Ent)
		return -1;

	LuaNetworkedVar_t netvar;
	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();

	netvar.m_LuaGameObject = GarrysMod::Lua::CLuaGameObject();
	Element.key = Key;
	Element.elem = netvar;

	unsigned short index = m_Ents[entindex].NetVars.Insert(Element);
	m_Ents[entindex].NetVars[index].elem.m_iNetworkStringID = g_pInterfaces->NetworkStringTableContainer()->FindTable("networkstring")->AddString(true, Key); // Use table id instead of comparing all the strings xd
	return index;
}


bool CLuaNetworkedVars::GetNWBool(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::BOOL);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetBool();

	return false;
}
int CLuaNetworkedVars::GetNWInt(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return 0;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::NUMBER);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetInt();

	return 0;
}
float CLuaNetworkedVars::GetNWFloat(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return 0.f;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::NUMBER);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetFloat();

	return 0.f;
}
char const* CLuaNetworkedVars::GetNWString(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return "";

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::STRING);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetString();

	return "";
}
CBaseEntity* CLuaNetworkedVars::GetNWEntity(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return nullptr;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::ENTITY);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetEntity();

	return nullptr;
}
Vector CLuaNetworkedVars::GetNWVector(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return vec3_origin;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::VECTOR);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetVector();

	return vec3_origin;
}
QAngle CLuaNetworkedVars::GetNWAngle(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return vec3_angle;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	unsigned short index = FindNetWorkedVar(Ent, VarName, GarrysMod::Lua::Type::ANGLE);

	if (index != -1)
		return m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.GetAngle();

	return vec3_angle;
}

bool CLuaNetworkedVars::SetNWBool(CBaseEntity* Ent, char const* Key, bool val) {
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	int index = FindNetWorkedVar(Ent, Key, GarrysMod::Lua::Type::BOOL, true);
	if (index != -1) {
		m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.SetBool(val);
		m_Ents[EntIndex].NetVars[index].elem.m_flLastUpdate = 0.0f; // force the var to update on all clients.
		return true;
	}
	return false;
}

bool CLuaNetworkedVars::SetNWInt(CBaseEntity* Ent, char const* Key, int val) {
	return SetNWFloat(Ent, Key, val);
}

bool CLuaNetworkedVars::SetNWFloat(CBaseEntity* Ent, char const* Key, float val) {
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	int index = FindNetWorkedVar(Ent, Key, GarrysMod::Lua::Type::NUMBER, true);
	if (index != -1) {
		m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.SetFloat(val);
		m_Ents[EntIndex].NetVars[index].elem.m_flLastUpdate = 0.0f; // force the var to update on all clients.
		return true;
	}
	return false;
}

bool CLuaNetworkedVars::SetNWString(CBaseEntity* Ent, char const* Key, char const* val) {
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	int index = FindNetWorkedVar(Ent, Key, GarrysMod::Lua::Type::STRING, true);
	if (index != -1) {
		m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.SetString(val);
		m_Ents[EntIndex].NetVars[index].elem.m_flLastUpdate = 0.0f; // force the var to update on all clients.
		return true;
	}
	return false;
}

bool CLuaNetworkedVars::SetNWEntity(CBaseEntity* Ent, char const* Key, CBaseEntity* val) { // fucked.
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	int index = FindNetWorkedVar(Ent, Key, GarrysMod::Lua::Type::ENTITY, true);
	if (index != -1) {
		m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.SetEntity(val);
		m_Ents[EntIndex].NetVars[index].elem.m_flLastUpdate = 0.0f; // force the var to update on all clients.
		return true;
	}
	return false;
}

bool CLuaNetworkedVars::SetNWVector(CBaseEntity* Ent, char const* Key, Vector val) {
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	int index = FindNetWorkedVar(Ent, Key, GarrysMod::Lua::Type::VECTOR, true);
	if (index != -1) {
		m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.SetVector(val);
		m_Ents[EntIndex].NetVars[index].elem.m_flLastUpdate = 0.0f; // force the var to update on all clients.
		return true;
	}
	return false;
}

bool CLuaNetworkedVars::SetNWAngle(CBaseEntity* Ent, char const* Key, QAngle val) {
	if (!Ent)
		return false;

	int EntIndex = Ent->GetRefEHandle().GetEntryIndex();
	int index = FindNetWorkedVar(Ent, Key, GarrysMod::Lua::Type::ANGLE, true);
	if (index != -1) {
		m_Ents[EntIndex].NetVars[index].elem.m_LuaGameObject.SetAngle(val);
		m_Ents[EntIndex].NetVars[index].elem.m_flLastUpdate = 0.0f; // force the var to update on all clients.
		return true;
	}
	return false;
}
