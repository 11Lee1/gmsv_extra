#ifndef CLUAOBJECT_H
#define CLUAOBJECT_H

#include "../../../Source SDK/mathlib/mathlib.h"
#include "ILuaObject.h"
class CBaseEntity;
namespace GarrysMod
{
	namespace Lua
	{
		class ILuaBase;
		class CLuaObject : public ILuaObject
		{
		public:
			CLuaObject();
			CLuaObject(int, int);
			/*
				Compiler memes not keeping the specific order feelsbad
			*/
			/*0 - 0*/virtual void				Set(ILuaObject* pObject);
			/*1 - 0*/virtual void				SetFromStack(int pos);
			/*2 - 0*/virtual void				UnReference();
			/*3 - 0*/virtual int				GetType();
			/*4 - 0*/virtual char const*		GetString();
			/*5 - 0*/virtual float				GetFloat();
			/*6 - 0*/virtual int				GetInt();
			/*7 - 0*/virtual void*				GetUserData();
			/*8 - 0*/virtual void				SetMember_0(char const*);
			/*9 - 0*/virtual void				SetMember_1(float, CFunc Fn);
			/*10 - 0*/virtual void				SetMember_2(float, char const*);
			/*11 - 0*/virtual void				SetMember_3(float, bool);
			/*12 - 0*/virtual void				SetMember_4(float, float);
			/*13 - 0*/virtual void				SetMember_5(float, ILuaObject* pObject);
			/*14 - 0*/virtual void				SetMember_6(float);
			/*15 - 0*/virtual void				SetMember_7(char const*, CFunc Fn);
			/*16 - 0*/virtual void				SetMember_8(char const*, char const*);
			/*17 - 0*/virtual void				SetMember_9(char const*, bool);
			/*18 - 0*/virtual void				SetMember_A(char const*, float);
			/*19 - 0*/virtual void				SetMember_B(ILuaObject* pObject1, ILuaObject* pObject2);
			/*20 - 0*/virtual void				SetMember_C(char const*, ILuaObject* pObject);
			/*21 - 0*/virtual bool				GetMemberBool(char const*, bool);
			/*22 - 0*/virtual int				GetMemberInt(char const*, int);
			/*23 - 0*/virtual float				GetMemberFloat(char const*, float);
			/*24 - 0*/virtual char const*		GetMemberStr_0(float, char const*);
			/*25 - 0*/virtual char const*		GetMemberStr_1(char const*, char const*);
			/*26 - 0*/virtual void*				GetMemberUserData_0(float, void*);
			/*27 - 0*/virtual void*				GetMemberUserData_1(char const*, void*);
			/*28 - 0*/virtual ILuaObject*		GetMember_0(ILuaObject* pObject);
			/*29 - 0*/virtual ILuaObject*		GetMember_1(ILuaObject*, char const*);
			/*30 - 0*/virtual void				GetMember_2(char const*, ILuaObject*);
			/*31 - 0*/virtual void				SetMetaTable(ILuaObject*);
			/*32 - 0*/virtual void				SetUserData(void*);
			/*33 - 0*/virtual void				Push();
			/*34 - 0*/virtual bool				IsNil();
			/*35 - 0*/virtual bool				IsTable();
			/*36 - 0*/virtual bool				IsString();
			/*37 - 0*/virtual bool				IsNumber();
			/*38 - 0*/virtual bool				IsFunction();
			/*39 - 0*/virtual bool				IsUserData();
			/*40 - 0*/virtual void				Remove_Me_1(char const*, void*); // actual name ;
			/*41 - 0*/virtual bool				GetBool();
			/*42 - 0*/virtual int				PushMemberFast(int);
			/*43 - 0*/virtual void				SetMemberFast(int, int);
			/*44 - 0*/virtual void				SetFloat(float);
			/*45 - 0*/virtual void				SetString(char const*);
			/*46 - 0*/virtual double			GetDouble();
			/*47 - 0*/virtual void				SetMember_FixKey_0(char const*, int);
			/*48 - 0*/virtual void				SetMember_FixKey_1(char const*, double);
			/*49 - 0*/virtual void				SetMember_FixKey_2(char const*, char const*);
			/*50 - 0*/virtual void				SetMember_FixKey_3(char const*, ILuaObject*);
			/*51 - 0*/virtual void				SetMember_FixKey_4(char const*, float);
			/*52 - 0*/virtual bool				IsBool();
			/*53 - 0*/virtual void				SetMemberDouble_0(char const*, double);
			/*54 - 0*/virtual void				SetMemberNil_0(float);
			/*55 - 0*/virtual void				SetMemberNil_1(char const*);
			/*56 - 0*/virtual bool				Debug_IsUnreferenced();
			/*57 - 0*/virtual void				Init();
			/*58 - 0*/virtual void				SetFromGlobal(char const*);
			/*59 - 0*/virtual int				GetStringLen(unsigned int*);
			/*60 - 0*/virtual unsigned int		GetMemberUInt(char const*, unsigned int);
			/*61 - 0*/virtual void				SetMember_D(char const*, unsigned long);
			/*62 - 0*/virtual void				SetReference(int);
			/*63 - 0*/virtual void				RemoveMember_0(float);
			/*64 - 0*/virtual void				RemoveMember_1(char const*);
			/*65 - 0*/virtual bool				MemberIsNil(char const*);
			/*66 - 0*/virtual void				SetMemberDouble_1(float, double);
			/*67 - 0*/virtual double			GetMemberDouble(char const*, double);
		public:
			bool		dontknow;
			int			m_iLUA_TYPE;		// lua type, string, number, vector, etc.
			int			m_iref;				// ref, for reference push etc.
			ILuaBase*	m_pLua;				// dont use this for function overrides, you WILL crash if not now eventually.
		};
	};
};

#endif