#include "CLuaGameObject.h"
#include "../../../interfaces.h" // interfaces.
namespace GarrysMod
{
	namespace Lua
	{
		CBaseEntity* CLuaGameObject::GetMemberEntity(char const*, CBaseEntity*) {
			return nullptr;
		}
		void CLuaGameObject::SetMemberEntity(char const*, CBaseEntity*) {
		
		}
		void CLuaGameObject::SetMemberEntity(float, CBaseEntity*) {
		
		}
		bool CLuaGameObject::IsEntity() { 
			return false;
		}
		CBaseEntity* CLuaGameObject::GetEntity() { 
			return nullptr;
		}
		void CLuaGameObject::SetEntity(CBaseEntity*) {
		
		}
		void CLuaGameObject::SetMemberVector(float, Vector*) {
		
		}
		void CLuaGameObject::SetMemberVector(char const*, Vector&) {
		
		}
		void CLuaGameObject::SetMemberVector(char const*, Vector*) {
		
		}
		Vector CLuaGameObject::GetMemberVector(int) { 
			return Vector(0, 0, 0);
		}
		Vector CLuaGameObject::GetMemberVector(char const*, Vector*) { 
			return Vector(0, 0, 0);
		}
		Vector CLuaGameObject::GetVector() { 
			return Vector(0, 0, 0);
		}
		bool CLuaGameObject::IsVector() { 
			return false;
		}
		void CLuaGameObject::SetMemberAngle(char const*, QAngle*) {
		
		}
		QAngle CLuaGameObject::GetMemberAngle(char const*, QAngle*) { 
			return QAngle(0, 0, 0);
		}
		QAngle CLuaGameObject::GetAngle() { 
			return QAngle(0, 0, 0);
		}
		bool CLuaGameObject::IsAngle() { 
			return false;
		}
	};
};