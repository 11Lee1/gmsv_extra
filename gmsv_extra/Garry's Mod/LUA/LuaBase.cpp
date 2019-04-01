#include "LuaBase.h"
#include "../../interfaces.h"
#include "../../Source SDK/basehandle.h"
namespace GarrysMod
{
	namespace Lua
	{
		CBaseEntity* ILuaBase::GetEntity(int iStackPos) {
			if (!g_pInterfaces->g_Lua)
				return nullptr;

			void* userdata = nullptr;
			if (!this->IsType(iStackPos, Type::ENTITY) || (userdata = this->GetUserdata(iStackPos), !userdata) || !(*(void**)userdata)) {
				this->Error("Tried to use a NULL Entity!");
				return nullptr;
			}
			int entindex = (**(unsigned int**)userdata) & ENT_ENTRY_MASK;
			if (entindex >= 0xFFFF)
				return nullptr;

			return (CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
		}
		void ILuaBase::PushEntity(CBaseEntity* Entity) {
			if (g_pInterfaces->g_Lua && Entity) {
				Entity->PushEntity();
			}
		}
		void ILuaBase::PushVector(Vector const* vec) {
			if (g_pInterfaces->g_Lua) {
				unsigned int newuserdata = (unsigned int)g_pInterfaces->g_Lua->NewUserdata(20);
				*(BYTE*)(newuserdata + 4) = Type::VECTOR;
				*(unsigned int*)newuserdata = newuserdata + 8;
				if (g_pInterfaces->g_Lua->PushMetaTable(Type::VECTOR))
					g_pInterfaces->g_Lua->SetMetaTable(-2);

				**(float**)(newuserdata) = vec->x;
				**(float**)(newuserdata + 4) = vec->y;
				**(float**)(newuserdata + 8) = vec->z;
			}
		}
		void ILuaBase::PushAngle(QAngle const* ang) {
			if (g_pInterfaces->g_Lua) {
				unsigned int newuserdata = (unsigned int)g_pInterfaces->g_Lua->NewUserdata(20);
				*(BYTE*)(newuserdata + 4) = Type::ANGLE;
				*(unsigned int*)newuserdata = newuserdata + 8;
				if (g_pInterfaces->g_Lua->PushMetaTable(Type::ANGLE))
					g_pInterfaces->g_Lua->SetMetaTable(-2);

				**(float**)(newuserdata) = ang->x;
				**(float**)(newuserdata + 4) = ang->y;
				**(float**)(newuserdata + 8) = ang->z;
			}
		}
	};
};