#ifndef GARRYSMOD_LUA_LUABASE_H
#define GARRYSMOD_LUA_LUABASE_H


#ifdef _WIN32
#pragma once
#endif

#include <stddef.h>
#include "LuaTypes.h"
#include "LuaUserData.h"
#include "../../Source SDK/server/baseentity.h"
struct lua_State;
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
			/*0 - 0*/virtual int					Top(void) = 0;
			/*1 - 4*/virtual void					Push(int iStackPos) = 0;
			/*2 - 8*/virtual void					Pop(int iAmt = 1) = 0;
			/*3 - 12*/virtual void					GetTable(int iStackPos) = 0;
			/*4 - 16*/virtual void					GetField(int iStackPos, const char* strName) = 0;
			/*5 - 20*/virtual void					SetField(int iStackPos, const char* strName) = 0;
			/*6 - 24*/virtual void					CreateTable() = 0;
			/*7 - 28*/virtual void					SetTable(int i) = 0;
			/*8 - 32*/virtual void					SetMetaTable(int i) = 0;
			/*9 - 36*/virtual bool					GetMetaTable(int i) = 0;
			/*10 - 40*/virtual void					Call(int iArgs, int iResults) = 0;
			/*11 - 44*/virtual int					PCall(int iArgs, int iResults, int iErrorFunc) = 0;
			/*12 - 48*/virtual int					Equal(int iA, int iB) = 0;
			/*13 - 52*/virtual int					RawEqual(int iA, int iB) = 0;
			/*14 - 56*/virtual void					Insert(int iStackPos) = 0;
			/*15 - 60*/virtual void					Remove(int iStackPos) = 0;
			/*16 - 64*/virtual int					Next(int iStackPos) = 0;
			/*17 - 68*/virtual void*				NewUserdata(unsigned int iSize) = 0;
			/*18 - 72*/virtual void					ThrowError(const char* strError) = 0;
			/*19 - 76*/virtual void					CheckType(int iStackPos, int iType) = 0;
			/*20 - 80*/virtual void					ArgError(int iArgNum, const char* strMessage) = 0;
			/*21 - 84*/virtual void					RawGet(int iStackPos) = 0;
			/*22 - 88*/virtual void					RawSet(int iStackPos) = 0;
			/*23 - 92*/virtual const char*			GetString(int iStackPos = -1, unsigned int* iOutLen = NULL) = 0;
			/*24 - 96*/virtual double				GetNumber(int iStackPos = -1) = 0;
			/*25 - 100*/virtual bool				GetBool(int iStackPos = -1) = 0; // 100 - 25
			/*26 - 104*/virtual CFunc				GetCFunction(int iStackPos = -1) = 0; // 104 - 26
			/*27 - 108*/virtual void*				GetUserdata(int iStackPos = -1) = 0; // 108 - 27
			/*28 - 112*/virtual void				PushNil() = 0;
			/*29 - 116*/virtual void				PushString(const char* val, unsigned int iLen = 0) = 0;
			/*30 - 120*/virtual void				PushNumber(double val) = 0; // 120 - 30
			/*31 - 124*/virtual void				PushBool(bool val) = 0;
			/*32 - 128*/virtual void				PushCFunction(CFunc val) = 0;
			/*33 - 132*/virtual void				PushCClosure(CFunc val, int iVars) = 0;
			/*34 - 136*/virtual void				PushUserdata(void*) = 0;
			/*35 - 140*/virtual int					ReferenceCreate() = 0;
			/*36 - 144*/virtual void				ReferenceFree(int i) = 0;
			/*37 - 148*/virtual void				ReferencePush(int i) = 0;
			/*38 - 152*/virtual void				PushSpecial(int iType) = 0;
			/*39 - 156*/virtual bool				IsType(int iStackPos, int iType) = 0;
			/*40 - 160*/virtual int					GetType(int iStackPos) = 0;
			/*41 - 164*/virtual const char*			GetTypeName(int iType) = 0;
			/*42 - 168*/virtual void				CreateMetaTableType(const char* strName, int iType) = 0;
			/*43 - 172*/virtual const char*			CheckString(int iStackPos = -1) = 0; // 172 - 43 
			/*44 - 176*/virtual double				CheckNumber(int iStackPos = -1) = 0;
