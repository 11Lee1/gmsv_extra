#ifndef ILUAINTERFACE_H
#define ILUAINTERFACE_H

#include "Base.h"
#include "../GLUA/LuaObject/CLuaGameObject.h"

#include "../../Source SDK/tier1/color.h"
class ILuaCallback;
class ILuaThreadedCall;
class ILuaInterface : public GarrysMod::Lua::ILuaBase
{
public:
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
	/*55 - 220*/virtual char				Init(ILuaCallback*, bool) = 0;
	/*56 - 224*/virtual int					Shutdown(void) = 0;
	/*57 - 228*/virtual int					Cycle(void) = 0;
	/*58 - 232*/virtual GarrysMod::Lua::CLuaObject*			Global(void) = 0;
	/*59 - 236*/virtual int					Lua_GetObject(int) = 0; // 236 - 59
	/*60 - 240*/virtual int					PushLuaObject(GarrysMod::Lua::ILuaObject*) = 0; // 240 - 60
	/*61 - 244*/virtual int					PushLuaFunction(GarrysMod::Lua::CFunc) = 0;
	/*62 - 248*/virtual int					LuaError(const char*, int) = 0;
	/*63 - 252*/virtual int					TypeError(const char*, int) = 0;
	/*64 - 256*/virtual int					CallInternal(int, int) = 0;
	/*65 - 260*/virtual int					CallInternalNoReturns(int) = 0;
	/*66 - 264*/virtual bool				CallInternalGetBool(int) = 0;
	/*67 - 268*/virtual const char*			CallInternalGetString(int) = 0;
	/*68 - 272*/virtual int					CallInternalGet(int, GarrysMod::Lua::ILuaObject*) = 0;
	/*69 - 276*/virtual char*				NewGlobalTable(const char*) = 0;
	/*70 - 280*/virtual int					NewTemporaryObject(int) = 0; // 280 - 70
	/*71 - 284*/virtual bool				isUserData(int) = 0;
	/*72 - 288*/virtual GarrysMod::Lua::ILuaObject*			GetMetaTableObject(const char*, int) = 0;
	/*73 - 292*/virtual GarrysMod::Lua::ILuaObject*			GetMetaTableObject(int) = 0;
	/*74 - 296*/virtual int					GetReturn(int) = 0;
	/*75 - 300*/virtual bool				IsServer(void) = 0;
	/*76 - 304*/virtual bool				IsClient(void) = 0;
	/*77 - 308*/virtual bool				IsMenu(void) = 0;
	/*78 - 312*/virtual int					DestroyObject(GarrysMod::Lua::ILuaObject*) = 0;
	/*79 - 316*/virtual int					CreateObject(void) = 0;
	/*80 - 320*/virtual int					SetMember(GarrysMod::Lua::ILuaObject*, const char*, GarrysMod::Lua::ILuaObject*) = 0;
	/*81 - 324*/virtual int					SetMember(GarrysMod::Lua::ILuaObject*, const char*) = 0;
	/*82 - 328*/virtual int					SetMember(GarrysMod::Lua::ILuaObject*, float, GarrysMod::Lua::ILuaObject*) = 0;
	/*83 - 332*/virtual int					SetMember(GarrysMod::Lua::ILuaObject*, float) = 0;
	/*84 - 336*/virtual int					SetMember(GarrysMod::Lua::ILuaObject*, GarrysMod::Lua::ILuaObject*, GarrysMod::Lua::ILuaObject*) = 0; // 320 - 80 
	/*85 - 340*/virtual int					GetNewTable(void) = 0;
	/*86 - 344*/virtual int					SetType(unsigned char) = 0;
	/*87 - 348*/virtual int					PushLong(long) = 0;
	/*88 - 352*/virtual int					GetFlags(int) = 0;
	/*89 - 356*/virtual int					FindOnObjectsMetaTable(int, int) = 0;
	/*90 - 360*/virtual int					FindObjectsOnMetaTable(int, int) = 0;
	/*91 - 364*/virtual int					SetMemberFast(GarrysMod::Lua::ILuaObject*, int, int) = 0;
	/*92 - 368*/virtual int					RunString(const char*, const char*, const char*, bool, bool) = 0;
	/*93 - 372*/virtual bool				IsEqual(GarrysMod::Lua::ILuaObject*, GarrysMod::Lua::ILuaObject*) = 0;
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
	/*115 - 460*/virtual int				MsgColor(const Color&, const char*, ...) = 0;
	/*116 - 464*/virtual int				GetCurrentFile(void) = 0;
	/*117 - 468*/virtual int				CompileString(void) = 0;
	/*118 - 472*/virtual int				CallFunctionProtected(int, int, bool) = 0;
	/*119 - 476*/virtual int				Require(const char*) = 0;
	/*120 - 480*/virtual const char*		GetActualTypeName(int) = 0;
	/*121 - 484*/virtual int				PreCreateTable(int, int) = 0;
	/*122 - 488*/virtual int				PushPooledString(int) = 0;
	/*123 - 492*/virtual int				GetBooledString(int) = 0;
	/*124 - 496*/virtual int				AddThreadedCall(ILuaThreadedCall*) = 0;
	/*125 - 500*/virtual int				AppendStackTrace(char*, unsigned long) = 0;
	/*126 - 504*/virtual int				CreateConVar(const char*, const char*, const char*, int) = 0;
	/*127 - 508*/virtual int				CreateConCommand(void) = 0;
};


#endif