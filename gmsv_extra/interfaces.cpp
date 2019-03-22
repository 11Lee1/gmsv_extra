#include "interfaces.h"
#include <regex>
#include "util/util.h"
void Interfaces::_SetupInterfaces() {
	GetInterfaceRegistries();
	GetInterfaces();
	FindOtherInterfaces();
}

void Interfaces::GetInterfaceRegistries() {
	m_pServerDLLInterfaceReg = GetInterfaceReg("server.dll");
	m_pEngineDLLInterfaceReg = GetInterfaceReg("engine.dll");
}
void Interfaces::GetInterfaces() {
	m_pServerEnts = (IServerGameEnts*)GetInterface("server.dll", "ServerGameEnts001");
	m_pEngineServer = (IVEngineServer*)GetInterface("engine.dll", "VEngineServer021");
	m_pServerGameDLL = (IServerGameDLL*)GetInterface("server.dll", "ServerGameDLL009");
	m_pServerGameClients = (IServerGameClients*)GetInterface("server.dll", "ServerGameClients004");
	m_pServerDLLSharedAppSystems = (IServerDLLSharedAppSystems*)GetInterface("server.dll", "VServerDllSharedAppSystems001");
	m_pServerGameTags = (IServerGameTags*)GetInterface("server.dll", "ServerGameTags001");
	m_pLuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");

	if (m_pLuaShared)
		g_Lua = (GarrysMod::Lua::ILuaBase*)LuaShared()->GetLuaInterface(1); // server
}

void Interfaces::FindOtherInterfaces() {


#ifdef _WIN32
	// until I can find a better method.
	g_LuaNetworkedVars = **(CLuaNetworkedVars***)(Util::Pattern::FindPattern("server.dll", "55 8B EC 8B 45 08 56 50 8B 48 48 8B 11 FF 92 ? ? ? ? FF 05 ? ? ? ? 6A 01 6A 01 E8 ? ? ? ? 8B 0D ? ? ? ? 8B F0 83 C4 08 8B 01 85 F6 75 35 6A 03 FF 90 ? ? ? ? 8B F0 85 F6 74 66")/*Entity__GetNetworkedInt*/ + 0x72);
#endif

}


void* Interfaces::GetInterface(char const* Module, char const* InterfaceName) {
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");

	if (!CreateInterface)
		return nullptr;

	void* pInterface = (void*)CreateInterface(InterfaceName, NULL);
#ifdef INCLCONSOLE
	printf("found interface %s: 0x%X\n", InterfaceName, pInterface);
#endif

	return pInterface;
}

void* Interfaces::GetInterface(InterfaceReg* Reg, char const* InterfaceName) {
	if (!Reg) {
#ifdef INCLCONSOLE
		printf("no interface registry returning nullptr\n");
#endif

		return nullptr;
	}

	std::regex regexInterfaceName(InterfaceName, std::regex_constants::icase | std::regex_constants::basic);

	for (Reg; Reg; Reg = Reg->m_pNext) {
		if (!Reg->m_pName)
			continue;

		if (std::regex_search(Reg->m_pName, regexInterfaceName)) {
#ifdef INCLCONSOLE
			printf("matched interface name \"%s\" with \"%s\":  0x%X\n", Reg->m_pName, InterfaceName, Reg->m_CreateFn);
#endif
			return Reg->m_CreateFn;
		}
	}
#ifdef INCLCONSOLE
	printf("failed finding interface with name: %s\n", InterfaceName);
#endif

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
