#ifndef INTERFACES_H
#define INTERFACES_H

#ifdef _WIN32
#pragma once
#endif
#include "include/baseinclude.h"
#include "Source SDK/tier1/interface.h"
#include "LUA/ILuaShared.h"
class IMemAlloc;
class IServerGameEnts;
class IVEngineServer;
class IServerGameDLL;
class IServerGameClients;
class IServerDLLSharedAppSystems;
class IServerGameTags;
class CLuaNetworkedVars;
class CLuaShared;
namespace GarrysMod
{
	namespace Lua
	{
		class ILuaBase;
	};
};
class Interfaces
{
public:
	Interfaces();
	void _SetupInterfaces();
private:
	void	GetInterfaceRegistries();
	void	GetInterfaces();
	void	FindOtherInterfaces();

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

	CLuaShared* LuaShared() { return m_pLuaShared; }
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
	CLuaShared* m_pLuaShared;
public:
	// GMod & GMod Lua shit
	CLuaNetworkedVars* g_LuaNetworkedVars;
	GarrysMod::Lua::ILuaBase* g_Lua;
};
extern "C"
extern Interfaces* g_pInterfaces;
#endif