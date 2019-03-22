#include "LuaNetworkedVars.h"

bool CLuaNetworkedVars::GetNWBool(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return false;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::BOOL)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetBool();
		}
	}
	return false;
}
int CLuaNetworkedVars::GetNWInt(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return 0;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::NUMBER)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetInt();
		}
	}
	return 0;
}
float CLuaNetworkedVars::GetNWFloat(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return 0.f;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::NUMBER)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetFloat();
		}
	}
	return 0.f;
}
char const* CLuaNetworkedVars::GetNWString(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return "";

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::STRING)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetString();
		}
	}
	return "";
}
CBaseEntity* CLuaNetworkedVars::GetNWEntity(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return nullptr;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::ENTITY)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetEntity();
		}
	}
	return nullptr;
}
Vector CLuaNetworkedVars::GetNWVector(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return vec3_origin;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::VECTOR)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetVector();
		}
	}
	return vec3_origin;
}
QAngle CLuaNetworkedVars::GetNWAngle(CBaseEntity* Ent, char const* VarName) {
	if (!Ent)
		return vec3_angle;

	int entindex = Ent->GetRefEHandle().GetEntryIndex();
	for (int i = 0; i < m_Ents[entindex].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = m_Ents[entindex].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != GarrysMod::Lua::Type::ANGLE)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			return Element.elem.m_LuaGameObject.GetAngle();
		}
	}
	return vec3_angle;
}