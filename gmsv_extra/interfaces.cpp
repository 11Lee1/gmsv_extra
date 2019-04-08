#include "interfaces.h"
#include <regex>
#include "util/util.h"
#include "Source SDK/server/iplayerinfo.h"
#include "Source SDK/tier1/color.h"

IMemAlloc* g_pMemAlloc = nullptr;
Interfaces* g_pInterfaces = nullptr;
#define PRINT_PTRCHECK(name,p)																				\
	if(!p)																									\
		printf("failed getting %s: returned nullptr\n",name);			\
	else																									\
		printf("found %s: 0x%X\n", name, p);							\


#define DLL_IMPORT extern "C" __declspec(dllimport)

void Interfaces::PrintInterfaceNames(char const* Module, InterfaceReg* reg) {
	for (reg; reg; reg = reg->m_pNext) {
		printf("%s ---> %s\n", Module, reg->m_pName);
	}
}
Interfaces::Interfaces() {
	*(void**)&ConColorMsg = GetProcAddress(GetModuleHandleA("tier0.dll"), "ConColorMsg");
	printf("Setting up interfaces \n");
	_SetupInterfaces();
}
Interfaces::~Interfaces() {

}
void Interfaces::_SetupInterfaces() {
	GetInterfaceRegistries();
	GetInterfaces();
	FindOtherInterfaces();
}

void Interfaces::GetInterfaceRegistries() {
	m_pServerDLLInterfaceReg = GetInterfaceReg("server.dll");
	PRINT_PTRCHECK("server.dll Interface registry", m_pServerDLLInterfaceReg);
	PrintInterfaceNames("server.dll", m_pServerDLLInterfaceReg);

	m_pEngineDLLInterfaceReg = GetInterfaceReg("engine.dll");
	PRINT_PTRCHECK("engine.dll Interface registry", m_pEngineDLLInterfaceReg);
	PrintInterfaceNames("server.dll", m_pEngineDLLInterfaceReg);

	m_pvstdlibDLLInterfaceReg = GetInterfaceReg("vstdlib.dll");
	PRINT_PTRCHECK("vstdlib.dll Interface registry", m_pvstdlibDLLInterfaceReg);
	PrintInterfaceNames("vstdlib.dll", m_pvstdlibDLLInterfaceReg);

	m_pFileSystem_stdioInterfaceReg = GetInterfaceReg("filesystem_stdio.dll");
	PRINT_PTRCHECK("filesystem_stdio.dll Interface registry", m_pFileSystem_stdioInterfaceReg);
	PrintInterfaceNames("filesystem_stdio.dll", m_pFileSystem_stdioInterfaceReg);
}
void Interfaces::GetInterfaces() {
	m_pServerEnts = (IServerGameEnts*)GetInterface("server.dll", "ServerGameEnts001");
	PRINT_PTRCHECK("ServerGameEnts001", m_pServerEnts);

	m_pEngineServer = (IVEngineServer*)GetInterface("engine.dll", "VEngineServer021");
	PRINT_PTRCHECK("VEngineServer021", m_pEngineServer);

	m_pServerGameDLL = (IServerGameDLL*)GetInterface("server.dll", "ServerGameDLL009");
	PRINT_PTRCHECK("ServerGameDLL009", m_pServerGameDLL);

	m_pServerGameClients = (IServerGameClients*)GetInterface("server.dll", "ServerGameClients004");
	PRINT_PTRCHECK("ServerGameClients004", m_pServerGameClients);

	m_pServerDLLSharedAppSystems = (IServerDLLSharedAppSystems*)GetInterface("server.dll", "VServerDllSharedAppSystems001");
	PRINT_PTRCHECK("VServerDllSharedAppSystems001", m_pServerDLLSharedAppSystems);

	m_pServerGameTags = (IServerGameTags*)GetInterface("server.dll", "ServerGameTags001");
	PRINT_PTRCHECK("ServerGameTags001", m_pServerGameTags);

	m_pLuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");
	PRINT_PTRCHECK("LUASHARED003", m_pLuaShared);

	m_pStaticPropMgr = (IStaticPropMgrServer*)GetInterface("engine.dll", "StaticPropMgrServer002");
	PRINT_PTRCHECK("StaticPropMgrServer002", m_pStaticPropMgr);

	m_pEngineTrace = (IEngineTrace*)GetInterface("engine.dll", "EngineTraceServer003");
	PRINT_PTRCHECK("EngineTraceServer003", m_pEngineTrace);

	m_pPlayerInfoManager = (IPlayerInfoManager*)GetInterface("server.dll", "PlayerInfoManager002");
	PRINT_PTRCHECK("PlayerInfoManager002", m_pPlayerInfoManager);

	m_pCVar = (ICvar*)GetInterface("vstdlib.dll", "VEngineCvar004");
	PRINT_PTRCHECK("VEngineCvar004", m_pCVar);

	m_pNetworkStringTableContainer = (INetworkStringTableContainer*)GetInterface("engine.dll", "VEngineServerStringTable001");
	PRINT_PTRCHECK("VEngineServerStringTable001", m_pNetworkStringTableContainer);


	if (m_pLuaShared)
		g_Lua = (GarrysMod::Lua::ILuaBase*)LuaShared()->GetLuaInterface(1); // server

	PRINT_PTRCHECK("g_Lua", g_Lua);
}

