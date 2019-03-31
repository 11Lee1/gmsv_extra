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
			virtual int				SetType(unsigned char) = 0;
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

			CBaseEntity* GetEntity(int iStackPos);
			void PushEntity(CBaseEntity* Entity);
		};
	}
}

#endif 

