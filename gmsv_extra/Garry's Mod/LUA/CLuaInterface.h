#ifndef CLUAINTERFACE_H
#define CLUAINTERFACE_H
#include "ILuaInterface.h"

struct lua_State;
class CLuaGameCallback;
class CLuaInterface : public ILuaInterface
{
public: // ILuaBase
	/*0 - 0*/virtual int					Top(void);
	/*1 - 4*/virtual void					Push(int iStackPos);
	/*2 - 8*/virtual void					Pop(int iAmt = 1);
	/*3 - 12*/virtual void					GetTable(int iStackPos);
	/*4 - 16*/virtual void					GetField(int iStackPos, const char* strName);
	/*5 - 20*/virtual void					SetField(int iStackPos, const char* strName);
	/*6 - 24*/virtual void					CreateTable();
	/*7 - 28*/virtual void					SetTable(int i);
	/*8 - 32*/virtual void					SetMetaTable(int i);
	/*9 - 36*/virtual bool					GetMetaTable(int i);
	/*10 - 40*/virtual void					Call(int iArgs, int iResults);
	/*11 - 44*/virtual int					PCall(int iArgs, int iResults, int iErrorFunc);
	/*12 - 48*/virtual int					Equal(int iA, int iB);
	/*13 - 52*/virtual int					RawEqual(int iA, int iB);
	/*14 - 56*/virtual void					Insert(int iStackPos);
	/*15 - 60*/virtual void					Remove(int iStackPos);
	/*16 - 64*/virtual int					Next(int iStackPos);
	/*17 - 68*/virtual GarrysMod::Lua::UserData*	NewUserdata(unsigned int iSize);
	/*18 - 72*/virtual void					ThrowError(const char* strError);
	/*19 - 76*/virtual void					CheckType(int iStackPos, int iType);
	/*20 - 80*/virtual void					ArgError(int iArgNum, const char* strMessage);
	/*21 - 84*/virtual void					RawGet(int iStackPos);
	/*22 - 88*/virtual void					RawSet(int iStackPos);
	/*23 - 92*/virtual const char*			GetString(int iStackPos = -1, unsigned int* iOutLen = NULL);
	/*24 - 96*/virtual double				GetNumber(int iStackPos = -1);
	/*25 - 100*/virtual bool				GetBool(int iStackPos = -1);
	/*26 - 104*/virtual GarrysMod::Lua::CFunc		GetCFunction(int iStackPos = -1);
	/*27 - 108*/virtual GarrysMod::Lua::UserData*	GetUserdata(int iStackPos = -1);
	/*28 - 112*/virtual void				PushNil();
	/*29 - 116*/virtual void				PushString(const char* val, unsigned int iLen = 0);
	/*30 - 120*/virtual void				PushNumber(double val);
	/*31 - 124*/virtual void				PushBool(bool val);
	/*32 - 128*/virtual void				PushCFunction(GarrysMod::Lua::CFunc val);
	/*33 - 132*/virtual void				PushCClosure(GarrysMod::Lua::CFunc val, int iVars);
	/*34 - 136*/virtual void				PushUserdata(GarrysMod::Lua::UserData*);
	/*35 - 140*/virtual int					ReferenceCreate();
	/*36 - 144*/virtual void				ReferenceFree(int i);
	/*37 - 148*/virtual void				ReferencePush(int i);
	/*38 - 152*/virtual void				PushSpecial(int iType);
	/*39 - 156*/virtual bool				IsType(int iStackPos, int iType);
	/*40 - 160*/virtual int					GetType(int iStackPos);
	/*41 - 164*/virtual const char*			GetTypeName(int iType);
	/*42 - 168*/virtual void				CreateMetaTableType(const char* strName, int iType);
	/*43 - 172*/virtual const char*			CheckString(int iStackPos = -1);
	/*44 - 176*/virtual double				CheckNumber(int iStackPos = -1);
public: // ILuaInterface
	/*45 - 180*/virtual int					ObjLen(int iStackPos);
	/*46 - 184*/virtual QAngle				GetAngle(int iStackPos);
	/*47 - 188*/virtual Vector				GetVector(int iStackPos);
	/*48 - 192*/virtual void				PushAngle(QAngle const&);
	/*49 - 196*/virtual void				PushVector(Vector const&);
	/*50 - 200*/virtual void				SetState(lua_State*);
	/*51 - 204*/virtual void				CreateMetaTable(const char* szName);
	/*52 - 208*/virtual bool				PushMetaTable(int iType);
	/*53 - 212*/virtual void				PushUserType(void* userdata, int iType);
	/*54 - 216*/virtual void*				SetUserType(int, void*);
	/*55 - 220*/virtual char				Init(ILuaCallback*, bool);
	/*56 - 224*/virtual int					Shutdown(void);
	/*57 - 228*/virtual int					Cycle(void);
	/*58 - 232*/virtual GarrysMod::Lua::CLuaObject* Global(void);
	/*59 - 236*/virtual GarrysMod::Lua::CLuaObject* Lua_GetObject(int iStackPos);
	/*60 - 240*/virtual void				PushLuaObject(GarrysMod::Lua::ILuaObject* pObj);
	/*61 - 244*/virtual void				PushLuaFunction(GarrysMod::Lua::CFunc func);
	/*62 - 248*/virtual int					LuaError(const char*, int args);
	/*63 - 252*/virtual int					TypeError(const char*, int narg);
	/*64 - 256*/virtual bool				CallInternal(int iStackPos, int iNumReturnValues);
	/*65 - 260*/virtual bool				CallInternalNoReturns(int iStackPos);
	/*66 - 264*/virtual bool				CallInternalGetBool(int iStackPos);
	/*67 - 268*/virtual char const*			CallInternalGetString(int iStackPos);
	/*68 - 272*/virtual bool				CallInternalGet(int iStackPos, GarrysMod::Lua::ILuaObject* pObj);
	/*69 - 276*/virtual void				NewGlobalTable(const char* szName);
	/*70 - 280*/virtual GarrysMod::Lua::CLuaObject* NewTemporaryObject();
	/*71 - 284*/virtual bool				isUserData(int iStackPos);
	/*72 - 288*/virtual GarrysMod::Lua::ILuaObject* GetMetaTableObject(int iType);
	/*73 - 292*/virtual GarrysMod::Lua::ILuaObject* GetMetaTableObject(const char* szName, int iType);
	/*74 - 296*/virtual GarrysMod::Lua::CLuaObject* GetReturn(int index);
	/*75 - 300*/virtual bool				IsServer(void);
	/*76 - 304*/virtual bool				IsClient(void);
	/*77 - 308*/virtual bool				IsMenu(void);
	/*78 - 312*/virtual void				DestroyObject(GarrysMod::Lua::ILuaObject* pObj);
	/*79 - 316*/virtual GarrysMod::Lua::CLuaObject*  CreateObject(void);
	/*80 - 320*/virtual void				SetMember(GarrysMod::Lua::ILuaObject* pObj0, const char* szName, GarrysMod::Lua::ILuaObject* pObj1);
	/*81 - 324*/virtual void				SetMember(GarrysMod::Lua::ILuaObject* pObj, const char* szName);
	/*82 - 328*/virtual void				SetMember(GarrysMod::Lua::ILuaObject* pObj0, float val, GarrysMod::Lua::ILuaObject* pObj1);
	/*83 - 332*/virtual void				SetMember(GarrysMod::Lua::ILuaObject* pObj, float val);
	/*84 - 336*/virtual void				SetMember(GarrysMod::Lua::ILuaObject* pObj0, GarrysMod::Lua::ILuaObject* pObj1, GarrysMod::Lua::ILuaObject* pObj2);
	/*85 - 340*/virtual GarrysMod::Lua::CLuaObject* GetNewTable(void);
	/*86 - 344*/virtual void				SetType(unsigned char type); // setting the state server menu client.
	/*87 - 348*/virtual void				PushLong(long val);
	/*88 - 352*/virtual int					GetFlags(int iStackPos);
	/*89 - 356*/virtual bool				FindOnObjectsMetaTable(int iStackPos, int dunno);
	/*90 - 360*/virtual bool				FindObjectsOnMetaTable(int iStackPos, int dunno);
	/*91 - 364*/virtual void				SetMemberFast(GarrysMod::Lua::ILuaObject* pObj, int, int);
	/*92 - 368*/virtual int					RunString(const char*, const char*, const char*, bool, bool);
	/*93 - 372*/virtual bool				IsEqual(GarrysMod::Lua::ILuaObject* pObj0, GarrysMod::Lua::ILuaObject* pObj1);
	/*94 - 376*/virtual void				Error(const char*);	
	/*95 - 380*/virtual int					GetStringOrError(int);
	/*96 - 384*/virtual int					RunLuaModule(const char*);
	/*97 - 388*/virtual int					FindAndRunScript(const char*, bool, bool, const char*, bool);
	/*98 - 392*/virtual int					SetPathID(const char*);
	/*99 - 396*/virtual char*				GetPathID(void);
	/*100 - 400*/virtual int				ErrorNoHalt(const char*, ...);
	/*101 - 404*/virtual int				Msg(const char*, ...);
	/*102 - 408*/virtual int				PushPath(const char*);
	/*103 - 412*/virtual int				PopPath(void);
	/*104 - 416*/virtual int				GetPath(void);
	/*105 - 420*/virtual Color				GetColor(int);
	/*106 - 424*/virtual int				PushColor(Color);
	/*107 - 428*/virtual int				GetStack(int, void*);
	/*108 - 432*/virtual int				GetInfo(const char*, void*);
	/*109 - 436*/virtual int				GetLocal(void*, int);
	/*110 - 440*/virtual int				GetUpvalue(int, int);
	/*111 - 444*/virtual int				RunStringEx(const char*, const char*, const char*, bool, bool, bool, bool);
	/*112 - 448*/virtual int				GetDataString(int, void**);
	/*113 - 452*/virtual int				ErrorFromLua(const char*, ...);
	/*114 - 456*/virtual void*				GetCurrentLocation(void);
	/*115 - 460*/virtual int				MsgColor(const Color&, const char*, ...);
	/*116 - 464*/virtual int				GetCurrentFile(void);
	/*117 - 468*/virtual int				CompileString(void);
	/*118 - 472*/virtual int				CallFunctionProtected(int iStackPos, int iNumReturnValues, bool);
	/*119 - 476*/virtual int				Require(const char* ModuleDir);
	/*120 - 480*/virtual const char*		GetActualTypeName(int);
	/*121 - 484*/virtual int				PreCreateTable(int, int);
	/*122 - 488*/virtual int				PushPooledString(int);
	/*123 - 492*/virtual int				GetBooledString(int);
	/*124 - 496*/virtual int				AddThreadedCall(ILuaThreadedCall*);
	/*125 - 500*/virtual int				AppendStackTrace(char*, unsigned long);
	/*126 - 504*/virtual int				CreateConVar(const char*, const char*, const char*, int);
	/*127 - 508*/virtual int				CreateConCommand(void);

public:
	CBaseEntity*		GetEntity(int iStackPos);
	void				PushEntity(CBaseEntity* Entity);
public:
#ifdef _WIN32
	lua_State*							m_LuaState;				// 0x4  -  functions from the lua interface use functions from the LuaAPI using this pointer.
	unsigned int						m_uiUNK_000;			// 0x8
	char*								m_UNK_000;				// 0xC
	unsigned int						m_uiUNK_001;			// 0x10
	char								PAD_UNK_000[0x8];		// 0x14       
	char*								m_UNK_001;				// 0x1C
	void*								m_pUNK_000;				// 0x20
	char								PAD_UNK_001[0x4];		// 0x24
	GarrysMod::Lua::CLuaObject*			m_ProtectedFunctionReturns[0x4];	// 0x28->0x34
	GarrysMod::Lua::CLuaObject*			m_TempObjects[0x20];	// 0x38->0xB4
	char								m_cLuaState;			// 0xB8  -  uses the enums Client, Server, Menu.
	CLuaGameCallback*					m_pLuaCallBack;			// 0xBC  -  wow I wish I knew about this before.
	unsigned int						m_uiUNK_002;			// 0xC0
	char								PAD_UNK_003[0x1C];		// 0xC4
	int									m_iCurrentTempObject;	// 0xE0
	GarrysMod::Lua::CLuaObject*			m_Global;				// 0xE4
	GarrysMod::Lua::CLuaObject*			m_LuaObjUNK_001;		// 0xE8
	int									m_iNumMetaTables;		// 0xEC
	GarrysMod::Lua::CLuaObject*			m_MetaTables[0xFF];		// 0xF0->0x4FC  -  Referenced in PushMetaTable.
	// size - 0x500
#endif
};

#endif