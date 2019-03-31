#include "CLuaObject.h"
#include "../../../interfaces.h" // interfaces.
#include "../../../Garry's Mod/LUA/LuaBase.h"

namespace GarrysMod
{
	namespace Lua
	{
		void CLuaObject::Set(ILuaObject* pObject) {
			if (pObject) {
				pObject->Push();
				this->SetFromStack(-1);
				g_pInterfaces->g_Lua->Pop(1);
			}
			else
				this->UnReference();
		}
		void CLuaObject::SetFromStack(int pos) {
			this->RemoveMember(pos);
		}
		void CLuaObject::UnReference() {
			if (this->m_iref != -1){
				ILuaBase* lua = this->m_pLua;
				if (g_pInterfaces->g_Lua == lua) {
					if (lua)
						g_pInterfaces->g_Lua->ReferenceFree(m_iref);
				}
			}
			this->dontknow = 0;
			this->m_iLUA_TYPE = -1;
			this->m_iref = -1;
		}
		int	CLuaObject::GetType() { 
			return m_iLUA_TYPE;
		}
		char const*	CLuaObject::GetString() {
			this->Push();
			char const* str = g_pInterfaces->g_Lua->GetString(-1, 0);
			g_pInterfaces->g_Lua->Pop(1);
			return str;
		}
		float CLuaObject::GetFloat() {
			if (!this->IsNumber())
				return 0.0f;

			this->Push();
			float out = g_pInterfaces->g_Lua->GetNumber(-1);
			g_pInterfaces->g_Lua->Pop(1);
			return out;
		}
		int	CLuaObject::GetInt() {
			if (!this->IsNumber())
				return 0;

			this->Push();
			double out = g_pInterfaces->g_Lua->GetNumber(-1);
			g_pInterfaces->g_Lua->Pop(1);
			return floor(out);
		}
		void* CLuaObject::GetUserData() {
			if (!this->IsUserData())
				return nullptr;

		}
		void CLuaObject::SetMember(char const*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(float, CFunc Fn) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(float, char const*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(float, bool) { 
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(float, float) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(float, ILuaObject* pObject) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(float) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(char const*, CFunc Fn) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(char const*, char const*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(char const*, bool) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(char const*, float) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(ILuaObject* pObject1, ILuaObject* pObject2) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember(char const*, ILuaObject* pObject) {
			/*

				finish me.

			*/
		}
		bool CLuaObject::GetMemberBool(char const*, bool) {
			/*

				finish me.

			*/
			return 0; 
		}  
		int CLuaObject::GetMemberInt(char const*, int) {
			/*

				finish me.

			*/
			return 0;
		}   
		float CLuaObject::GetMemberFloat(char const*, float) {
			/*

				finish me.

			*/
			return 0;
		}  
		char const* CLuaObject::GetMemberStr(float, char const*) {
			/*

				finish me.

			*/
			return nullptr;
		}   
		char const* CLuaObject::GetMemberStr(char const*, char const*) {
			/*

				finish me.

			*/
			return nullptr;
		}  
		void* CLuaObject::GetMemberUserData(float, void*) {
			/*

				finish me.

			*/
			return nullptr;
		}  
		void* CLuaObject::GetMemberUserData(char const*, void*) {
			/*

				finish me.

			*/
			return nullptr;
		}  
		ILuaObject* CLuaObject::GetMember(ILuaObject* pObject) {
			/*

				finish me.

			*/
			return nullptr;
		}  
		ILuaObject* CLuaObject::GetMember(ILuaObject*, char const*) {
			/*

				finish me.

			*/
			return nullptr;
		}  
		ILuaObject* CLuaObject::GetMember(char const* name, ILuaObject* object) {
			/*

				finish me.

			*/
			return nullptr;
		}   
		void CLuaObject::SetMetaTable(ILuaObject* object) {
			this->Push();
			object->Push();
			g_pInterfaces->g_Lua->SetMetaTable(-2);
			g_pInterfaces->g_Lua->Pop(1);
		}
		void CLuaObject::SetUserData(void* data) {
			this->Push();
			int* udata = (int*)g_pInterfaces->g_Lua->GetUserdata(-1);
			if (udata)
				*udata = *(int*)data;

			g_pInterfaces->g_Lua->Pop(1);
		}
		void CLuaObject::Push() {
			if (!g_pInterfaces->g_Lua)
				return;

			if (m_iref == -1)
				return g_pInterfaces->g_Lua->PushNil();

			return g_pInterfaces->g_Lua->ReferencePush(m_iref);
		}
		bool CLuaObject::IsNil() {
			if (!g_pInterfaces->g_Lua || m_iLUA_TYPE == Type::NIL)
				return true;

			return false;
		}
		bool CLuaObject::IsTable() {
			if (!g_pInterfaces->g_Lua)
				return false;

			if (m_iLUA_TYPE == Type::TABLE)
				return true;

			return false;
		}
		bool CLuaObject::IsString() {
			if (!g_pInterfaces->g_Lua)
				return false;

			if (m_iLUA_TYPE == Type::STRING)
				return true;

			return false;
		}
		bool CLuaObject::IsNumber() {
			if (!g_pInterfaces->g_Lua)
				return false;

			if (m_iLUA_TYPE == Type::NUMBER)
				return true;

			return false;
		}
		bool CLuaObject::IsFunction() {
			if (!g_pInterfaces->g_Lua)
				return false;

			if (m_iLUA_TYPE == Type::FUNCTION)
				return true;

			return false;
		}
		bool CLuaObject::IsUserData() {
			if (!g_pInterfaces->g_Lua)
				return false;

			if (m_iLUA_TYPE == Type::USERDATA)
				return true;

			return false;
		}
		void CLuaObject::Remove_Me_1(char const*, void*) {
			// does nothing
		}
		bool CLuaObject::GetBool() {
			if (!this->IsBool())
				return false;

			this->Push();
			bool out = g_pInterfaces->g_Lua->GetBool(-1);
			g_pInterfaces->g_Lua->Pop(-1);
			return out;
		}
		void CLuaObject::PushMemberFast(int) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMemberFast(int, int) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetFloat(float val) {
			g_pInterfaces->g_Lua->PushNumber(val);
			this->SetFromStack(-1);
			g_pInterfaces->g_Lua->Pop(1);
		}
		void CLuaObject::SetString(char const* string) {
			g_pInterfaces->g_Lua->PushString(string);
			this->SetFromStack(-1);
			g_pInterfaces->g_Lua->Pop(1);
		}
		double CLuaObject::GetDouble() {
			if (!this->IsNumber())
				return 0.0;

			this->Push();
			double out = g_pInterfaces->g_Lua->GetNumber(-1);
			g_pInterfaces->g_Lua->Pop(1);
			return out;
		}
		void CLuaObject::SetMember_FixKey(char const*, int) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey(char const*, double) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey(char const*, char const*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey(char const*, ILuaObject*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey(char const*, float) {
			/*

				finish me.

			*/
		}
		bool CLuaObject::IsBool() {
			if (!g_pInterfaces->g_Lua)
				return false;

			return m_iLUA_TYPE == Type::BOOL;
		}
		void CLuaObject::SetMemberDouble(char const* name, double val) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushNumber(val);
				this->SetMember(name);
			}
		}
		void CLuaObject::SetMemberNil(float val) {
			g_pInterfaces->g_Lua->PushNil();
			this->SetMember(val);
		}
		void CLuaObject::SetMemberNil(char const* name) {
			/*

				finish me.

			*/
		}
		bool CLuaObject::Debug_IsUnreferenced() {
			return this->m_iref == -1;
		}
		void CLuaObject::Init() {
			this->dontknow = 0;
			this->m_iLUA_TYPE = -1;
			this->m_iref = -1;
			this->m_pLua = g_pInterfaces->g_Lua;
		}
		void CLuaObject::SetFromGlobal(char const*) {
			/*

				finish me.

			*/
		}
		int CLuaObject::GetStringLen(unsigned int* len) {
			this->Push();
			g_pInterfaces->g_Lua->GetString(-1, len);
			g_pInterfaces->g_Lua->Pop(1);
			return *len;
		}
		unsigned int CLuaObject::GetMemberUInt(char const* name, unsigned int val) {
			if (!this->IsTable())
				return val;

			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isnumber = g_pInterfaces->g_Lua->GetType(-1) == GarrysMod::Lua::Type::NUMBER;
			if (!isnumber) {
				g_pInterfaces->g_Lua->Pop(2);
				return val;
			}
			val = g_pInterfaces->g_Lua->GetNumber(-1);
			g_pInterfaces->g_Lua->Pop(2);
			return val;
		}
		void CLuaObject::SetMember(char const*, unsigned long) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetReference(int val) {
			/*

				finish me.

			*/
		}
		void CLuaObject::RemoveMember(float) {
			/*

				finish me.

			*/
		}
		void CLuaObject::RemoveMember(char const* name) {
			/*
			
				finish me.
			
			*/
		}
		bool CLuaObject::MemberIsNil(char const* name) {
			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			int type = g_pInterfaces->g_Lua->GetType(-1);
			g_pInterfaces->g_Lua->Pop(2);
			return type == GarrysMod::Lua::Type::NIL;
		} 
		void CLuaObject::SetMemberDouble(float flt, double val) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushNumber(val);
				this->SetMember(flt);
			}
		}
		double CLuaObject::GetMemberDouble(char const* name , double val = 0) {
			if (this->IsTable()) {
				this->Push();
				g_pInterfaces->g_Lua->PushString(name, 0);
				g_pInterfaces->g_Lua->GetTable(-2);
				if (g_pInterfaces->g_Lua->GetType(-1) == GarrysMod::Lua::Type::NUMBER) {
					val = g_pInterfaces->g_Lua->GetNumber(-1);
				}
				g_pInterfaces->g_Lua->Pop(2);
			}
			return val; 
		}
	};
};