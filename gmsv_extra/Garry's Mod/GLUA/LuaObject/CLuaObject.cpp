#include "CLuaObject.h"
#include "../../../interfaces.h" // interfaces.
#include "../../LUA/Interface.h"
#include "../../../Source SDK/tier1/strtools.h"
namespace GarrysMod
{
	namespace Lua
	{
		CLuaObject::CLuaObject() {
			this->m_bUserData = 0;
			this->m_iLUA_TYPE = -1;
			this->m_iref = -1;
			this->m_pLua = g_pInterfaces->g_Lua;
		}
		CLuaObject::CLuaObject(int i0, int i1) {
			this->m_bUserData = 0;
			this->m_iLUA_TYPE = -1;
			this->m_iref = -1;
			this->m_pLua = g_pInterfaces->g_Lua;
			this->SetReference(i0);
			if (g_pInterfaces->g_Lua) {
				if (i1 != -1 && i1 != this->m_iLUA_TYPE) {
					// char buffer[0x100] = { };
					// unexpected type.
				}
			}
		}
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
			this->SetReference(pos);
		}
		void CLuaObject::UnReference() {
			if (this->m_iref != -1){
				CLuaInterface* lua = this->m_pLua;
				if (g_pInterfaces->g_Lua == lua) {
					if (lua)
						g_pInterfaces->g_Lua->ReferenceFree(m_iref);
				}
			}
			this->m_bUserData = 0;
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

			this->Push();
			void* UserdataOut = g_pInterfaces->g_Lua->GetUserdata(-1);
			g_pInterfaces->g_Lua->Pop(1);
			return UserdataOut;
		}
		void CLuaObject::SetMember_0(char const* name) {
			g_pInterfaces->g_Lua->SetMember(this, name);
		}
		void CLuaObject::SetMember_1(float fl, CFunc Fn) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushLuaFunction(Fn);
				g_pInterfaces->g_Lua->SetMember(this, fl);
			}
		}
		void CLuaObject::SetMember_2(float fl, char const* name) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushString(name);
				g_pInterfaces->g_Lua->SetMember(this, fl);
			}
		}
		void CLuaObject::SetMember_3(float fl, bool Bool) { 
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushBool(Bool);
				this->SetMember_6(fl);
			}
		}
		void CLuaObject::SetMember_4(float fl1, float fl2) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushNumber(fl2);
				this->SetMember_6(fl1);
			}
		}
		void CLuaObject::SetMember_5(float fl, ILuaObject* pObject) {
			g_pInterfaces->g_Lua->SetMember(this, fl, pObject);
		}
		void CLuaObject::SetMember_6(float fl) {
			g_pInterfaces->g_Lua->SetMember(this, fl);
		}
		void CLuaObject::SetMember_7(char const* name, CFunc Fn) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushLuaFunction(Fn);
				g_pInterfaces->g_Lua->SetMember(this, name);
			}
		}
		void CLuaObject::SetMember_8(char const* name1, char const* name2) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushString(name2, 0);
				g_pInterfaces->g_Lua->SetMember(this, name1);
			}
		}
		void CLuaObject::SetMember_9(char const* name, bool Bool) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushBool(Bool);
				this->SetMember_0(name);
			}
		}
		void CLuaObject::SetMember_A(char const* name, float fl) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushNumber(fl);
				this->SetMember_0(name);
			}
		}
		
		void CLuaObject::SetMember_B(ILuaObject* pObject1, ILuaObject* pObject2) {
			/*

				finish me.

				.text:000B5390 arg_0           = dword ptr  8
				.text:000B5390 arg_4           = dword ptr  0Ch
				.text:000B5390                 push    ebp
				.text:000B5391                 mov     ebp, esp
				.text:000B5393                 push    [ebp+arg_4]
				.text:000B5396                 mov     edx, ecx
				.text:000B5398                 mov     ecx, g_Lua
				.text:000B539E                 push    [ebp+arg_0]
				.text:000B53A1                 push    edx
				.text:000B53A2                 mov     eax, [ecx]
				.text:000B53A4                 call    dword ptr [eax+140h]
				.text:000B53AA                 pop     ebp
				.text:000B53AB                 retn    8
			*/
		}
		void CLuaObject::SetMember_C(char const* name, ILuaObject* pObject) {
			g_pInterfaces->g_Lua->SetMember(this, name, pObject);
		}
		bool CLuaObject::GetMemberBool(char const* name , bool ret) {
			if (!this->IsTable() || this->m_iLUA_TYPE != Type::TABLE /*ugh? garry u okay bro?*/) 
				return ret;

			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isbool = g_pInterfaces->g_Lua->GetType(-1) == Type::BOOL;
			if (!isbool) {
				g_pInterfaces->g_Lua->Pop(2);
				return ret;
			}
			bool out = g_pInterfaces->g_Lua->GetBool(-1);
			g_pInterfaces->g_Lua->Pop(2);
			return out;
		}  
		int CLuaObject::GetMemberInt(char const* name, int ret) {
			if (!this->IsTable())
				return ret;

			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isnumber = g_pInterfaces->g_Lua->GetType(-1) == Type::NUMBER;
			if (!isnumber) {
				g_pInterfaces->g_Lua->Pop(2);
				return ret;
			}
			double out = g_pInterfaces->g_Lua->GetNumber(-1);
			out = floor(out);
			g_pInterfaces->g_Lua->Pop(2);
			return out;
		}   
		float CLuaObject::GetMemberFloat(char const* name, float ret) {
			if (!this->IsTable())
				return ret;

			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isnumber = g_pInterfaces->g_Lua->GetType(-1) == Type::NUMBER;
			if (!isnumber) {
				g_pInterfaces->g_Lua->Pop(2);
				return ret;
			}
			double out = g_pInterfaces->g_Lua->GetNumber(-1);
			g_pInterfaces->g_Lua->Pop(2);
			return out;
		}  
		char const* CLuaObject::GetMemberStr_0(float fl, char const* ret) {
			if (!this->IsTable())
				return ret;

			this->Push();
			g_pInterfaces->g_Lua->PushNumber(fl);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isstring = g_pInterfaces->g_Lua->GetType(-1) == Type::STRING;
			if (!isstring) {
				g_pInterfaces->g_Lua->Pop(2);
				return ret;
			}
			char const* out = g_pInterfaces->g_Lua->GetString(-1,0);
			g_pInterfaces->g_Lua->Pop(2);
			return out;
		}   
		char const* CLuaObject::GetMemberStr_1(char const* name1, char const* ret) {
			if (this->IsTable()) {
				this->Push();
				g_pInterfaces->g_Lua->PushString(name1, 0);
				g_pInterfaces->g_Lua->GetTable(-2);
				bool isstring = g_pInterfaces->g_Lua->GetType(-1) == Type::STRING;
				if (isstring) {
					char const* out = g_pInterfaces->g_Lua->GetString(-1, 0);
					g_pInterfaces->g_Lua->Pop(2);
					return out;
				}
				else {
					g_pInterfaces->g_Lua->Pop(2);
					return ret;
				}
			}
			else
				return "";
		}  
		void* CLuaObject::GetMemberUserData_0(float fl, void* userdata) {
			if (!this->IsTable())
				return userdata;

			this->Push();
			g_pInterfaces->g_Lua->PushNumber(fl);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isuserdata = g_pInterfaces->g_Lua->isUserData(-1);
			if (isuserdata) {
				g_pInterfaces->g_Lua->Pop(2);
				return userdata;
			}
			unsigned int udata = (unsigned int)g_pInterfaces->g_Lua->GetUserdata(-1);
			g_pInterfaces->g_Lua->Pop(2);
			if (*(BYTE*)(udata + 4) == 9 && !*(unsigned int*)udata)
				return userdata;

			return (void*)udata;
		}  
		void* CLuaObject::GetMemberUserData_1(char const* name, void* userdata) {
			if (!this->IsTable())
				return userdata;

			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			bool isuserdata = g_pInterfaces->g_Lua->isUserData(-1);
			if (isuserdata) {
				g_pInterfaces->g_Lua->Pop(2);
				return userdata;
			}
			unsigned int udata = (unsigned int)g_pInterfaces->g_Lua->GetUserdata(-1);
			g_pInterfaces->g_Lua->Pop(2);
			if (*(BYTE*)(udata + 4) == 9 && !*(unsigned int*)udata)
				return userdata;

			return (void*)udata;
		}  
		ILuaObject* CLuaObject::GetMember_0(ILuaObject* pObject) {
			/*

				finish me.

			*/

			return nullptr;
		}  
		ILuaObject* CLuaObject::GetMember_1(ILuaObject* object, char const*) {
			/*

				finish me.

			*/
			return nullptr;
		}  
		void CLuaObject::GetMember_2(char const* name, ILuaObject* object) {
			if (this->IsTable()) {
				this->Push();
				g_pInterfaces->g_Lua->PushString(name, 0);
				g_pInterfaces->g_Lua->GetTable(-2);
				object->SetFromStack(-1);
				g_pInterfaces->g_Lua->Pop(2);
			}
			else
				object->UnReference();
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
			return this->m_bUserData;
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
		int CLuaObject::PushMemberFast(int i1) {
			if (!this->IsTable())
				return 0;

			this->Push();
			g_pInterfaces->g_Lua->Push(i1);
			g_pInterfaces->g_Lua->GetTable(-2);
			if (g_pInterfaces->g_Lua->IsType(-1, 0)) {
				g_pInterfaces->g_Lua->Pop(1);
				return 0;
			}
			return 1;
		}
		void CLuaObject::SetMemberFast(int i1, int i2) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->SetMemberFast(this, i1, i2);
			}
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
		void CLuaObject::SetMember_FixKey_0(char const*, int) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey_1(char const*, double) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey_2(char const*, char const*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey_3(char const*, ILuaObject*) {
			/*

				finish me.

			*/
		}
		void CLuaObject::SetMember_FixKey_4(char const*, float) {
			/*

				finish me.

			*/
		}
		bool CLuaObject::IsBool() {
			if (!g_pInterfaces->g_Lua)
				return false;

			return m_iLUA_TYPE == Type::BOOL;
		}
		void CLuaObject::SetMemberDouble_0(char const* name, double val) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushNumber(val);
				this->SetMember_0(name);
			}
		}
		void CLuaObject::SetMemberNil_0(float val) {
			g_pInterfaces->g_Lua->PushNil();
			this->SetMember_6(val);
		}
		void CLuaObject::SetMemberNil_1(char const* name) {
			g_pInterfaces->g_Lua->PushNil();
			this->SetMember_0(name);
		}
		bool CLuaObject::Debug_IsUnreferenced() {
			return this->m_iref == -1;
		}
		void CLuaObject::Init() {
			this->m_bUserData = 0;
			this->m_iLUA_TYPE = -1;
			this->m_iref = -1;
			this->m_pLua = g_pInterfaces->g_Lua;
		}
		void CLuaObject::SetFromGlobal(char const* name) {
			CLuaObject* global = g_pInterfaces->g_Lua->Global();
			global->GetMember_2(name, this);
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
		void CLuaObject::SetMember_D(char const* name , unsigned long ul) {
			char buffer[256] = {};
			if (this->IsTable()) {
				V_snprintf(buffer, 256, "%llu", name, ul);
				g_pInterfaces->g_Lua->PushString(buffer, 0);
				g_pInterfaces->g_Lua->SetMember(this, name);
			}
		}
		void CLuaObject::SetReference(int val) {
			this->UnReference();
			this->m_bUserData = g_pInterfaces->g_Lua->isUserData(val);
			this->m_iLUA_TYPE = g_pInterfaces->g_Lua->GetType(val);
			this->m_pLua = g_pInterfaces->g_Lua;

			bool TypeIsNil = this->m_iLUA_TYPE == Type::NIL;
			if (TypeIsNil)
				g_pInterfaces->g_Lua->PushNil();
			else
				g_pInterfaces->g_Lua->Push(val);

			this->m_iref = g_pInterfaces->g_Lua->ReferenceCreate();
		}
		void CLuaObject::RemoveMember_0(float fl) {
			g_pInterfaces->g_Lua->PushNil();
			g_pInterfaces->g_Lua->SetMember(this, fl);
		}
		void CLuaObject::RemoveMember_1(char const* name) {
			g_pInterfaces->g_Lua->PushNil();
			g_pInterfaces->g_Lua->SetMember(this, name);
		}
		bool CLuaObject::MemberIsNil(char const* name) {
			this->Push();
			g_pInterfaces->g_Lua->PushString(name, 0);
			g_pInterfaces->g_Lua->GetTable(-2);
			int type = g_pInterfaces->g_Lua->GetType(-1);
			g_pInterfaces->g_Lua->Pop(2);
			return type == GarrysMod::Lua::Type::NIL;
		} 
		void CLuaObject::SetMemberDouble_1(float flt, double val) {
			if (this->IsTable()) {
				g_pInterfaces->g_Lua->PushNumber(val);
				this->SetMember_6(flt);
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

		void CLuaObject::SetBool(bool val) {
			g_pInterfaces->g_Lua->PushBool(val);
			this->SetFromStack(-1);
			g_pInterfaces->g_Lua->Pop(1);
		}
	};
};