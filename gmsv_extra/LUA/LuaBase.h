#ifndef GARRYSMOD_LUA_LUABASE_H
#define GARRYSMOD_LUA_LUABASE_H

#include <stddef.h>
#include "LuaTypes.h"
#include "LuaUserData.h"

struct lua_State;

class C_BaseEntity;
namespace GarrysMod
{
	namespace Lua
	{
		typedef int(*CFunc) (lua_State *L);

		//
		// Access to raw Lua function calls
		// 5D DB 9A CF
		enum
		{
			SPECIAL_GLOB,		// Global table
			SPECIAL_ENV,		// Environment table
			SPECIAL_REG,		// Registry table
		};
		enum
		{
			Client,
			Server,
			Menu
		};
		class ILuaObject;
		class ILuaBase
		{
		public:
			/*

				Heads up:

				I don't use the lua interface like (almost) at all within the cheat, so dont expect this to be very accurate / useful.


			*/
			virtual int				Top(void) = 0;
			virtual void			Push(int iStackPos) = 0;
			virtual void			Pop(int iAmt = 1) = 0;
			virtual void			GetTable(int iStackPos) = 0;
			virtual void			GetField(int iStackPos, const char* strName) = 0;
			virtual void			SetField(int iStackPos, const char* strName) = 0;
			virtual void			CreateTable() = 0;
			virtual void			SetTable(int i) = 0;
			virtual void			SetMetaTable(int i) = 0;
			virtual bool			GetMetaTable(int i) = 0;
			virtual void			Call(int iArgs, int iResults) = 0;
			virtual int				PCall(int iArgs, int iResults, int iErrorFunc) = 0;
			virtual int				Equal(int iA, int iB) = 0;
			virtual int				RawEqual(int iA, int iB) = 0;
			virtual void			Insert(int iStackPos) = 0;
			virtual void			Remove(int iStackPos) = 0;
			virtual int				Next(int iStackPos) = 0;
			virtual void*			NewUserdata(unsigned int iSize) = 0;
			virtual void			ThrowError(const char* strError) = 0;
			virtual void			CheckType(int iStackPos, int iType) = 0;
			virtual void			ArgError(int iArgNum, const char* strMessage) = 0;
			virtual void			RawGet(int iStackPos) = 0;
			virtual void			RawSet(int iStackPos) = 0;
			virtual const char*		GetString(int iStackPos = -1, unsigned int* iOutLen = NULL) = 0;
			virtual double			GetNumber(int iStackPos = -1) = 0;
			virtual bool			GetBool(int iStackPos = -1) = 0; // 100 - 25
			virtual CFunc			GetCFunction(int iStackPos = -1) = 0; // 104 - 26
			virtual void*			GetUserdata(int iStackPos = -1) = 0; // 108 - 27
			virtual void			PushNil() = 0;
			virtual void			PushString(const char* val, unsigned int iLen = 0) = 0;
			virtual void			PushNumber(double val) = 0; // 120 - 30
			virtual void			PushBool(bool val) = 0;
			virtual void			PushCFunction(CFunc val) = 0;
			virtual void			PushCClosure(CFunc val, int iVars) = 0;
			virtual void			PushUserdata(void*) = 0;
			virtual int				ReferenceCreate() = 0;
			virtual void			ReferenceFree(int i) = 0;
			virtual void			ReferencePush(int i) = 0;
			virtual void			PushSpecial(int iType) = 0;
			virtual bool			IsType(int iStackPos, int iType) = 0;
			virtual int				GetType(int iStackPos) = 0;
			virtual const char*		GetTypeName(int iType) = 0;
			virtual void			CreateMetaTableType(const char* strName, int iType) = 0;
			virtual const char*		CheckString(int iStackPos = -1) = 0; // 172 - 43 
			virtual double			CheckNumber(int iStackPos = -1) = 0;
			virtual int				ObjLen(int) = 0;
			virtual QAngle			GetAngle(int) = 0;
			virtual Vector			GetVector(int) = 0;
			virtual int				PushAngle(QAngle const&) = 0;
			virtual int				PushVector(Vector const&) = 0;
			virtual int				SetState(lua_State*) = 0;
			virtual int				CreateMetaTable(const char*) = 0;
			virtual char			PushMetaTable(int) = 0;
			virtual int				PushUserType(void*, int) = 0;
			virtual void**			SetUserType(int, void*) = 0;
			virtual char			Init(void*/*ILuaCallback* */, bool) = 0;
			virtual int				Shutdown(void) = 0;
			virtual int				Cycle(void) = 0;
			virtual int				Global(void) = 0;
			virtual int				Lua_GetObject(int) = 0; // 236 - 59
			virtual int				PushLuaObject(void*/*ILuaObject* */) = 0; // 240 - 60
			virtual int				PushLuaFunction(int*, CFunc) = 0;
			virtual int				LuaError(const char*, int) = 0;
			virtual int				TypeError(const char*, int) = 0;
			virtual int				CallInternal(int, int) = 0;
			virtual int				CallInternalNoReturns(int) = 0;
			virtual bool			CallInternalGetBool(int) = 0;
			virtual const char*		CallInternalGetString(int) = 0;
			virtual int				CallInternalGet(int, ILuaObject*) = 0;
			virtual char*			NewGlobalTable(const char*) = 0;
			virtual int				NewTemporaryObject(int) = 0; // 280 - 70
			virtual bool			isUserData(int) = 0;
			virtual ILuaObject*		GetMetaTableObject(const char*, int) = 0;
			virtual ILuaObject*		GetMetaTableObject(int) = 0;
			virtual int				GetReturn(int) = 0;
			virtual bool			IsServer(void) = 0;
			virtual bool			IsClient(void) = 0;
			virtual bool			IsMenu(void) = 0;
			virtual int				DestroyObject(ILuaObject*) = 0;
			virtual int				CreateObject(void) = 0;
			virtual int				SetMember(ILuaObject*, ILuaObject*, ILuaObject*) = 0; // 320 - 80 
			virtual int				GetNewTable(void) = 0;
			virtual int				SetMember(ILuaObject*, float) = 0;
			virtual int				SetMember(ILuaObject*, float, ILuaObject*) = 0;
			virtual int				SetMember(ILuaObject*, const char*) = 0;
			virtual int				SetMember(ILuaObject*, const char*, ILuaObject*) = 0;
			virtual int				SetType(UCHAR) = 0;
			virtual int				PushLong(long) = 0;
			virtual int				GetFlags(int) = 0;
			virtual int				FindOnObjectsMetaTable(int, int) = 0;
			virtual int				FindObjectsOnMetaTable(int, int) = 0;
			virtual int				SetMemberFast(ILuaObject*, int, int) = 0;
			virtual int				RunString(const char*, const char*, const char*, bool, bool) = 0;
			virtual bool			IsEqual(ILuaObject*, ILuaObject*) = 0;
			virtual int				Error(const char*) = 0;
			virtual int				GetStringOrError(int) = 0;
			virtual int				RunLuaModule(const char*) = 0;
			virtual int				FindAndRunScript(const char*, bool, bool, const char*, bool) = 0;
			virtual int				SetPathID(const char*) = 0;
			virtual char*			GetPathID(void) = 0;
			virtual int				ErrorNoHalt(const char*, ...) = 0;
			virtual int				Msg(const char*, ...) = 0;
			virtual int				PushPath(const char*) = 0;
			virtual int				PopPath(void) = 0;
			virtual int				GetPath(void) = 0;
			virtual Color			GetColor(int) = 0;
			virtual int				PushColor(Color) = 0;
			virtual int				GetStack(int, void*) = 0;
			virtual int				GetInfo(const char*, void*) = 0;
			virtual int				GetLocal(void*, int) = 0;
			virtual int				GetUpvalue(int, int) = 0;
			virtual int				RunStringEx(const char*, const char*, const char*, bool, bool, bool, bool) = 0;
			virtual int				GetDataString(int, void**) = 0;
			virtual int				ErrorFromLua(const char*, ...) = 0;
			virtual void*			GetCurrentLocation(void) = 0;
			virtual int				MsgColour(const Color&, const char*, ...) = 0;
			virtual int				GetCurrentFile(void) = 0;
			virtual int				CompileString(void) = 0;
			virtual int				CallFunctionProtected(int, int, bool) = 0;
			virtual int				Require(const char*) = 0;
			virtual const char*		GetActualTypeName(int) = 0;
			virtual int				PreCreateTable(int, int) = 0;
			virtual int				PushPooledString(int) = 0;
			virtual int				GetBooledString(int) = 0;
			virtual int				AddThreadedCall(void*/*ILuaThreadedCall**/) = 0;
			virtual int				AppendStackTrace(char*, unsigned long) = 0;
			virtual int				CreateConVar(const char*, const char*, const char*, int) = 0;
			virtual int				CreateConCommand(void) = 0;

