#include "Interface.h"
#include "../../interfaces.h"
#include "../../Source SDK/server/baseentity.h"
#include "../../Source SDK/eiface.h"

#ifdef _WIN32
#include <libloaderapi.h>
#define GETADR(Module,Name)											\
	(unsigned int)GetProcAddress(GetModuleHandleA(Module), Name)	\

#elif __linux__ 
#include <dlfcn.h>
#define GETADR(Module,Name)											\
	(unsigned int)dlsym(dlopen(Module, RTLD_NOW), Name);			\

#endif


CBaseEntity* CLuaInterface::GetEntity(int iStackPos) {
	if (!g_pInterfaces->g_Lua)
		return nullptr;

	GarrysMod::Lua::UserData* userdata = nullptr;
	if (!this->IsType(iStackPos, GarrysMod::Lua::Type::ENTITY) || (userdata = this->GetUserdata(iStackPos), !userdata) || !(*(void**)userdata)) {
		this->Error("Tried to use a NULL Entity!");
		return nullptr;
	}
	int entindex = (**(unsigned int**)userdata) & ENT_ENTRY_MASK;
	if (entindex >= 0xFFFF)
		return nullptr;

	return (CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
}
void CLuaInterface::PushEntity(CBaseEntity* Entity) {
	if (g_pInterfaces->g_Lua && Entity) {
		Entity->PushEntity();
	}
}

int CLuaInterface::Top() {
	typedef int(*lua_gettopFn)(lua_State*);
	static lua_gettopFn lua_gettop = nullptr;
	if(!lua_gettop)
		lua_gettop = (lua_gettopFn)GETADR("lua_shared.dll", "lua_gettop");

	return lua_gettop(this->m_LuaState);
}

void CLuaInterface::Push(int iStackPos) {
	typedef void(*lua_pushvalueFn)(lua_State*, int);
	static lua_pushvalueFn lua_pushvalue = nullptr;
	if (!lua_pushvalue)
		lua_pushvalue = (lua_pushvalueFn)GETADR("lua_shared.dll", "lua_pushvalue");

	lua_pushvalue(this->m_LuaState, iStackPos);
}

void CLuaInterface::Pop(int iAmt) {
	typedef void(*lua_settopFn)(lua_State*, int);
	static lua_settopFn lua_settop = nullptr;
	if (!lua_settop)
		lua_settop = (lua_settopFn)GETADR("lua_shared.dll", "lua_settop");

	lua_settop(this->m_LuaState, iAmt);
}

void CLuaInterface::GetTable(int iStackPos) {
	typedef void(*lua_gettableFn)(lua_State*, int);
	static lua_gettableFn lua_gettable = nullptr;
	if (!lua_gettable)
		lua_gettable = (lua_gettableFn)GETADR("lua_shared.dll", "lua_gettable");

	lua_gettable(this->m_LuaState, iStackPos);
}

void CLuaInterface::GetField(int iStackPos, char const* strName) {
	typedef void(*lua_getfieldFn)(lua_State*, int, char const*);
	static lua_getfieldFn lua_getfield = nullptr;
	if (!lua_getfield)
		lua_getfield = (lua_getfieldFn)GETADR("lua_shared.dll", "lua_getfield");

	lua_getfield(this->m_LuaState, iStackPos, strName);
}

void CLuaInterface::SetField(int iStackPos, char const* strName) {
	typedef void(*lua_setfieldFn)(lua_State*, int, char const*);
	static lua_setfieldFn lua_setfield = nullptr;
	if (!lua_setfield)
		lua_setfield = (lua_setfieldFn)GETADR("lua_shared.dll", "lua_setfield");

	lua_setfield(this->m_LuaState, iStackPos, strName);
}

void CLuaInterface::CreateTable() {
	typedef void(*lua_createtableFn)(lua_State*, int, int);
	static lua_createtableFn lua_createtable = nullptr;
	if (!lua_createtable)
		lua_createtable = (lua_createtableFn)GETADR("lua_shared.dll", "lua_createtable");

	lua_createtable(this->m_LuaState, 0, 0);
}

void CLuaInterface::SetTable(int i) {
	typedef void(*lua_settableFn)(lua_State*, int);
	static lua_settableFn lua_settable = nullptr;
	if (!lua_settable)
		lua_settable = (lua_settableFn)GETADR("lua_shared.dll", "lua_settable");

	lua_settable(this->m_LuaState, i);
}

void CLuaInterface::SetMetaTable(int i) {
	typedef void(*lua_setmetatableFn)(lua_State*, int);
	static lua_setmetatableFn lua_setmetatable = nullptr;
	if (!lua_setmetatable)
		lua_setmetatable = (lua_setmetatableFn)GETADR("lua_shared.dll", "lua_setmetatable");

	lua_setmetatable(this->m_LuaState, i);
}

bool CLuaInterface::GetMetaTable(int i) {
	typedef unsigned int(*lua_getmetatableFn)(lua_State*, int);
	static lua_getmetatableFn lua_getmetatable = nullptr;
	if (!lua_getmetatable)
		lua_getmetatable = (lua_getmetatableFn)GETADR("lua_shared.dll", "lua_getmetatable");

	return lua_getmetatable(this->m_LuaState, i) != 0;
}

void CLuaInterface::Call(int iArgs, int iResults) {
	typedef void(*lua_callFn)(lua_State*, int, int);
	static lua_callFn lua_call = nullptr;
	if (!lua_call)
		lua_call = (lua_callFn)GETADR("lua_shared.dll", "lua_call");

	lua_call(this->m_LuaState, iArgs, iResults);
	this->SetState(this->m_LuaState);	// 200
}

int CLuaInterface::PCall(int iArgs, int iResults, int iErrorFunc) {
	typedef int(*lua_pcallFn)(lua_State*, int, int, int);
	static lua_pcallFn lua_pcall = nullptr;
	if (!lua_pcall)
		lua_pcall = (lua_pcallFn)GETADR("lua_shared.dll", "lua_pcall");

	int returnvalue = lua_pcall(this->m_LuaState, iArgs, iResults, iErrorFunc);
	this->SetState(this->m_LuaState);
	return returnvalue;
}

int CLuaInterface::Equal(int iA, int iB) {
	typedef int(*lua_equalFn)(lua_State*, int, int);
	static lua_equalFn lua_equal = nullptr;
	if (!lua_equal)
		lua_equal = (lua_equalFn)GETADR("lua_shared.dll", "lua_equal");

	return lua_equal(this->m_LuaState, iA, iB);
}

int CLuaInterface::RawEqual(int iA, int iB) {
	typedef int(*lua_rawequalFn)(lua_State*, int, int);
	static lua_rawequalFn lua_rawequal = nullptr;
	if (!lua_rawequal)
		lua_rawequal = (lua_rawequalFn)GETADR("lua_shared.dll", "lua_rawequal");

	return lua_rawequal(this->m_LuaState, iA, iB);
}

void CLuaInterface::Insert(int iStackPos) {
	typedef void(*lua_insertFn)(lua_State*, int);
	static lua_insertFn lua_insert = nullptr;
	if (!lua_insert)
		lua_insert = (lua_insertFn)GETADR("lua_shared.dll", "lua_insert");

	lua_insert(this->m_LuaState, iStackPos);
}

void CLuaInterface::Remove(int iStackPos) {
	typedef void(*lua_removeFn)(lua_State*, int);
	static lua_removeFn lua_remove = nullptr;
	if (!lua_remove)
		lua_remove = (lua_removeFn)GETADR("lua_shared.dll", "lua_remove");

	lua_remove(this->m_LuaState, iStackPos);
}

int CLuaInterface::Next(int iStackPos) {
	typedef int(*lua_nextFn)(lua_State*, int);
	static lua_nextFn lua_next = nullptr;
	if (!lua_next)
		lua_next = (lua_nextFn)GETADR("lua_shared.dll", "lua_next");

	return lua_next(this->m_LuaState, iStackPos);
}

GarrysMod::Lua::UserData* CLuaInterface::NewUserdata(unsigned int iSize) {
	typedef void* (*lua_newuserdataFn)(lua_State*, int);
	static lua_newuserdataFn lua_newuserdata = nullptr;
	if (!lua_newuserdata)
		lua_newuserdata = (lua_newuserdataFn)GETADR("lua_shared.dll", "lua_newuserdata");

	return (GarrysMod::Lua::UserData*)lua_newuserdata(this->m_LuaState, iSize);
}

void CLuaInterface::ThrowError(char const* strError) {
	typedef void(*luaL_errorFn)(lua_State*, char const*, char const*);
	static luaL_errorFn luaL_error = nullptr;
	if (!luaL_error)
		luaL_error = (luaL_errorFn)GETADR("lua_shared.dll", "luaL_error");

	luaL_error(this->m_LuaState, "%s", strError);
}

void CLuaInterface::CheckType(int iStackPos, int iType) {
	int type = this->GetType(iStackPos);
	if (type != iType) {
		char const* TypeName = this->GetTypeName(type);
		this->TypeError(TypeName, 0);
	}
}

void CLuaInterface::ArgError(int iArgNum, const char* strMessage) {
	typedef void(*luaL_argerrorFn)(lua_State*, int, char const*);
	static luaL_argerrorFn luaL_argerror = nullptr;
	if (!luaL_argerror)
		luaL_argerror = (luaL_argerrorFn)GETADR("lua_shared.dll", "luaL_argerror");

	luaL_argerror(this->m_LuaState, iArgNum, strMessage);
}

void CLuaInterface::RawGet(int iStackPos) {
	typedef void(*lua_rawgetFn)(lua_State*, int);
	static lua_rawgetFn lua_rawget = nullptr;
	if (!lua_rawget)
		lua_rawget = (lua_rawgetFn)GETADR("lua_shared.dll", "lua_rawget");

	lua_rawget(this->m_LuaState, iStackPos);
}

void CLuaInterface::RawSet(int iStackPos) {
	typedef void(*lua_rawsetFn)(lua_State*, int);
	static lua_rawsetFn lua_rawset = nullptr;
	if (!lua_rawset)
		lua_rawset = (lua_rawsetFn)GETADR("lua_shared.dll", "lua_rawset");

	lua_rawset(this->m_LuaState, iStackPos);
}

char const* CLuaInterface::GetString(int iStackPos, unsigned int* iOutLen) {
	typedef char const* (*lua_tolstringFn)(lua_State*, int, unsigned int*);
	static lua_tolstringFn lua_tolstring = nullptr;
	if (!lua_tolstring)
		lua_tolstring = (lua_tolstringFn)GETADR("lua_shared.dll", "lua_tolstring");

	return lua_tolstring(this->m_LuaState, iStackPos, iOutLen);
}

double CLuaInterface::GetNumber(int iStackPos) {
	typedef double(*lua_tonumberFn)(lua_State*, int);
	static lua_tonumberFn lua_tonumber = nullptr;
	if (!lua_tonumber)
		lua_tonumber = (lua_tonumberFn)GETADR("lua_shared.dll", "lua_tonumber");

	return lua_tonumber(this->m_LuaState, iStackPos);
}

bool CLuaInterface::GetBool(int iStackPos) {
	typedef bool(*lua_tobooleanFn)(lua_State*, int);
	static lua_tobooleanFn lua_toboolean = nullptr;
	if (!lua_toboolean)
		lua_toboolean = (lua_tobooleanFn)GETADR("lua_shared.dll", "lua_toboolean");

	return lua_toboolean(this->m_LuaState, iStackPos) != 0;
}

GarrysMod::Lua::CFunc CLuaInterface::GetCFunction(int iStackPos) {
	typedef GarrysMod::Lua::CFunc(*lua_tocfunctionFn)(lua_State*, int);
	static lua_tocfunctionFn lua_tocfunction = nullptr;
	if (!lua_tocfunction)
		lua_tocfunction = (lua_tocfunctionFn)GETADR("lua_shared.dll", "lua_tocfunction");

	return lua_tocfunction(this->m_LuaState, iStackPos);
}

GarrysMod::Lua::UserData* CLuaInterface::GetUserdata(int iStackPos) {
	typedef GarrysMod::Lua::UserData* (*lua_touserdataFn)(lua_State*, int);
	static lua_touserdataFn lua_touserdata = nullptr;
	if (!lua_touserdata)
		lua_touserdata = (lua_touserdataFn)GETADR("lua_shared.dll", "lua_touserdata");

	return lua_touserdata(this->m_LuaState, iStackPos);
}

void CLuaInterface::PushNil() {
	typedef void(*lua_pushnilFn)(lua_State*);
	static lua_pushnilFn lua_pushnil = nullptr;
	if (!lua_pushnil)
		lua_pushnil = (lua_pushnilFn)GETADR("lua_shared.dll", "lua_pushnil");

	lua_pushnil(this->m_LuaState);
}

void CLuaInterface::PushString(char const* val, unsigned int iLen) {
	typedef void(*lua_pushlstringFn)(lua_State*, char const*, unsigned int);
	static lua_pushlstringFn lua_pushlstring = nullptr;
	if (!lua_pushlstring)
		lua_pushlstring = (lua_pushlstringFn)GETADR("lua_shared.dll", "lua_pushlstring");

	typedef void(*lua_pushstringFn)(lua_State*, char const*);
	static lua_pushstringFn lua_pushstring = nullptr;
	if (!lua_pushstring)
		lua_pushstring = (lua_pushstringFn)GETADR("lua_shared.dll", "lua_pushstring");

	if (iLen)
		lua_pushlstring(this->m_LuaState, val, iLen);
	else
		lua_pushstring(this->m_LuaState, val);
}

void CLuaInterface::PushNumber(double val) {
	typedef void(*lua_pushnumberFn)(lua_State*, double);
	static lua_pushnumberFn lua_pushnumber = nullptr;
	if (!lua_pushnumber)
		lua_pushnumber = (lua_pushnumberFn)GETADR("lua_shared.dll", "lua_pushnumber");

	lua_pushnumber(this->m_LuaState, val);
}

void CLuaInterface::PushBool(bool val) {
	typedef void(*lua_pushboolFn)(lua_State*, bool);
	static lua_pushboolFn lua_pushbool = nullptr;
	if (!lua_pushbool)
		lua_pushbool = (lua_pushboolFn)GETADR("lua_shared.dll", "lua_pushbool");

	lua_pushbool(this->m_LuaState, val);
}

void CLuaInterface::PushCFunction(GarrysMod::Lua::CFunc val) {
	typedef void(*lua_pushcclosureFn)(lua_State*, GarrysMod::Lua::CFunc val, int);
	static lua_pushcclosureFn lua_pushcclosure = nullptr;
	if (!lua_pushcclosure)
		lua_pushcclosure = (lua_pushcclosureFn)GETADR("lua_shared.dll", "lua_pushcclosure");

	lua_pushcclosure(this->m_LuaState, val, 0);
}

void CLuaInterface::PushCClosure(GarrysMod::Lua::CFunc val, int iVars) {
	typedef void(*lua_pushcclosureFn)(lua_State*, GarrysMod::Lua::CFunc val, int);
	static lua_pushcclosureFn lua_pushcclosure = nullptr;
	if (!lua_pushcclosure)
		lua_pushcclosure = (lua_pushcclosureFn)GETADR("lua_shared.dll", "lua_pushcclosure");

	lua_pushcclosure(this->m_LuaState, val, iVars);
}

void CLuaInterface::PushUserdata(GarrysMod::Lua::UserData* userdata) {
	typedef void(*lua_pushlightuserdataFn)(lua_State*, GarrysMod::Lua::UserData*);
	static lua_pushlightuserdataFn lua_pushlightuserdata = nullptr;
	if (!lua_pushlightuserdata)
		lua_pushlightuserdata = (lua_pushlightuserdataFn)GETADR("lua_shared.dll", "lua_pushlightuserdata");

	lua_pushlightuserdata(this->m_LuaState, userdata);
}

int CLuaInterface::ReferenceCreate() {
	typedef int(*luaL_refFn)(lua_State*, int);
	static luaL_refFn luaL_ref = nullptr;
	if (!luaL_ref)
		luaL_ref = (luaL_refFn)GETADR("lua_shared.dll", "luaL_ref");

	return luaL_ref(this->m_LuaState, -10000);
}

void CLuaInterface::ReferenceFree(int i) {
	typedef void(*luaL_unrefFn)(lua_State*, int, int);
	static luaL_unrefFn luaL_unref = nullptr;
	if (!luaL_unref)
		luaL_unref = (luaL_unrefFn)GETADR("lua_shared.dll", "luaL_unref");

	luaL_unref(this->m_LuaState, -10000, i);
}

void CLuaInterface::ReferencePush(int i) {
	typedef void(*lua_rawgetiFn)(lua_State*, int, int);
	static lua_rawgetiFn lua_rawgeti = nullptr;
	if (!lua_rawgeti)
		lua_rawgeti = (lua_rawgetiFn)GETADR("lua_shared.dll", "lua_rawgeti");

	lua_rawgeti(this->m_LuaState, -10000, i);
}

void CLuaInterface::PushSpecial(int iType) {
	typedef void(*lua_pushvalueFn)(lua_State*, int);
	static lua_pushvalueFn lua_pushvalue = nullptr;
	if (!lua_pushvalue)
		lua_pushvalue = (lua_pushvalueFn)GETADR("lua_shared.dll", "lua_pushvalue");

	if (iType) {
		if (iType == 1)
			lua_pushvalue(this->m_LuaState, -10001);
		else if (iType - 1 == 1)
			lua_pushvalue(this->m_LuaState, -10000);
		else
			this->PushNil();
	}
	else
		lua_pushvalue(this->m_LuaState, -10002);
}

bool CLuaInterface::IsType(int iStackPos, int iType) {
	typedef int(*lua_typeFn)(lua_State*, int);
	static lua_typeFn lua_type = nullptr;
	if (!lua_type)
		lua_type = (lua_typeFn)GETADR("lua_shared.dll", "lua_type");

	int type = lua_type(this->m_LuaState, iStackPos);
	if (type == iType)
		return true;
	else if (type != 7 || iType <= 7)
		return false;
	else
		this->GetUserdata(iStackPos)->type == iType;
}

int CLuaInterface::GetType(int iStackpos) {
	typedef int(*lua_typeFn)(lua_State*, int);
	static lua_typeFn lua_type = nullptr;
	if (!lua_type)
		lua_type = (lua_typeFn)GETADR("lua_shared.dll", "lua_type");

	int returntype = 0;
	switch (lua_type(this->m_LuaState,iStackpos))
	{
	case GarrysMod::Lua::Type::BOOL:
		returntype = GarrysMod::Lua::Type::BOOL;
		break;
	case GarrysMod::Lua::Type::LIGHTUSERDATA:
		returntype = GarrysMod::Lua::Type::LIGHTUSERDATA;
		break;
	case GarrysMod::Lua::Type::NUMBER:
		returntype = GarrysMod::Lua::Type::NUMBER;
		break;
	case GarrysMod::Lua::Type::STRING:
		returntype = GarrysMod::Lua::Type::STRING;
		break;
	case GarrysMod::Lua::Type::TABLE:
		returntype = GarrysMod::Lua::Type::TABLE;
		break;
	case GarrysMod::Lua::Type::FUNCTION:
		returntype = GarrysMod::Lua::Type::FUNCTION;
		break;
	case GarrysMod::Lua::Type::USERDATA:
		{
			GarrysMod::Lua::UserData* udata = this->GetUserdata(iStackpos);
			if (udata && (udata->type >= 9))
				returntype = udata->type;
			else
				returntype = GarrysMod::Lua::Type::USERDATA;
		}
		break;
	case GarrysMod::Lua::Type::THREAD:
		returntype = GarrysMod::Lua::Type::THREAD;
		break;
	default:
		returntype = GarrysMod::Lua::Type::NIL;
		break;
	}

	return returntype;
}

char const* CLuaInterface::GetTypeName(int iType) {
	if (iType > 0x2A)
		return "none";
	else
		return (char const*)GarrysMod::Lua::Type::Name[iType];
}

void CLuaInterface::CreateMetaTableType(char const* strName, int iType) {
	typedef int(*luaL_newmetatable_typeFn)(lua_State*, char const*, int);
	static luaL_newmetatable_typeFn luaL_newmetatable_type = nullptr;
	if (!luaL_newmetatable_type)
		luaL_newmetatable_type = (luaL_newmetatable_typeFn)GETADR("lua_shared.dll", "luaL_newmetatable_type");

	int val = luaL_newmetatable_type(this->m_LuaState, strName, iType);
	if (val && iType <= 0xFE) {
		GarrysMod::Lua::CLuaObject* pObj = this->m_MetaTables[iType];
		if (!pObj) {
			pObj = this->CreateObject();
			this->m_MetaTables[iType] = pObj;
		}
		pObj->SetFromStack(-1);
	}
}

char const* CLuaInterface::CheckString(int iStackPos) {
	typedef char const* (*luaL_checklstringFn)(lua_State*, int, int);
	static luaL_checklstringFn luaL_checklstring = nullptr;
	if (!luaL_checklstring)
		luaL_checklstring = (luaL_checklstringFn)GETADR("lua_shared.dll", "luaL_checklstring");

	return luaL_checklstring(this->m_LuaState, iStackPos, 0);
}

double CLuaInterface::CheckNumber(int iStackPos) {
	typedef double(*luaL_checknumberFn)(lua_State*, int);
	static luaL_checknumberFn luaL_checknumber = nullptr;
	if (!luaL_checknumber)
		luaL_checknumber = (luaL_checknumberFn)GETADR("lua_shared.dll", "luaL_checknumber");

	return luaL_checknumber(this->m_LuaState, iStackPos);
}

// ILuaInterface overrides

int CLuaInterface::ObjLen(int iStackPos) {
	typedef int(*lua_objlenFn)(lua_State*, int);
	static lua_objlenFn lua_objlen = nullptr;
	if (!lua_objlen)
		lua_objlen = (lua_objlenFn)GETADR("lua_shared.dll", "lua_objlen");

	return lua_objlen(this->m_LuaState, iStackPos);
}

QAngle CLuaInterface::GetAngle(int iStackPos) {
	GarrysMod::Lua::UserData* udata = this->GetUserdata(iStackPos);
	if (!udata || !udata->data || udata->type != GarrysMod::Lua::Type::ANGLE)
		return QAngle(0, 0, 0);

	return *(QAngle*)udata->data; 
}

Vector CLuaInterface::GetVector(int iStackPos) {
	GarrysMod::Lua::UserData* udata = this->GetUserdata(iStackPos);
	if (!udata || !udata->data || udata->type != GarrysMod::Lua::Type::VECTOR)
		return Vector(0, 0, 0);

	return *(Vector*)udata->data;  
}

void CLuaInterface::PushAngle(QAngle const& angle) {
	GarrysMod::Lua::UserData* udata = this->NewUserdata(20);
	udata->type = GarrysMod::Lua::Type::ANGLE;
	*(unsigned int*)udata->data = (unsigned int)udata->data + 8;
	if (this->PushMetaTable(GarrysMod::Lua::Type::ANGLE))
		this->SetMetaTable(-2);

	*(QAngle*)udata->data = angle;
}

void CLuaInterface::PushVector(Vector const& vec) {
	GarrysMod::Lua::UserData* udata = this->NewUserdata(20);
	udata->type = GarrysMod::Lua::Type::VECTOR;
	*(unsigned int*)udata->data = (unsigned int)udata->data + 8;
	if (this->PushMetaTable(GarrysMod::Lua::Type::VECTOR))
		this->SetMetaTable(-2);

	*(Vector*)udata->data = vec;
}

void CLuaInterface::SetState(lua_State* state) {
	this->m_LuaState = state;
}

void CLuaInterface::CreateMetaTable(char const* szName) {
	typedef int(*luaL_newmetatable_typeFn)(lua_State*, char const*, int);
	static luaL_newmetatable_typeFn luaL_newmetatable_type = nullptr;
	if (!luaL_newmetatable_type)
		luaL_newmetatable_type = (luaL_newmetatable_typeFn)GETADR("lua_shared.dll", "luaL_newmetatable_type");

	int numtables = this->m_iNumMetaTables;
	if (luaL_newmetatable_type(this->m_LuaState, szName, numtables)) {
		GarrysMod::Lua::CLuaObject* pObj = this->m_MetaTables[numtables];
		if (!pObj) {
			pObj = this->CreateObject();
			this->m_MetaTables[numtables] = pObj;
		}
		pObj->SetFromStack(-1);
		this->m_iNumMetaTables++;
	}
}

bool CLuaInterface::PushMetaTable(int iType) {
	if (iType <= 0xFE && this->m_MetaTables[iType] != 0) {
		this->m_MetaTables[iType]->Push();
		return true;
	}
	else
		return false;
}

void CLuaInterface::PushUserType(void* userdata, int iType) {
	GarrysMod::Lua::UserData* udata = this->NewUserdata(8);
	udata->type = iType;
	udata->data = userdata;
	bool success = this->PushMetaTable(iType);
	if (success)
		this->SetMetaTable(-2);
}

void* CLuaInterface::SetUserType(int iStackPos, void* data) {
	GarrysMod::Lua::UserData* udata = this->GetUserdata(iStackPos);
	if (udata)
		udata->data = data;

	return !udata->data ? nullptr : udata->data;
}

char CLuaInterface::Init(ILuaCallback*, bool) {
	// not now lol.
	return 0;
}

int CLuaInterface::Shutdown() {
	// not now.
	return 0;
}

int CLuaInterface::Cycle() {
	// not now.
	return 0;
}

GarrysMod::Lua::CLuaObject* CLuaInterface::Global() {
	return this->m_Global;
}

GarrysMod::Lua::CLuaObject* CLuaInterface::Lua_GetObject(int iStackPos) {
	GarrysMod::Lua::CLuaObject* tempobj = this->NewTemporaryObject();
	tempobj->SetFromStack(iStackPos);

	return tempobj; // ?
}

void CLuaInterface::PushLuaObject(GarrysMod::Lua::ILuaObject* pObj) {
	if (pObj)
		pObj->Push();
	else
		this->PushNil();
}

void CLuaInterface::PushLuaFunction(GarrysMod::Lua::CFunc Func) {
	typedef void(*lua_pushcclosureFn)(lua_State*, GarrysMod::Lua::CFunc, int);
	static lua_pushcclosureFn lua_pushcclosure = nullptr;
	if (!lua_pushcclosure)
		lua_pushcclosure = (lua_pushcclosureFn)GETADR("lua_shared.dll", "lua_pushcclosure");

	lua_pushcclosure(this->m_LuaState, Func, 0);
}

int CLuaInterface::LuaError(char const* message, int args) {
	typedef int(*luaL_argerrorFn)(lua_State*, int, char const*);
	static luaL_argerrorFn luaL_argerror = nullptr;
	if (!luaL_argerror)
		luaL_argerror = (luaL_argerrorFn)GETADR("lua_shared.dll", "luaL_argerror");

	if (args == -1)
		return this->ErrorNoHalt("%s", message);
	else
		return luaL_argerror(this->m_LuaState, args, message);
}

int CLuaInterface::TypeError(char const* message, int narg) {
	typedef int(*luaL_typerrorFn)(lua_State*, int, char const*);
	static luaL_typerrorFn luaL_typerror = nullptr;
	if (!luaL_typerror)
		luaL_typerror = (luaL_typerrorFn)GETADR("lua_shared.dll", "luaL_typerror");

	return luaL_typerror(this->m_LuaState, narg, message);
}

bool CLuaInterface::CallInternal(int iStackPos, int iNumReturnValues) {
	// finish this properly, because I doubt this is correct.
	if (this->GetType(iStackPos) != 6)
		printf("Lua tried to call non functions\n");
	
	if (iNumReturnValues > 4)
		printf("[CLuaInterface::Call] Expecting more returns than possible\n");

	this->m_ProtectedFunctionReturns[0] = nullptr;
	this->m_ProtectedFunctionReturns[1] = nullptr;
	this->m_ProtectedFunctionReturns[2] = nullptr;
	this->m_ProtectedFunctionReturns[3] = nullptr;

	if (iNumReturnValues > 0) {
		int SavenRetValues = iNumReturnValues;
		int index = 0;
		do {
			GarrysMod::Lua::CLuaObject* tempobj = this->NewTemporaryObject();
			index++;
			this->m_ProtectedFunctionReturns[index] = tempobj;
		} while (!(SavenRetValues-- == 1));
	}
	if (this->CallFunctionProtected(iStackPos, iNumReturnValues, false)) {
		if (iNumReturnValues > 0) {
			int index = 0;
			do {
				if (!this->m_ProtectedFunctionReturns[index]) {
					this->m_ProtectedFunctionReturns[index] = this->NewTemporaryObject();
				}
				this->m_ProtectedFunctionReturns[index]->SetFromStack(~index++);
			} while (index < iNumReturnValues);
		}
		return true;
	}
	else {
		printf("erorr using call internal\n");
		return false;
	}
	return false;
}

bool CLuaInterface::CallInternalNoReturns(int iStackPos) {
	if (this->CallFunctionProtected(iStackPos, 0, 0))
		return 1;
	else {
		printf("failed calling \"CallInternalNoReturns\"");
		return 0;
	}
	return 0;
}

bool CLuaInterface::CallInternalGetBool(int iStackPos) {
	if (this->CallFunctionProtected(iStackPos, 1, 0)) {
		int rettype = this->GetType(-1);
		if (rettype == GarrysMod::Lua::Type::BOOL) {
			bool bRet = this->GetBool(-1);
			this->Pop(1);
		}
		else {
			this->Pop(1);
			return false;
		}
	}
	else {
		printf("failed calling \"CallInternalGetBool\"");
		return false;
	}
	return false;
}

char const* CLuaInterface::CallInternalGetString(int iStackPos) {
	if (this->CallFunctionProtected(iStackPos, 1, 0)) {
		int rettype = this->GetType(-1);
		if (rettype == GarrysMod::Lua::Type::STRING) {
			char const* szRet = this->GetString(-1, 0);
			this->Pop(1);
			return szRet;
		}
		else {
			return nullptr;
		}
	}
	else {
		printf("failed calling \"CallInternalGetString\"");
		return nullptr;
	}
	return nullptr;
}

bool CLuaInterface::CallInternalGet(int iStackPos, GarrysMod::Lua::ILuaObject* pObj) {
	if (this->CallFunctionProtected(iStackPos, 1, 0)) {
		pObj->SetFromStack(-1);
		this->Pop(1);
	}
	else {
		printf("failed calling \"CallInternalGet\"");
		return false;
	}
	return false;
}

void CLuaInterface::NewGlobalTable(char const* szName) {
	CreateTable();
	SetField(-10002, szName);
}

GarrysMod::Lua::CLuaObject* CLuaInterface::NewTemporaryObject() {
	this->m_iCurrentTempObject++;
	if (this->m_iCurrentTempObject >= 32)
		this->m_iCurrentTempObject = 0;

	if (this->m_TempObjects[this->m_iCurrentTempObject])
		this->m_TempObjects[this->m_iCurrentTempObject]->UnReference();
	else
		this->m_TempObjects[this->m_iCurrentTempObject] = this->CreateObject();

	return this->m_TempObjects[this->m_iCurrentTempObject];
}

bool CLuaInterface::isUserData(int iStackPos) {
	typedef int(*lua_typeFn)(lua_State*, int);
	static lua_typeFn lua_type = nullptr;
	if (!lua_type)
		lua_type = (lua_typeFn)GETADR("lua_shared.dll", "lua_type");

	return lua_type(this->m_LuaState, iStackPos) == GarrysMod::Lua::Type::USERDATA;
}

GarrysMod::Lua::ILuaObject* CLuaInterface::GetMetaTableObject(int iType) {
	typedef unsigned int(*lua_getmetatableFn)(lua_State*, int);
	static lua_getmetatableFn lua_getmetatable = nullptr;
	if (!lua_getmetatable)
		lua_getmetatable = (lua_getmetatableFn)GETADR("lua_shared.dll", "lua_getmetatable");

	if (lua_getmetatable(this->m_LuaState, iType)) {
		GarrysMod::Lua::ILuaObject* ret = this->NewTemporaryObject();
		ret->SetFromStack(-1);
		this->Pop(1);
		return ret;
	}
	else {
		return nullptr;
	}
	return nullptr;
}

GarrysMod::Lua::ILuaObject* CLuaInterface::GetMetaTableObject(char const* szName, int iType) {
	this->GetField(-10000,szName);
	if (this->GetType(-1) != GarrysMod::Lua::Type::TABLE) {
		this->Pop(1);
		if (iType == -1) {
			return nullptr;
		}
		this->CreateMetaTableType(szName, iType);
	}
	GarrysMod::Lua::ILuaObject* ret = this->NewTemporaryObject();
	ret->SetFromStack(-1);
	this->Pop(1);
	return ret;
}

GarrysMod::Lua::CLuaObject* CLuaInterface::GetReturn(int index) {
	if (index >= 4)
		printf("Tried to get return higher than max\n");

	GarrysMod::Lua::CLuaObject* ret = this->m_ProtectedFunctionReturns[index];
	if (!ret)
		printf("Error: Calling GetReturn on an invalid return! Check code!!\n");

	return ret;
}

bool CLuaInterface::IsServer() {
	return this->m_cLuaState == GarrysMod::Lua::Server;
}

bool CLuaInterface::IsClient() {
	return this->m_cLuaState == GarrysMod::Lua::Client;
}

bool CLuaInterface::IsMenu() {
	return this->m_cLuaState == GarrysMod::Lua::Menu;
}