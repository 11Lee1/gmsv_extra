#ifndef GARRYSMOD_LUA_LUABASE_H
#define GARRYSMOD_LUA_LUABASE_H


#ifdef _WIN32
#pragma once
#endif

#include <stddef.h>
#include "Types.h"
#include "UserData.h"
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
			/*17 - 68*/virtual UserData*			NewUserdata(unsigned int iSize) = 0;
			/*18 - 72*/virtual void					ThrowError(const char* strError) = 0;
			/*19 - 76*/virtual void					CheckType(int iStackPos, int iType) = 0;
			/*20 - 80*/virtual void					ArgError(int iArgNum, const char* strMessage) = 0;
			/*21 - 84*/virtual void					RawGet(int iStackPos) = 0;
			/*22 - 88*/virtual void					RawSet(int iStackPos) = 0;
			/*23 - 92*/virtual const char*			GetString(int iStackPos = -1, unsigned int* iOutLen = NULL) = 0;
			/*24 - 96*/virtual double				GetNumber(int iStackPos = -1) = 0;
			/*25 - 100*/virtual bool				GetBool(int iStackPos = -1) = 0; // 100 - 25
			/*26 - 104*/virtual CFunc				GetCFunction(int iStackPos = -1) = 0; // 104 - 26
			/*27 - 108*/virtual UserData*			GetUserdata(int iStackPos = -1) = 0; // 108 - 27
			/*28 - 112*/virtual void				PushNil() = 0;
			/*29 - 116*/virtual void				PushString(const char* val, unsigned int iLen = 0) = 0;
			/*30 - 120*/virtual void				PushNumber(double val) = 0; // 120 - 30
			/*31 - 124*/virtual void				PushBool(bool val) = 0;
			/*32 - 128*/virtual void				PushCFunction(CFunc val) = 0;
			/*33 - 132*/virtual void				PushCClosure(CFunc val, int iVars) = 0;
			/*34 - 136*/virtual void				PushUserdata(UserData*) = 0;
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
		};
	}
}

#endif 

