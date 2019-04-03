#ifndef INTERFACES_H
#define INTERFACES_H

#ifdef _WIN32
#pragma once
#endif
#include "include/baseinclude.h"
#include "Source SDK/tier1/interface.h"
#include "Garry's Mod/LUA/ILuaShared.h"
class IMemAlloc;
class IServerGameEnts;
class IVEngineServer;
class IServerGameDLL;
class IServerGameClients;
class IServerDLLSharedAppSystems;
class IServerGameTags;
class CLuaNetworkedVars;
class CLuaShared;
class CGlobalVars;
class CUniformRandomStream;
class IStaticPropMgrServer;
class IEngineTrace;
class IPlayerInfoManager;
class ICvar;
class IKeyValuesSystem;
class INetworkStringTableContainer;
namespace GarrysMod
{
	namespace Lua
	{
		class ILuaBase;
	};
};
class Color;
class Interfaces
{
public:
	Interfaces();
	~Interfaces();
	void _SetupInterfaces();
private:
	void	GetInterfaceRegistries();
	void	GetInterfaces();
	void	FindOtherInterfaces();

	void*	GetInterface(char const* Module, char const* InterfaceName);
	void*	GetInterface(InterfaceReg* Reg, char const* InterfaceName); // if you dont know/care about the version.
	InterfaceReg*	GetInterfaceReg(char const* Module);
	void	PrintInterfaceNames(char const* Module, InterfaceReg* reg);

public:
	IMemAlloc* MemAlloc() { return *(IMemAlloc**)m_pMemAlloc; }
	IServerGameEnts* ServerEnts() { return m_pServerEnts; }
	IVEngineServer*	EngineServer() { return m_pEngineServer; }
	IServerGameDLL* ServerGameDLL() { return m_pServerGameDLL; }
	IServerGameClients* ServerGameClients() { return m_pServerGameClients; }
	IServerDLLSharedAppSystems* ServerDLLSharedAppSystems() { return m_pServerDLLSharedAppSystems; }
	IServerGameTags* ServerGameTags() { return m_pServerGameTags; }
	IStaticPropMgrServer* StaticPropMgr() { return staticpropmgr; }
	IEngineTrace* EngineTrace() { return enginetrace; }

	CLuaShared* LuaShared() { return m_pLuaShared; }
	CLuaNetworkedVars* LuaNetworkedVars() { return *(CLuaNetworkedVars**)g_pLuaNetworkedVars; }
	CUniformRandomStream*	Random() { return *(CUniformRandomStream**)random; }
	IPlayerInfoManager*	PlayerInfoMgr() { return playerinfomgr; }
	CGlobalVars*  Globals();
	INetworkStringTableContainer* NetworkStringTableContainer() { return nwstringtbl; }
	ICvar* CVar() { return cvar; }
	IKeyValuesSystem* KeyValuesSystem() { return keyvaluessystem; }
private:
	// Interface registries 
	InterfaceReg* m_pServerDLLInterfaceReg;
	InterfaceReg* m_pEngineDLLInterfaceReg;
	InterfaceReg* m_pvstdlibDLLInterfaceReg;
	InterfaceReg* m_pFileSystem_stdioInterfaceReg;

	// Interfaces
private:
	void* m_pMemAlloc;
	IServerGameEnts* m_pServerEnts;
	IVEngineServer* m_pEngineServer;
	IServerGameDLL* m_pServerGameDLL;
	IServerGameClients* m_pServerGameClients;
	IServerDLLSharedAppSystems* m_pServerDLLSharedAppSystems;
	IServerGameTags* m_pServerGameTags;
	CLuaShared* m_pLuaShared;
	IStaticPropMgrServer* staticpropmgr;
	IEngineTrace* enginetrace;
	INetworkStringTableContainer* nwstringtbl;
	void* random;
	IPlayerInfoManager*	playerinfomgr;
	ICvar* cvar;

	IKeyValuesSystem* keyvaluessystem;

	// globals
	void* gpGlobals;

	// GMod & GMod Lua shit
	void* g_pLuaNetworkedVars;
public:
	// GMod & GMod Lua shit
	GarrysMod::Lua::ILuaBase* g_Lua;

	void(*ConColorMsg)(int, const Color&, const tchar*, ...);
};
extern Interfaces* g_pInterfaces;
#endif

/*

server.dll ---> VSERVERCHOREOTOOLS001
server.dll ---> VSERVERTOOLS002
server.dll ---> VSERVERTOOLS001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> GameMovement001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> PluginHelpersCheck001
server.dll ---> BotManager001
server.dll ---> PlayerInfoManager002
server.dll ---> PlayerInfoManager001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> HLTVDirector001
server.dll ---> VServerDllSharedAppSystems001
server.dll ---> ServerGameClients004
server.dll ---> ServerGameClients003
server.dll ---> ServerGameEnts001
server.dll ---> ServerGameDLL009
server.dll ---> ServerGameDLL008
server.dll ---> ServerGameTags001
server.dll ---> IEffects001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001
server.dll ---> ServerGameTags001



engine.dll ---> VEngineVGui001
engine.dll ---> VSERVERENGINETOOLS001
engine.dll ---> VCLIENTENGINETOOLS001
engine.dll ---> VTOOLFRAMEWORKVERSION002
engine.dll ---> VENGINETOOLFRAMEWORK003
engine.dll ---> VENGINETOOL003
engine.dll ---> XboxSystemInterface001
engine.dll ---> VProfExport001
engine.dll ---> VoiceServer002
engine.dll ---> VENGINE_GAMEUIFUNCS_VERSION005
engine.dll ---> VENGINE_HLDS_API_VERSION002
engine.dll ---> VENGINE_LAUNCHER_API_VERSION004
engine.dll ---> StaticPropMgrServer002
engine.dll ---> StaticPropMgrClient004
engine.dll ---> SpatialPartition001
engine.dll ---> VEngineRandom001
engine.dll ---> VEngineServerStringTable001
engine.dll ---> VEngineClientStringTable001
engine.dll ---> VModelInfoClient006
engine.dll ---> VModelInfoServer004
engine.dll ---> VModelInfoServer003
engine.dll ---> VENGINE_MATCHMAKING_VERSION001
engine.dll ---> GAMEEVENTSMANAGER001
engine.dll ---> GAMEEVENTSMANAGER002
engine.dll ---> EngineTraceClient003
engine.dll ---> EngineTraceServer003
engine.dll ---> DownloadSystem001
engine.dll ---> VCvarQuery001
engine.dll ---> VEngineServer021
engine.dll ---> ServerUploadGameStats001
engine.dll ---> GameServerData001
engine.dll ---> ISERVERPLUGINHELPERS001
engine.dll ---> VEngineRenderView014
engine.dll ---> VEngineShadowMgr002
engine.dll ---> VEngineEffects001
engine.dll ---> VEngineModel016
engine.dll ---> VPhysicsDebugOverlay001
engine.dll ---> VDebugOverlay003
engine.dll ---> VEngineClient013
engine.dll ---> VEngineClient015
engine.dll ---> IEngineSoundServer003
engine.dll ---> IEngineSoundClient003

*/