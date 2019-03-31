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
			/*0 - 0*/virtual void				Set(ILuaObject* pObject);
			/*1 - 0*/virtual void				SetFromStack(int pos);
			/*1 - 0*/virtual void				UnReference();
			/*1 - 0*/virtual int				GetType();
			/*1 - 0*/virtual char const*		GetString();
			/*1 - 0*/virtual float				GetFloat();
			/*1 - 0*/virtual	int				GetInt();
			/*1 - 0*/virtual void*				GetUserData();
			/*1 - 0*/virtual	void			SetMember(char const*);
			/*1 - 0*/virtual void				SetMember(float, CFunc Fn);
			/*1 - 0*/virtual void				SetMember(float, char const*);
			/*1 - 0*/virtual void				SetMember(float, bool);
			/*1 - 0*/virtual void				SetMember(float, float);
			/*1 - 0*/virtual void				SetMember(float, ILuaObject* pObject);
			/*1 - 0*/virtual void				SetMember(float);
			/*1 - 0*/virtual void				SetMember(char const*, CFunc Fn);
			/*1 - 0*/virtual void				SetMember(char const*, char const*);
			/*1 - 0*/virtual void				SetMember(char const*, bool);
			/*1 - 0*/virtual void				SetMember(char const*, float);
			/*1 - 0*/virtual void				SetMember(ILuaObject* pObject1, ILuaObject* pObject2);
			/*1 - 0*/virtual void				SetMember(char const*, ILuaObject* pObject);
			/*1 - 0*/virtual bool				GetMemberBool(char const*, bool);
			/*1 - 0*/virtual int				GetMemberInt(char const*, int);
			/*1 - 0*/virtual float				GetMemberFloat(char const*, float);
			/*1 - 0*/virtual char const*		GetMemberStr(float, char const*);
			/*1 - 0*/virtual char const*		GetMemberStr(char const*, char const*);
			/*1 - 0*/virtual void*				GetMemberUserData(float, void*);
			/*1 - 0*/virtual void*				GetMemberUserData(char const*, void*);
			/*1 - 0*/virtual ILuaObject*		GetMember(ILuaObject* pObject);
			/*1 - 0*/virtual ILuaObject*		GetMember(ILuaObject*, char const*);
			/*1 - 0*/virtual ILuaObject*		GetMember(char const*, ILuaObject*);
			/*1 - 0*/virtual void				SetMetaTable(ILuaObject*);
			/*1 - 0*/virtual void				SetUserData(void*);
			/*1 - 0*/virtual void				Push();
			/*1 - 0*/virtual bool				IsNil();
			/*1 - 0*/virtual bool				IsTable();
			/*1 - 0*/virtual bool				IsString();
			/*1 - 0*/virtual bool				IsNumber();
			/*1 - 0*/virtual bool				IsFunction();
			/*1 - 0*/virtual bool				IsUserData();
			/*1 - 0*/virtual void				Remove_Me_1(char const*, void*); // actual name ;
			/*1 - 0*/virtual bool				GetBool();
			/*1 - 0*/virtual void				PushMemberFast(int);
			/*1 - 0*/virtual void				SetMemberFast(int, int);
			/*1 - 0*/virtual void				SetFloat(float);
			/*1 - 0*/virtual void				SetString(char const*);
			/*1 - 0*/virtual double				GetDouble();
			/*1 - 0*/virtual void				SetMember_FixKey(char const*, int);
			/*1 - 0*/virtual void				SetMember_FixKey(char const*, double);
			/*1 - 0*/virtual void				SetMember_FixKey(char const*, char const*);
			/*1 - 0*/virtual void				SetMember_FixKey(char const*, ILuaObject*);
			/*1 - 0*/virtual void				SetMember_FixKey(char const*, float);
			/*1 - 0*/virtual bool				IsBool();
			/*1 - 0*/virtual void				SetMemberDouble(char const*, double);
			/*1 - 0*/virtual void				SetMemberNil(float);
			/*1 - 0*/virtual void				SetMemberNil(char const*);
			/*1 - 0*/virtual bool				Debug_IsUnreferenced();
			/*1 - 0*/virtual void				Init();
			/*1 - 0*/virtual void				SetFromGlobal(char const*);
			/*1 - 0*/virtual int				GetStringLen(unsigned int*);
			/*1 - 0*/virtual unsigned int		GetMemberUInt(char const*, unsigned int);
			/*1 - 0*/virtual void				SetMember(char const*, unsigned long);
			/*1 - 0*/virtual void				SetReference(int);
			/*1 - 0*/virtual void				RemoveMember(float);
			/*1 - 0*/virtual void				RemoveMember(char const*);
			/*1 - 0*/virtual bool				MemberIsNil(char const*);
			/*1 - 0*/virtual void				SetMemberDouble(float, double);
			/*1 - 0*/virtual double				GetMemberDouble(char const*, double);
		public:
			bool		dontknow;
			int			m_iLUA_TYPE;		// lua type, string, number, vector, etc.
			int			m_iref;				// ref, for reference push etc.
			ILuaBase*	m_pLua;				// dont use this for function overrides, you WILL crash if not now eventually.
		};
	};
};

#endif