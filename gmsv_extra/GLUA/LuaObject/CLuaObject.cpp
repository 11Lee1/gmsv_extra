#include "CLuaObject.h"
#include "../../interfaces.h" // interfaces.
namespace GarrysMod
{
	namespace Lua
	{
		void CLuaObject::Set(ILuaObject* pObject) {

		}
		int	CLuaObject::SetFromStack(int pos) {
			return 0;
		}
		void CLuaObject::UnReference() {
		
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
		
		}
		void CLuaObject::SetMember(float, CFunc Fn) {
		
		}
		void CLuaObject::SetMember(float, char const*) {
		
		}
		void CLuaObject::Setmember(float, bool) { 
		
		}
		void CLuaObject::SetMember(float, float) {
		
		}
		void CLuaObject::SetMember(float, ILuaObject* pObject) {
		
		}
		void CLuaObject::SetMember(float) {
		
		}
		void CLuaObject::SetMember(char const*, CFunc Fn) {
		
		}
		void CLuaObject::SetMember(char const*, char const*) {
		
		}
		void CLuaObject::SetMember(char const*, bool) {
		
		}
		void CLuaObject::SetMember(char const*, float) {
		
		}
		void CLuaObject::SetMember(ILuaObject* pObject1, ILuaObject* pObject2) {
		
		}
		void CLuaObject::SetMember(char const*, ILuaObject* pObject) {
		
		}
		bool CLuaObject::GetMemberBool(char const*, bool) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		int CLuaObject::GetMemberInt(char const*, int) {
			return 0;
		}  ///// FINISH!!!!!!!!!!!!!! 
		float CLuaObject::GetMemberFloat(char const*, float) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		char const* CLuaObject::GetMemberStr(float, char const*) {
			return 0;
		}  ///// FINISH!!!!!!!!!!!!!! 
		char const* CLuaObject::GetMemberStr(char const*, char const*) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		void* CLuaObject::GetMemberUserData(float, void*) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		void* CLuaObject::GetMemberUserData(char const*, void*) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		ILuaObject* CLuaObject::GetMember(ILuaObject* pObject) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		ILuaObject* CLuaObject::GetMember(ILuaObject*, char const*) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		ILuaObject* CLuaObject::GetMember(char const*, ILuaObject*) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		void CLuaObject::SetMetaTable(ILuaObject*) {
		
		}
		void CLuaObject::SetUserData(void*) {
		
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
		
		} // actual name
		bool CLuaObject::GetBool() {
			if (!this->IsBool())
				return false;

			this->Push();
			bool out = g_pInterfaces->g_Lua->GetBool(-1);
			g_pInterfaces->g_Lua->Pop(-1);
			return out;
		}
		void CLuaObject::PushMemberFast(int) {
		
		}
		void CLuaObject::SetMemberFast(int, int) {
		
		}
		void CLuaObject::SetFloat(float) {
		
		}
		void CLuaObject::SetString(char const*) {
		
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
		
		}
		void CLuaObject::SetMember_FixKey(char const*, double) {
		
		}
		void CLuaObject::SetMember_FixKey(char const*, char const*) {
		
		}
		void CLuaObject::SetMember_FixKey(char const*, ILuaObject*) {
		
		}
		void CLuaObject::SetMember_FixKey(char const*, float) {
		
		}
		bool CLuaObject::IsBool() {
			if (!g_pInterfaces->g_Lua)
				return false;

			return m_iLUA_TYPE == Type::BOOL;
		}
		void CLuaObject::SetMemberDouble(char const*, double) {
		
		}
		void CLuaObject::SetMemberNil(float) {
		
		}
		void CLuaObject::SetMemberNil(char const*) {
		
		}
		bool CLuaObject::Debug_IsUnreferenced() {
			return 0;
		}  ///// FINISH!!!!!!!!!!!!!! 
		void CLuaObject::Init() {
		
		}
		void CLuaObject::SetFromGlobal(char const*) {
		
		}
		int CLuaObject::GetStringLen(unsigned int* len) {
			this->Push();
			g_pInterfaces->g_Lua->GetString(-1, len);
			g_pInterfaces->g_Lua->Pop(1);
			return *len;
		}
		ILuaObject* CLuaObject::GetMemberUInt(char const*, unsigned int) {
			return 0;
		}  ///// FINISH!!!!!!!!!!!!!! 
		void CLuaObject::SetMember(char const*, unsigned long) {
		
		}
		void CLuaObject::SetReference(int) {
		
		}
		void CLuaObject::RemoveMember(float) {
		
		}
		void CLuaObject::RemoveMember(char const*) {
		
		}
		bool CLuaObject::MemberIsNil(char const*) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
		void CLuaObject::SetMemberDouble(float, double) {
		
		}
		double CLuaObject::GetMemberDouble(char const*, double) {
			return 0; 
		}  ///// FINISH!!!!!!!!!!!!!! 
	};
};