#include "CLuaGameObject.h"
#include "../../../Garry's Mod/LUA/LuaBase.h"
#include "../../../interfaces.h" // interfaces.
#include "../../../Source SDK/eiface.h"
namespace GarrysMod
{
	namespace Lua
	{
		CBaseEntity* CLuaGameObject::GetMemberEntity(char const* name, CBaseEntity* ret) {
			if (!this->IsTable())
				return nullptr;

			void* userdata = this->GetMemberUserData(name, nullptr);
			if (!userdata)
				return ret;

			int entindex = (**(unsigned int**)userdata) & ENT_ENTRY_MASK;
			if (entindex >= 0xFFFF)
				return nullptr;

			return (CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
		}
		void CLuaGameObject::SetMemberEntity(char const* name, CBaseEntity* pEnt) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushEntity(pEnt);
				g_pInterfaces->g_Lua->SetMember(this, name);
			}
		}
		void CLuaGameObject::SetMemberEntity(float fl, CBaseEntity* pEnt) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushEntity(pEnt);
				g_pInterfaces->g_Lua->SetMember(this, fl);
			}
		}
		bool CLuaGameObject::IsEntity() { 
			return this->GetType() == Type::ENTITY;
		}
		CBaseEntity* CLuaGameObject::GetEntity() { 
			void* userdata = this->GetUserData();
			unsigned int data;
			if (userdata && (data = **(unsigned int**)userdata, data != -1)) {
				int entindex = data & ENT_ENTRY_MASK;
				if (entindex >= 0xFFFF)
					return nullptr;

				return (CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
			}
			return nullptr;
		}
		void CLuaGameObject::SetEntity(CBaseEntity* pEnt) {
			g_pInterfaces->g_Lua->PushEntity(pEnt);
			this->SetFromStack(-1);
			g_pInterfaces->g_Lua->Pop(1);
		}
		void CLuaGameObject::SetMemberVector(float fl, Vector* vec) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushVector(vec);
				g_pInterfaces->g_Lua->SetMember(this, fl);
			}
		}
		void CLuaGameObject::SetMemberVector(char const* name, Vector& vec) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushVector(vec);
				g_pInterfaces->g_Lua->SetMember(this, name);
			}
		}
		void CLuaGameObject::SetMemberVector(char const* name, Vector* vec) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushVector(vec);
				g_pInterfaces->g_Lua->SetMember(this, name);
			}
		}
		Vector& CLuaGameObject::GetMemberVector(int i1) { 
			Vector* out = &Vector(0,0,0);
			return *(Vector*)this->GetMemberUserData((float)i1, out);
		}
		Vector& CLuaGameObject::GetMemberVector(char const* name, Vector* ret) { 
			Vector* out = ret;
			return *(Vector*)this->GetMemberUserData(name, out);
		}
		Vector& CLuaGameObject::GetVector() { 
			return *(Vector*)this->GetUserData();
		}
		bool CLuaGameObject::IsVector() { 
			return this->GetType() == Type::VECTOR;
		}
		void CLuaGameObject::SetMemberAngle(char const* name, QAngle* ang) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushAngle(ang);
				g_pInterfaces->g_Lua->SetMember(this, name);
			}
		}
		QAngle& CLuaGameObject::GetMemberAngle(char const* name, QAngle* ret) { 
			QAngle* out = ret;
			return *(QAngle*)this->GetMemberUserData(name, out);
		}
		QAngle& CLuaGameObject::GetAngle() { 
			return *(QAngle*)this->GetUserData();
		}
		bool CLuaGameObject::IsAngle() { 
			return this->GetType() == Type::ANGLE;
		}
	};
};