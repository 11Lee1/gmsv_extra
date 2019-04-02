#include "LuaNetworkedVars.h"
#include "LuaObject/CLuaGameObject.h"

bool CLuaNetworkedVars::GetNetworkedVar(CBaseEntity* Ent, char const* VarName, int type, CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t &Element) {
	if (!Ent)
		return false;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	if (entindex >= ENT_ENTRY_MASK)
		return false;
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != type)
			continue;

		if (!V_stricmp(Element.key, VarName))
			return true;
	}
	return false;
}
bool CLuaNetworkedVars::GetNWBool(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return false;

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::BOOL, Element))
		return Element.elem.m_LuaGameObject.GetBool();

	return false;
}
int CLuaNetworkedVars::GetNWInt(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return 0;

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::NUMBER, Element))
		return Element.elem.m_LuaGameObject.GetInt();

	return 0;
}
float CLuaNetworkedVars::GetNWFloat(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return 0.f;

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::NUMBER, Element))
		return Element.elem.m_LuaGameObject.GetFloat();

	return 0.f;
}
char const* CLuaNetworkedVars::GetNWString(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return "";

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::STRING, Element))
		return Element.elem.m_LuaGameObject.GetString();

	return "";
}
CBaseEntity* CLuaNetworkedVars::GetNWEntity(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return nullptr;

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::ENTITY, Element))
		return Element.elem.m_LuaGameObject.GetEntity();

	return nullptr;
}
Vector CLuaNetworkedVars::GetNWVector(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return vec3_origin;

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::VECTOR, Element))
		return Element.elem.m_LuaGameObject.GetVector();

	return vec3_origin;
}
QAngle CLuaNetworkedVars::GetNWAngle(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return vec3_angle;

	CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element;
	if (GetNetworkedVar(Ent, VarName, GarrysMod::Lua::Type::ANGLE, Element))
		return Element.elem.m_LuaGameObject.GetAngle();

	return vec3_angle;
}