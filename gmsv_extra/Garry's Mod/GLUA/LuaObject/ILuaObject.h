#ifndef ILUAOBJECT_H
#define ILUAOBJECT_H

#include "../../../Source SDK/mathlib/mathlib.h"
struct lua_State;
namespace GarrysMod
{
	namespace Lua
	{
		typedef int(*CFunc) (lua_State *L);
		class ILuaObject
		{
		public:
			/*0 - 0*/virtual void				Set(ILuaObject* pObject) = 0;
			/*1 - 0*/virtual void				SetFromStack(int pos) = 0;
			/*2 - 0*/virtual void				UnReference() = 0;
			/*3 - 0*/virtual int				GetType() = 0;
			/*4 - 0*/virtual char const*		GetString() = 0;
			/*5 - 0*/virtual float				GetFloat() = 0;
			/*6 - 0*/virtual int				GetInt() = 0;
			/*7 - 0*/virtual void*				GetUserData() = 0;
			/*8 - 0*/virtual void				SetMember_0(char const*) = 0;
			/*9 - 0*/virtual void				SetMember_1(float, CFunc Fn) = 0;
			/*10 - 0*/virtual void				SetMember_2(float, char const*) = 0;
			/*11 - 0*/virtual void				SetMember_3(float, bool) = 0;
			/*12 - 0*/virtual void				SetMember_4(float, float) = 0;
			/*13 - 0*/virtual void				SetMember_5(float, ILuaObject* pObject) = 0;
			/*14 - 0*/virtual void				SetMember_6(float) = 0;
			/*15 - 0*/virtual void				SetMember_7(char const*, CFunc Fn) = 0;
			/*16 - 0*/virtual void				SetMember_8(char const*, char const*) = 0;
			/*17 - 0*/virtual void				SetMember_9(char const*, bool) = 0;
			/*18 - 0*/virtual void				SetMember_A(char const*, float) = 0;
			/*19 - 0*/virtual void				SetMember_B(ILuaObject* pObject1, ILuaObject* pObject2) = 0;
			/*20 - 0*/virtual void				SetMember_C(char const*, ILuaObject* pObject) = 0;
			/*21 - 0*/virtual bool				GetMemberBool(char const*, bool) = 0;
			/*22 - 0*/virtual int				GetMemberInt(char const*, int) = 0;
			/*23 - 0*/virtual float				GetMemberFloat(char const*, float) = 0;
			/*24 - 0*/virtual char const*		GetMemberStr_0(float, char const*) = 0;
			/*25 - 0*/virtual char const*		GetMemberStr_1(char const*, char const*) = 0;
			/*26 - 0*/virtual void*				GetMemberUserData_0(float, void*) = 0;
			/*27 - 0*/virtual void*				GetMemberUserData_1(char const*, void*) = 0;
			/*28 - 0*/virtual ILuaObject*		GetMember_0(ILuaObject* pObject) = 0;
			/*29 - 0*/virtual ILuaObject*		GetMember_1(ILuaObject*, char const*) = 0;
			/*30 - 0*/virtual void				GetMember_2(char const*, ILuaObject*) = 0;
			/*31 - 0*/virtual void				SetMetaTable(ILuaObject*) = 0;
			/*32 - 0*/virtual void				SetUserData(void*) = 0;
			/*33 - 0*/virtual void				Push() = 0;
			/*34 - 0*/virtual bool				IsNil() = 0;
			/*35 - 0*/virtual bool				IsTable() = 0;
			/*36 - 0*/virtual bool				IsString() = 0;
			/*37 - 0*/virtual bool				IsNumber() = 0;
			/*38 - 0*/virtual bool				IsFunction() = 0;
			/*39 - 0*/virtual bool				IsUserData() = 0;
			/*40 - 0*/virtual void				Remove_Me_1(char const*, void*) = 0; // actual name
			/*41 - 0*/virtual bool				GetBool() = 0;
			/*42 - 0*/virtual int				PushMemberFast(int) = 0;
			/*43 - 0*/virtual void				SetMemberFast(int, int) = 0;
			/*44 - 0*/virtual void				SetFloat(float) = 0;
			/*45 - 0*/virtual void				SetString(char const*) = 0;
			/*46 - 0*/virtual double			GetDouble() = 0;
			/*47 - 0*/virtual void				SetMember_FixKey_0(char const*, int) = 0;
			/*48 - 0*/virtual void				SetMember_FixKey_1(char const*, double) = 0;
			/*49 - 0*/virtual void				SetMember_FixKey_2(char const*, char const*) = 0;
			/*50 - 0*/virtual void				SetMember_FixKey_3(char const*, ILuaObject*) = 0;
			/*51 - 0*/virtual void				SetMember_FixKey_4(char const*, float) = 0;
			/*52 - 0*/virtual bool				IsBool() = 0;
			/*53 - 0*/virtual void				SetMemberDouble_0(char const*, double) = 0;
			/*54 - 0*/virtual void				SetMemberNil_0(float) = 0;
			/*55 - 0*/virtual void				SetMemberNil_1(char const*) = 0;
			/*56 - 0*/virtual bool				Debug_IsUnreferenced() = 0;
			/*57 - 0*/virtual void				Init() = 0;
			/*58 - 0*/virtual void				SetFromGlobal(char const*) = 0;
			/*59 - 0*/virtual int				GetStringLen(unsigned int*) = 0;
			/*60 - 0*/virtual unsigned int		GetMemberUInt(char const*, unsigned int) = 0;
			/*61 - 0*/virtual void				SetMember_D(char const*, unsigned long) = 0;
			/*62 - 0*/virtual void				SetReference(int) = 0;
			/*63 - 0*/virtual void				RemoveMember_0(float) = 0;
			/*64 - 0*/virtual void				RemoveMember_1(char const*) = 0;
			/*65 - 0*/virtual bool				MemberIsNil(char const*) = 0;
			/*66 - 0*/virtual void				SetMemberDouble_1(float, double) = 0;
			/*67 - 0*/virtual double			GetMemberDouble(char const*, double) = 0;
		};
	};
};
#endif