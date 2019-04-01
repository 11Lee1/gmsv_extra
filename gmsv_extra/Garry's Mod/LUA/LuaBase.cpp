#include "LuaBase.h"
#include "../../interfaces.h"
#include "../../Source SDK/basehandle.h"
namespace GarrysMod
{
	namespace Lua
	{
		CBaseEntity* ILuaBase::GetEntity(int iStackPos) {
			void* userdata = nullptr;
			if (!this->IsType(iStackPos, Type::ENTITY) || (userdata = this->GetUserdata(iStackPos), !userdata) || !(*(void**)userdata)) {
				this->Error("Tried to use a NULL Entity!");
				return nullptr;
			}
			int entindex = **(unsigned int**)userdata & ENT_ENTRY_MASK;
			if (entindex >= 0xFFFF)
				return nullptr;

			return (CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
		}
	};
};