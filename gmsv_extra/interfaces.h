#ifdef _WIN32
#pragma once
#endif

#include <regex>
#include "include/baseinclude.h"
#include "Source SDK/tier1/interface.h"

class IMemAlloc;
class IServerGameEnts;
class IVEngineServer;
class IServerGameDLL;
class IServerGameClients;
class IServerDLLSharedAppSystems;
class IServerGameTags;

class Interfaces
{
public:
	void _SetupInterfaces();
private:
	void	GetInterfaceRegistries();
	void	GetInterfaces();

	void*	GetInterface(char const* Module, char const* InterfaceName);
	void*	GetInterface(InterfaceReg* Reg, char const* InterfaceName); // if you dont know/care about the version.
	InterfaceReg*	GetInterfaceReg(char const* Module);


public:
	IMemAlloc* MemAlloc() { return m_pMemAlloc; }
	IServerGameEnts* ServerEnts() { return m_pServerEnts; }
	IVEngineServer*	EngineServer() { return m_pEngineServer; }
	IServerGameDLL* ServerGameDLL() { return m_pServerGameDLL; }
	IServerGameClients* ServerGameClients() { return m_pServerGameClients; }
	IServerDLLSharedAppSystems* ServerDLLSharedAppSystems() { return m_pServerDLLSharedAppSystems; }
	IServerGameTags* ServerGameTags() { return m_pServerGameTags; }
private:
	// Interface registries 
	InterfaceReg* m_pServerDLLInterfaceReg;
	InterfaceReg* m_pEngineDLLInterfaceReg;

	// Interfaces
	IMemAlloc* m_pMemAlloc;
	IServerGameEnts* m_pServerEnts;
	IVEngineServer* m_pEngineServer;
	IServerGameDLL* m_pServerGameDLL;
	IServerGameClients* m_pServerGameClients;
	IServerDLLSharedAppSystems* m_pServerDLLSharedAppSystems;
	IServerGameTags* m_pServerGameTags;
};

void Interfaces::_SetupInterfaces() {
	GetInterfaceRegistries();
	GetInterfaces();


	void* test = GetInterface(m_pServerDLLInterfaceReg, "ServerGameEnts");

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
			printf("matched interface name \"%s\" with \"%s\":  0x%X\n", Reg->m_pName, InterfaceName,Reg->m_CreateFn);
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
		if(offset2 == 0xFFFF || offset2 == 0x0000)
			return **(InterfaceReg***)((uintptr_t)(((uintptr_t)createinterface + 0x8) + (*(unsigned short*)((uintptr_t)createinterface + 0x5) - offset2)) + 0x6);
		else
			return **(InterfaceReg***)((uintptr_t)(((uintptr_t)createinterface + 0x8) + (*(unsigned int*)((uintptr_t)createinterface + 0x5))) + 0x6);

		break;
	}
	}

	return nullptr;
}


extern Interfaces* g_pInterfaces = nullptr;