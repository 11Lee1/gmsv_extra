#ifndef CLUAOBJECT_H
#define CLUAOBJECT_H

#include "../../Source SDK/mathlib/mathlib.h"
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
			virtual  ~CLuaObject() {};
			virtual void			Set(ILuaObject* pObject);
			virtual int				SetFromStack(int pos);
			virtual void			UnReference();
			virtual int				GetType();
			virtual char const*		GetString();
			virtual float			GetFloat();
			virtual	int				GetInt();
			virtual void*			GetUserData();
			virtual	void			SetMember(char const*);
			virtual void			SetMember(float, CFunc Fn);
			virtual void			SetMember(float, char const*);
			virtual void			Setmember(float, bool);
			virtual void			SetMember(float, float);
			virtual void			SetMember(float, ILuaObject* pObject);
			virtual void			SetMember(float);
			virtual void			SetMember(char const*, CFunc Fn);
			virtual void			SetMember(char const*, char const*);
			virtual void			SetMember(char const*, bool);
			virtual void			SetMember(char const*, float);
			virtual void			SetMember(ILuaObject* pObject1, ILuaObject* pObject2);
			virtual void			SetMember(char const*, ILuaObject* pObject);
			virtual bool			GetMemberBool(char const*, bool);
			virtual int				GetMemberInt(char const*, int);
			virtual float			GetMemberFloat(char const*, float);
			virtual char const*		GetMemberStr(float, char const*);
			virtual char const*		GetMemberStr(char const*, char const*);
			virtual void*			GetMemberUserData(float, void*);
			virtual void*			GetMemberUserData(char const*, void*);
			virtual ILuaObject*		GetMember(ILuaObject* pObject);
			virtual ILuaObject*		GetMember(ILuaObject*, char const*);
			virtual ILuaObject*		GetMember(char const*, ILuaObject*);
			virtual void			SetMetaTable(ILuaObject*);
			virtual void			SetUserData(void*);
			virtual void			Push();
			virtual bool			IsNil();
			virtual bool			IsTable();
			virtual bool			IsString();
			virtual bool			IsNumber();
			virtual bool			IsFunction();
			virtual bool			IsUserData();
			virtual void			Remove_Me_1(char const*, void*); // actual name ;
			virtual bool			GetBool();
			virtual void			PushMemberFast(int);
			virtual void			SetMemberFast(int, int);
			virtual void			SetFloat(float);
			virtual void			SetString(char const*);
			virtual double			GetDouble();
			virtual void			SetMember_FixKey(char const*, int);
			virtual void			SetMember_FixKey(char const*, double);
			virtual void			SetMember_FixKey(char const*, char const*);
			virtual void			SetMember_FixKey(char const*, ILuaObject*);
			virtual void			SetMember_FixKey(char const*, float);
			virtual bool			IsBool();
			virtual void			SetMemberDouble(char const*, double);
			virtual void			SetMemberNil(float);
			virtual void			SetMemberNil(char const*);
			virtual bool			Debug_IsUnreferenced();
			virtual void			Init();
			virtual void			SetFromGlobal(char const*);
			virtual int				GetStringLen(unsigned int*);
			virtual ILuaObject*		GetMemberUInt(char const*, unsigned int);
			virtual void			SetMember(char const*, unsigned long);
			virtual void			SetReference(int);
			virtual void			RemoveMember(float);
			virtual void			RemoveMember(char const*);
			virtual bool			MemberIsNil(char const*);
			virtual void			SetMemberDouble(float, double);
			virtual double			GetMemberDouble(char const*, double);
		public:
			BYTE		pad_unk[0x4];
			int			m_iLUA_TYPE;		// lua type, string, number, vector, etc.
			int			m_iref;				// ref, for reference push etc.
			ILuaBase*	m_pLua;				// dont use this for function overrides, you WILL crash if not now eventually.
		};
	};
};

#endif