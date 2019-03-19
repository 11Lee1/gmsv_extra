#ifdef _WIN32
#pragma once
#endif

#include "Source SDK/tier1/interface.h"

class IMemAlloc;
class IServerGameEnts;
class IVEngineServer;
class IServerGameDLL;
class IServerGameClients;
class IServerDLLSharedAppSystems;
class IServerGameTags;
namespace Interfaces
{
	namespace _I
	{
		IMemAlloc* _memalloc;
		IServerGameEnts* ServerEnts;
		IVEngineServer* EngineServer;
		IServerGameDLL* ServerGameDLL;
		IServerGameClients* ServerGameClients;
		IServerDLLSharedAppSystems* ServerDLLSharedAppSystems;
		IServerGameTags* ServerGameTags;
	};

	IMemAlloc* MemAlloc() { return _I::_memalloc; }


	IVEngineServer*	EngineServer() { return _I::EngineServer; }
	IServerGameDLL* ServerGameDLL() { return _I::ServerGameDLL; }
	IServerGameEnts* ServerEnts() { return _I::ServerEnts; }
	IServerGameClients* ServerGameClients() { return _I::ServerGameClients; }
	IServerDLLSharedAppSystems* ServerDLLSharedAppSystems() { return _I::ServerDLLSharedAppSystems; }
	IServerGameTags* ServerGameTags() { return _I::ServerGameTags; }


	void* _GetInterface(const char* Module, const char* InterfaceName) {
		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");

		if (!CreateInterface)
			return nullptr;

		return (void*)CreateInterface(InterfaceName, NULL);
	}

	void _SetupInterfaces() {
		_I::EngineServer = (IVEngineServer*)_GetInterface("engine.dll", "VEngineServer021");
		_I::ServerGameDLL = (IServerGameDLL*)_GetInterface("server.dll", "ServerGameDLL009");
		_I::ServerEnts = (IServerGameEnts*)_GetInterface("server.dll", "ServerGameEnts001");
		_I::ServerGameClients = (IServerGameClients*)_GetInterface("server.dll", "ServerGameClients004");
		_I::ServerDLLSharedAppSystems = (IServerDLLSharedAppSystems*)_GetInterface("server.dll", "VServerDllSharedAppSystems001");
		_I::ServerGameTags = (IServerGameTags*)_GetInterface("server.dll", "ServerGameTags001");
	}
};