void Interfaces::FindOtherInterfaces() {

	gpGlobals = Globals();


#ifdef _WIN32 
	m_pMemAlloc = GetProcAddress(GetModuleHandleA("tier0.dll"), "g_pMemAlloc");



	// until I can find a better method.
	uintptr_t GetNetworkedIntFn = Util::Pattern::FindPattern("server.dll", "55 8B EC 8B 45 08 56 50 8B 48 48 8B 11 FF 92 ? ? ? ? FF 05 ? ? ? ? 6A 01 6A 01 E8 ? ? ? ? 8B 0D ? ? ? ? 8B F0 83 C4 08 8B 01 85 F6 75 35 6A 03 FF 90 ? ? ? ? 8B F0 85 F6 74 66");
	PRINT_PTRCHECK("GetNetworkedInt Function", GetNetworkedIntFn);
	if (GetNetworkedIntFn) {
		g_pLuaNetworkedVars = *(CLuaNetworkedVars**)(GetNetworkedIntFn + 0x72);
		PRINT_PTRCHECK("CLuaNetworkedVars from GetNetworkedInt function", g_pLuaNetworkedVars);
	}

	void* RandomSeed = GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed");
	PRINT_PTRCHECK("RandomSeed Function", RandomSeed);
	if (RandomSeed)
		random = *(CUniformRandomStream**)((uintptr_t)RandomSeed + 0x5);

	PRINT_PTRCHECK("random(CUniformRandomStream) from RandomSeed function", random);

	m_pSv = *(CGameServer**)((*(unsigned int**)this->EngineServer())[44]/*MessageEnd*/ + 0xE5 + 0x1);
	PRINT_PTRCHECK("m_pSv(CGameServer) from CVEngineServer::MessageEnd function", m_pSv);
#endif
	g_pMemAlloc = this->MemAlloc();
}


void* Interfaces::GetInterface(char const* Module, char const* InterfaceName) {
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");

	if (!CreateInterface)
		return nullptr;

	void* pInterface = (void*)CreateInterface(InterfaceName, NULL);

	return pInterface;
}

void* Interfaces::GetInterface(InterfaceReg* Reg, char const* InterfaceName) {
	if (!Reg)
		return nullptr;

	std::regex regexInterfaceName(InterfaceName, std::regex_constants::icase | std::regex_constants::basic);

	for (Reg; Reg; Reg = Reg->m_pNext) {
		if (!Reg->m_pName)
			continue;

		if (std::regex_search(Reg->m_pName, regexInterfaceName))
			return Reg->m_CreateFn;
	}
	return nullptr;
}

InterfaceReg* Interfaces::GetInterfaceReg(char const* Module) {
	void* createinterface = GetProcAddress(GetModuleHandleA(Module), "CreateInterface");
	if (!createinterface)
		return nullptr;

	BYTE OP = *(BYTE*)((uintptr_t)createinterface + 0x4);
	switch (OP)
	{
	case 0xE9: // jmp r16/32
	{
		unsigned short offset2 = *(unsigned short*)((uintptr_t)createinterface + 0x7);
		if (offset2 == 0xFFFF || offset2 == 0x0000)
			return **(InterfaceReg***)((uintptr_t)(((uintptr_t)createinterface + 0x8) + (*(unsigned short*)((uintptr_t)createinterface + 0x5) - offset2)) + 0x6);
		else
			return **(InterfaceReg***)((uintptr_t)(((uintptr_t)createinterface + 0x8) + (*(unsigned int*)((uintptr_t)createinterface + 0x5))) + 0x6);

		break;
	}
	}

	return nullptr;
}




CGlobalVars* Interfaces::Globals() {
	return m_pPlayerInfoManager->GetGlobalVars();
}