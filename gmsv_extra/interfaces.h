#ifdef _WIN32
#pragma once
#endif

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


	void* _GetInterface(const char* Module, const char* InterfaceName);

public:
	IMemAlloc* MemAlloc() { return m_pMemAlloc; }
	IServerGameEnts* ServerEnts() { return m_pServerEnts; }
	IVEngineServer*	EngineServer() { return m_pEngineServer; }
	IServerGameDLL* ServerGameDLL() { return m_pServerGameDLL; }
	IServerGameClients* ServerGameClients() { return m_pServerGameClients; }
	IServerDLLSharedAppSystems* ServerDLLSharedAppSystems() { return m_pServerDLLSharedAppSystems; }
	IServerGameTags* ServerGameTags() { return m_pServerGameTags; }
private:
	IMemAlloc* m_pMemAlloc;
	IServerGameEnts* m_pServerEnts;
	IVEngineServer* m_pEngineServer;
	IServerGameDLL* m_pServerGameDLL;
	IServerGameClients* m_pServerGameClients;
	IServerDLLSharedAppSystems* m_pServerDLLSharedAppSystems;
	IServerGameTags* m_pServerGameTags;
};

void* Interfaces::_GetInterface(const char* Module, const char* InterfaceName) {
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");

	if (!CreateInterface)
		return nullptr;

	return (void*)CreateInterface(InterfaceName, NULL);
}

void Interfaces::_SetupInterfaces() {
	m_pServerEnts = (IServerGameEnts*)_GetInterface("server.dll", "ServerGameEnts001");
	m_pEngineServer = (IVEngineServer*)_GetInterface("engine.dll", "VEngineServer021");
	m_pServerGameDLL = (IServerGameDLL*)_GetInterface("server.dll", "ServerGameDLL009");
	m_pServerGameClients = (IServerGameClients*)_GetInterface("server.dll", "ServerGameClients004");
	m_pServerDLLSharedAppSystems = (IServerDLLSharedAppSystems*)_GetInterface("server.dll", "VServerDllSharedAppSystems001");
	m_pServerGameTags = (IServerGameTags*)_GetInterface("server.dll", "ServerGameTags001");
}



extern Interfaces* g_pInterfaces = nullptr;