#ifdef _WIN32 // CLuaInterface 
			/*45 - 180*/virtual int					ObjLen(int) = 0;
			/*46 - 184*/virtual QAngle				GetAngle(int) = 0;
			/*47 - 188*/virtual Vector				GetVector(int) = 0;
			/*48 - 192*/virtual int					PushAngle(QAngle const&) = 0;
			/*49 - 196*/virtual int					PushVector(Vector const&) = 0;
			/*50 - 200*/virtual int					SetState(lua_State*) = 0;
			/*51 - 204*/virtual int					CreateMetaTable(const char*) = 0;
			/*52 - 208*/virtual bool				PushMetaTable(int) = 0;
			/*53 - 212*/virtual int					PushUserType(void*, int) = 0;
			/*54 - 216*/virtual void**				SetUserType(int, void*) = 0;
			/*55 - 220*/virtual char				Init(void*/*ILuaCallback* */, bool) = 0;
			/*56 - 224*/virtual int					Shutdown(void) = 0;
			/*57 - 228*/virtual int					Cycle(void) = 0;
			/*58 - 232*/virtual CLuaObject*			Global(void) = 0;
			/*59 - 236*/virtual int					Lua_GetObject(int) = 0; // 236 - 59
			/*60 - 240*/virtual int					PushLuaObject(void*/*ILuaObject* */) = 0; // 240 - 60
			/*61 - 244*/virtual int					PushLuaFunction(CFunc) = 0;
			/*62 - 248*/virtual int					LuaError(const char*, int) = 0;
			/*63 - 252*/virtual int					TypeError(const char*, int) = 0;
			/*64 - 256*/virtual int					CallInternal(int, int) = 0;
			/*65 - 260*/virtual int					CallInternalNoReturns(int) = 0;
			/*66 - 264*/virtual bool				CallInternalGetBool(int) = 0;
			/*67 - 268*/virtual const char*			CallInternalGetString(int) = 0;
			/*68 - 272*/virtual int					CallInternalGet(int, ILuaObject*) = 0;
			/*69 - 276*/virtual char*				NewGlobalTable(const char*) = 0;
			/*70 - 280*/virtual int					NewTemporaryObject(int) = 0; // 280 - 70
			/*71 - 284*/virtual bool				isUserData(int) = 0;
			/*72 - 288*/virtual ILuaObject*			GetMetaTableObject(const char*, int) = 0;
			/*73 - 292*/virtual ILuaObject*			GetMetaTableObject(int) = 0;
			/*74 - 296*/virtual int					GetReturn(int) = 0;
			/*75 - 300*/virtual bool				IsServer(void) = 0;
			/*76 - 304*/virtual bool				IsClient(void) = 0;
			/*77 - 308*/virtual bool				IsMenu(void) = 0;
			/*78 - 312*/virtual int					DestroyObject(ILuaObject*) = 0;
			/*79 - 316*/virtual int					CreateObject(void) = 0;
			/*80 - 320*/virtual int					SetMember(ILuaObject*, const char*, ILuaObject*) = 0;
			/*81 - 324*/virtual int					SetMember(ILuaObject*, const char*) = 0;
			/*82 - 328*/virtual int					SetMember(ILuaObject*, float, ILuaObject*) = 0;
			/*83 - 332*/virtual int					SetMember(ILuaObject*, float) = 0;
			/*84 - 336*/virtual int					SetMember(ILuaObject*, ILuaObject*, ILuaObject*) = 0; // 320 - 80 
			/*85 - 340*/virtual int					GetNewTable(void) = 0;
			/*86 - 344*/virtual int					SetType(unsigned char) = 0;
			/*87 - 348*/virtual int					PushLong(long) = 0;
			/*88 - 352*/virtual int					GetFlags(int) = 0;
			/*89 - 356*/virtual int					FindOnObjectsMetaTable(int, int) = 0;
			/*90 - 360*/virtual int					FindObjectsOnMetaTable(int, int) = 0;
			/*91 - 364*/virtual int					SetMemberFast(ILuaObject*, int, int) = 0;
			/*92 - 368*/virtual int					RunString(const char*, const char*, const char*, bool, bool) = 0;
			/*93 - 372*/virtual bool				IsEqual(ILuaObject*, ILuaObject*) = 0;
			/*94 - 376*/virtual int					Error(const char*) = 0;
			/*95 - 380*/virtual int					GetStringOrError(int) = 0;
			/*96 - 384*/virtual int					RunLuaModule(const char*) = 0;
			/*97 - 388*/virtual int					FindAndRunScript(const char*, bool, bool, const char*, bool) = 0;
			/*98 - 392*/virtual int					SetPathID(const char*) = 0;
			/*99 - 396*/virtual char*				GetPathID(void) = 0;
			/*100 - 400*/virtual int				ErrorNoHalt(const char*, ...) = 0;
			/*101 - 404*/virtual int				Msg(const char*, ...) = 0;
			/*102 - 408*/virtual int				PushPath(const char*) = 0;
			/*103 - 412*/virtual int				PopPath(void) = 0;
			/*104 - 416*/virtual int				GetPath(void) = 0;
			/*105 - 420*/virtual Color				GetColor(int) = 0;
			/*106 - 424*/virtual int				PushColor(Color) = 0;
			/*107 - 428*/virtual int				GetStack(int, void*) = 0;
			/*108 - 432*/virtual int				GetInfo(const char*, void*) = 0;
			/*109 - 436*/virtual int				GetLocal(void*, int) = 0;
			/*110 - 440*/virtual int				GetUpvalue(int, int) = 0;
			/*111 - 444*/virtual int				RunStringEx(const char*, const char*, const char*, bool, bool, bool, bool) = 0;
			/*112 - 448*/virtual int				GetDataString(int, void**) = 0;
			/*113 - 452*/virtual int				ErrorFromLua(const char*, ...) = 0;
			/*114 - 456*/virtual void*				GetCurrentLocation(void) = 0;
			/*115 - 460*/virtual int				MsgColour(const Color&, const char*, ...) = 0;
			/*116 - 464*/virtual int				GetCurrentFile(void) = 0;
			/*117 - 468*/virtual int				CompileString(void) = 0;
			/*118 - 472*/virtual int				CallFunctionProtected(int, int, bool) = 0;
			/*119 - 476*/virtual int				Require(const char*) = 0;
			/*120 - 480*/virtual const char*		GetActualTypeName(int) = 0;
			/*121 - 484*/virtual int				PreCreateTable(int, int) = 0;
			/*122 - 488*/virtual int				PushPooledString(int) = 0;
			/*123 - 492*/virtual int				GetBooledString(int) = 0;
			/*124 - 496*/virtual int				AddThreadedCall(void*/*ILuaThreadedCall**/) = 0;
			/*125 - 500*/virtual int				AppendStackTrace(char*, unsigned long) = 0;
			/*126 - 504*/virtual int				CreateConVar(const char*, const char*, const char*, int) = 0;
			/*127 - 508*/virtual int				CreateConCommand(void) = 0;
#endif
			CBaseEntity* GetEntity(int iStackPos);
			void PushEntity(CBaseEntity* Entity);
			void PushVector(Vector const* vec);
			void PushAngle(QAngle const* ang);
		};
	}
}

#endif 

