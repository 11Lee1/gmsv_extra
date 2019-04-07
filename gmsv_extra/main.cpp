#include "interfaces.h" // interfaces.
#include "include.h"
#include "Source SDK/engine/baseserver.h"
#include "Hooks/hook.h"

Interfaces* g_pInterfaces = nullptr;
Hooks* hooks = nullptr;
IMemAlloc* g_pMemAlloc = nullptr;

#define __INJECT
#define MODULENAME "gmsv_extra_win32"
void AttachConsole(char const* name);
void Loop();
void main();
void detatch(HANDLE thread);



#ifdef __INJECT
BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { 
	static HANDLE thread = nullptr;

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr);
	if (ul_reason_for_call == DLL_PROCESS_DETACH) 
		detatch(thread);

	return true;
}
#else
HANDLE thread = nullptr;
GMOD_MODULE_OPEN()
{
	AttachConsole("Console");
	thread = CreateThread(nullptr,0, (LPTHREAD_START_ROUTINE)main, GetModuleHandleA(MODULENAME), 0, nullptr);
	return 1;
}

GMOD_MODULE_CLOSE()
{
	detatch(thread);
	return 1;
}
#endif // __INJECT








void AttachConsole(char const* name) {
	AllocConsole();
	FILE* fp;
	fp = freopen("CONOUT$", "w", stdout);

	SetConsoleTitleA(name);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x7);
}

void Loop() {

	do {

		auto luanetworkvars = g_pInterfaces->LuaNetworkedVars();
		int entitycnt = g_pInterfaces->EngineServer()->GetEntityCount();
		for (int i = 1; i < entitycnt; i++)
		{
			edict_t* entedict = g_pInterfaces->EngineServer()->PEntityOfEntIndex(i);
			if (entedict) {
				CBaseEntity* ent = (CBaseEntity*)entedict->GetUnknown();
				if (ent && ent->IsPlayer()) {
					printf("ent %s:    0x%X\n", ent->m_iClassname, ent);
				}
			}
		}
		Sleep((int)(1000 * g_pInterfaces->Globals()->interval_per_tick)); // who cares we just want to loop shit for it's values etc
	} while (1);
}

void main() {
#ifdef __INJECT
	AttachConsole("Console");
#endif
	g_pInterfaces = new Interfaces();
	g_pMemAlloc = g_pInterfaces->MemAlloc();
	hooks = new Hooks();


	//IVEngineServer::MessageEnd contains pointer to sv (CBaseServer) + 230
	CBaseServer* baseserver = *(CBaseServer**)((*(unsigned int**)g_pInterfaces->EngineServer())[44]/*MessageEnd*/ + 0xE5 + 0x1);
	CBaseClient* xd = baseserver->m_Clients[0];
	xd->SetName("XDXDdsa");

	CNetChan* test1 = (CNetChan*)g_pInterfaces->EngineServer()->GetPlayerNetInfo(1);  // fix cnetchan
	QAngle lol = g_pInterfaces->LuaNetworkedVars()->GetNWAngle((CBaseEntity*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(1)->GetUnknown(), "test");

	//Loop();
}
void detatch(HANDLE thread) {
	if (!thread)
		return;
	hooks->~Hooks();
	g_pInterfaces->~Interfaces();
	if (TerminateThread(thread, 0)) {
		g_pInterfaces->ConColorMsg(1, Color(255, 0, 0), "terminating thread\n");
	}
}