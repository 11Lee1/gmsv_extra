#include "Interface.h"
#include "../../interfaces.h"
#include "../../Source SDK/server/baseentity.h"
#include "../../Source SDK/eiface.h"
CBaseEntity* CLuaInterface::GetEntity(int iStackPos) {
	if (!g_pInterfaces->g_Lua)
		return nullptr;

	void* userdata = nullptr;
	if (!this->IsType(iStackPos, GarrysMod::Lua::Type::ENTITY) || (userdata = this->GetUserdata(iStackPos), !userdata) || !(*(void**)userdata)) {
		this->Error("Tried to use a NULL Entity!");
		return nullptr;
	}
	int entindex = (**(unsigned int**)userdata) & ENT_ENTRY_MASK;
	if (entindex >= 0xFFFF)
		return nullptr;

	return (CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
}
void CLuaInterface::PushEntity(CBaseEntity* Entity) {
	if (g_pInterfaces->g_Lua && Entity) {
		Entity->PushEntity();
	}
}