#ifndef ILUAOBJECT_H
#define ILUAOBJECT_H
struct lua_State;
namespace GarrysMod
{
	namespace Lua
	{
		typedef int(*CFunc) (lua_State *L);
		class ILuaObject
		{
		public:
			/*0 - 0*/virtual void			Set(ILuaObject* pObject) = 0;
			/*1 - 4*/virtual int			SetFromStack(int pos) = 0;
			/*1 - 8*/virtual void			UnReference() = 0;
			/*2 - 12*/virtual int			GetType() = 0;
			/*3 - 16*/virtual char const*	GetString() = 0;
			/*4 - 20*/virtual float			GetFloat() = 0;
			/*5 - 24*/virtual int			GetInt() = 0;
			/*6 - 28*/virtual void*			GetUserData() = 0;
			/*7 - 32*/virtual void			SetMember(char const*) = 0;
			/*8 - 36*/virtual void			SetMember(float, CFunc Fn) = 0;
			/*9 - 40*/virtual void			SetMember(float, char const*) = 0;
			/*10 - 44*/virtual void			Setmember(float, bool) = 0;
			/*11 - 48*/virtual void			SetMember(float, float) = 0;
			/*12 - 52*/virtual void			SetMember(float, ILuaObject* pObject) = 0;
			/*13 - 56*/virtual void			SetMember(float) = 0;
			/*14 - 60*/virtual void			SetMember(char const*, CFunc Fn) = 0;
			/*15 - 64*/virtual void			SetMember(char const*, char const*) = 0;
			/*16 - 68*/virtual void			SetMember(char const*, bool) = 0;
			/*17 - 72*/virtual void			SetMember(char const*, float) = 0;
			/*18 - 76*/virtual void			SetMember(ILuaObject* pObject1, ILuaObject* pObject2) = 0;
			/*19 - 80*/virtual void			SetMember(char const*, ILuaObject* pObject) = 0;
			/*20 - 84*/virtual bool			GetMemberBool(char const*, bool) = 0;
			/*21 - 88*/virtual int			GetMemberInt(char const*, int) = 0;
			/*22 - 92*/virtual float		GetMemberFloat(char const*, float) = 0;
			/*23 - 96*/virtual char const*	GetMemberStr(float, char const*) = 0;
			/*24 - 100*/virtual char const*	GetMemberStr(char const*, char const*) = 0;
			/*25 - 104*/virtual void*		GetMemberUserData(float, void*) = 0;
			/*26 - 108*/virtual void*		GetMemberUserData(char const*, void*) = 0;
			/*27 - 112*/virtual ILuaObject*	GetMember(ILuaObject* pObject) = 0;
			/*28 - 116*/virtual ILuaObject*	GetMember(ILuaObject*, char const*) = 0;
			/*29 - 120*/virtual ILuaObject*	GetMember(char const*, ILuaObject*) = 0;
			/*30 - 124*/virtual void		SetMetaTable(ILuaObject*) = 0;
			/*31 - 128*/virtual void		SetUserData(void*) = 0;
			/*32 - 132*/virtual void		Push() = 0;
			/*33 - 136*/virtual bool		IsNil() = 0;
			/*34 - 140*/virtual bool		IsTable() = 0;
			/*35 - 144*/virtual bool		IsString() = 0;
			/*36 - 148*/virtual bool		IsNumber() = 0;
			/*37 - 152*/virtual bool		IsFunction() = 0;
			/*38 - 156*/virtual bool		IsUserData() = 0;
			/*39 - 160*/virtual void		Remove_Me_1(char const*, void*) = 0; // actual name lol.
			/*40 - 164*/virtual bool		GetBool() = 0;
			/*41 - 168*/virtual void		PushMemberFast(int) = 0;
			/*42 - 172*/virtual void		SetMemberFast(int, int) = 0;
			/*43 - 176*/virtual void		SetFloat(float) = 0;
			/*44 - 180*/virtual void		SetString(char const*) = 0;
			/*45 - 184*/virtual double		GetDouble() = 0; // same as getfloat
			/*46 - 188*/virtual void		SetMember_FixKey(char const*, int) = 0;
			/*47 - 192*/virtual void		SetMember_FixKey(char const*, double) = 0;
			/*48 - 196*/virtual void		SetMember_FixKey(char const*, char const*) = 0;
			/*49 - 200*/virtual void		SetMember_FixKey(char const*, ILuaObject*) = 0;
			/*50 - 204*/virtual void		SetMember_FixKey(char const*, float) = 0;
			/*51 - 208*/virtual bool		IsBool() = 0;
			/*52 - 212*/virtual void		SetMemberDouble(char const*, double) = 0;
			/*53 - 216*/virtual void		SetMemberNil(float) = 0;
			/*54 - 220*/virtual void		SetMemberNil(char const*) = 0;
			/*55 - 224*/virtual bool		Debug_IsUnreferenced() = 0;
			/*56 - 228*/virtual void		Init() = 0;
			/*57 - 232*/virtual void		SetFromGlobal(char const*) = 0;
			/*58 - 236*/virtual int			GetStringLen(unsigned int*) = 0;
			/*59 - 240*/virtual ILuaObject*	GetMemberUInt(char const*, unsigned int) = 0;
			/*60 - 244*/virtual void		SetMember(char const*, unsigned long) = 0;
			/*61 - 252*/virtual void		SetReference(int) = 0;
			/*62 - 256*/virtual void		RemoveMember(float) = 0;
			/*63 - 260*/virtual void		RemoveMember(char const*) = 0;
			/*64 - 264*/virtual bool		MemberIsNil(char const*) = 0;
			/*65 - 268*/virtual void		SetMemberDouble(float, double) = 0;
			/*66 - 272*/virtual double		GetMemberDouble(char const*, double) = 0;
		};
	};
};
#endif