			C_BaseEntity* GetEntity(int iStackPos);
			void PushEntity(C_BaseEntity* Entity);
		};
		// properly make overides for these dumbass lol
		class ILuaObject
		{
		public:
			/*0 - 0*/virtual void			Set(ILuaObject* pObject) = 0;
			/*1 - 4*/virtual int			SetFromStack(int pos) = 0;
			/*1 - 8*/virtual void			UnReference() = 0;
			/*2 - 12*/virtual int			GetType() = 0;
			/*3 - 16*/virtual char const*	GetString() = 0;
			/*4 - 20*/virtual float			GetFloat() = 0;
			/*5 - 24*/virtual	int			GetInt() = 0;
			/*6 - 28*/virtual void*			GetUserData() = 0;
			/*7 - 32*/virtual	void		SetMember(char const*) = 0;
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

		class CLuaObject : public ILuaObject
		{
		public:
			virtual  ~CLuaObject() {};
			/*
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
			virtual void			Remove_Me_1(char const*, void*) = 0; // actual name ;
			virtual bool			GetBool();
			virtual void			PushMemberFast(int);
			virtual void			SetMemberFast(int, int);
			virtual void			SetFloat(float);
			virtual void			SetString(char const*);
			virtual double			GetDouble() = 0; // same as getf;
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
			*/
			virtual void			Set(ILuaObject* pObject) { }
			virtual int				SetFromStack(int pos) { return 0; }
			virtual void			UnReference() { }
			virtual int				GetType() { return m_iLUA_TYPE; }
			virtual char const*		GetString() {
				this->Push();
				char const* str = g_pInterfaces->g_Lua->GetString(-1, 0);
				g_pInterfaces->g_Lua->Pop(1);
				return str;
			}
			virtual float			GetFloat() {
				if (!this->IsNumber())
					return 0.0f;

				this->Push();
				float out = g_pInterfaces->g_Lua->GetNumber(-1);
				g_pInterfaces->g_Lua->Pop(1);
				return out;
			}
			virtual	int				GetInt() {
				if (!this->IsNumber())
					return 0;

				this->Push();
				double out = g_pInterfaces->g_Lua->GetNumber(-1);
				g_pInterfaces->g_Lua->Pop(1);
				return floor(out);
			}
			virtual void*			GetUserData() {
				if (!this->IsUserData())
					return nullptr;


			}
			virtual	void			SetMember(char const*) { }
			virtual void			SetMember(float, CFunc Fn) { }
			virtual void			SetMember(float, char const*) { }
			virtual void			Setmember(float, bool) { }
			virtual void			SetMember(float, float) { }
			virtual void			SetMember(float, ILuaObject* pObject) { }
			virtual void			SetMember(float) { }
			virtual void			SetMember(char const*, CFunc Fn) { }
			virtual void			SetMember(char const*, char const*) { }
			virtual void			SetMember(char const*, bool) { }
			virtual void			SetMember(char const*, float) { }
			virtual void			SetMember(ILuaObject* pObject1, ILuaObject* pObject2) { }
			virtual void			SetMember(char const*, ILuaObject* pObject) { }
			virtual bool			GetMemberBool(char const*, bool) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual int				GetMemberInt(char const*, int) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual float			GetMemberFloat(char const*, float) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual char const*		GetMemberStr(float, char const*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual char const*		GetMemberStr(char const*, char const*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual void*			GetMemberUserData(float, void*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual void*			GetMemberUserData(char const*, void*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual ILuaObject*		GetMember(ILuaObject* pObject) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual ILuaObject*		GetMember(ILuaObject*, char const*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual ILuaObject*		GetMember(char const*, ILuaObject*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual void			SetMetaTable(ILuaObject*) { }
			virtual void			SetUserData(void*) { }
			virtual void			Push() {
				if (!g_pInterfaces->g_Lua)
					return;

				if (m_iref == -1)
					return g_pInterfaces->g_Lua->PushNil();

				return g_pInterfaces->g_Lua->ReferencePush(m_iref);
			}
			virtual bool			IsNil() {
				if (!g_pInterfaces->g_Lua || m_iLUA_TYPE == Type::NIL)
					return true;

				return false;
			}
			virtual bool			IsTable() {
				if (!g_pInterfaces->g_Lua)
					return false;

				if (m_iLUA_TYPE == Type::TABLE)
					return true;

				return false;
			}
			virtual bool			IsString() {
				if (!g_pInterfaces->g_Lua)
					return false;

				if (m_iLUA_TYPE == Type::STRING)
					return true;

				return false;
			}
			virtual bool			IsNumber() {
				if (!g_pInterfaces->g_Lua)
					return false;

				if (m_iLUA_TYPE == Type::NUMBER)
					return true;

				return false;
			}
			virtual bool			IsFunction() {
				if (!g_pInterfaces->g_Lua)
					return false;

				if (m_iLUA_TYPE == Type::FUNCTION)
					return true;

				return false;
			}
			virtual bool			IsUserData() {
				if (!g_pInterfaces->g_Lua)
					return false;

				if (m_iLUA_TYPE == Type::USERDATA)
					return true;

				return false;
			}
			virtual void			Remove_Me_1(char const*, void*) { } // actual name
			virtual bool			GetBool() {
				if (!this->IsBool())
					return false;

				this->Push();
				bool out = g_pInterfaces->g_Lua->GetBool(-1);
				g_pInterfaces->g_Lua->Pop(-1);
				return out;
			}
			virtual void			PushMemberFast(int) { }
			virtual void			SetMemberFast(int, int) { }
			virtual void			SetFloat(float) { }
			virtual void			SetString(char const*) { }
			virtual double			GetDouble() {
				if (!this->IsNumber())
					return 0.0;

				this->Push();
				double out = g_pInterfaces->g_Lua->GetNumber(-1);
				g_pInterfaces->g_Lua->Pop(1);
				return out;
			}
			virtual void			SetMember_FixKey(char const*, int) { }
			virtual void			SetMember_FixKey(char const*, double) { }
			virtual void			SetMember_FixKey(char const*, char const*) { }
			virtual void			SetMember_FixKey(char const*, ILuaObject*) { }
			virtual void			SetMember_FixKey(char const*, float) { }
			virtual bool			IsBool() { 
				if (!g_pInterfaces->g_Lua)
					return false;

				return m_iLUA_TYPE == Type::BOOL;
			}
			virtual void			SetMemberDouble(char const*, double) { }
			virtual void			SetMemberNil(float) { }
			virtual void			SetMemberNil(char const*) { }
			virtual bool			Debug_IsUnreferenced() { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual void			Init() { }
			virtual void			SetFromGlobal(char const*) { }
			virtual int				GetStringLen(unsigned int* len) { 
				this->Push();
				g_pInterfaces->g_Lua->GetString(-1, len);
				g_pInterfaces->g_Lua->Pop(1);
				return *len;
			}
			virtual ILuaObject*		GetMemberUInt(char const*, unsigned int) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual void			SetMember(char const*, unsigned long) { }
			virtual void			SetReference(int) { }
			virtual void			RemoveMember(float) { }
			virtual void			RemoveMember(char const*) { }
			virtual bool			MemberIsNil(char const*) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
			virtual void			SetMemberDouble(float, double) { }
			virtual double			GetMemberDouble(char const*, double) { return 0; }  ///// FINISH!!!!!!!!!!!!!! 
		public:
			BYTE		pad_unk[0x4];
			int			m_iLUA_TYPE;		// lua type, string, number, vector, etc.
			int			m_iref;				// ref, for reference push etc.
			ILuaBase*	m_pLua;				// dont use this for function overrides, you WILL crash if not now eventually.
		};

		class CLuaGameObject : public CLuaObject
		{
		public:
			virtual ~CLuaGameObject() {};
			/*67 - 276*/virtual CBaseEntity*	GetMemberEntity(char const*, CBaseEntity*) { return nullptr; }
			/*68 - 280*/virtual void			SetMemberEntity(char const*, CBaseEntity*) {}
			/*69 - 284*/virtual void			SetMemberEntity(float, CBaseEntity*) {}
			/*70 - 288*/virtual bool			IsEntity() { return false; }
			/*71 - 292*/virtual CBaseEntity*	GetEntity() { return nullptr; }
			/*72 - 296*/virtual void			SetEntity(CBaseEntity*) {}
			/*73 - 300*/virtual void			SetMemberVector(float, Vector*) {}
			/*74 - 304*/virtual void			SetMemberVector(char const*, Vector&) {}
			/*75 - 308*/virtual void			SetMemberVector(char const*, Vector*) {}
			/*76 - 312*/virtual Vector			GetMemberVector(int) { return Vector(0, 0, 0); }
			/*77 - 316*/virtual	Vector			GetMemberVector(char const*, Vector*) { return Vector(0, 0, 0); }
			/*78 - 320*/virtual Vector			GetVector() { return Vector(0, 0, 0); }
			/*79 - 324*/virtual bool			IsVector() { return false; }
			/*80 - 328*/virtual void			SetMemberAngle(char const*, QAngle*) {}
			/*81 - 332*/virtual QAngle			GetMemberAngle(char const*, QAngle*) { return QAngle(0, 0, 0); }
			/*82 - 336*/virtual QAngle			GetAngle() { return QAngle(0, 0, 0); }
			/*83 - 340*/virtual bool			IsAngle() { return false; }
		};
	}
}

#endif 

