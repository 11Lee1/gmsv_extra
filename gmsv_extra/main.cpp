#include "interfaces.h" // interfaces.
#include "include.h"
#include "Hooks/hook.h"

Interfaces* g_pInterfaces = nullptr;
Hooks* hooks = nullptr;
HMODULE hModule = nullptr;
HANDLE mainThread = nullptr;


//#define __INJECT
#define MODULENAME "gmsv_extra_win32"
void AttachConsole(char const* name);
void Loop();
int main();



#ifdef __INJECT // note: calling require("extra") in lua will run the module but spit out an error via lua
BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { 
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#else
GMOD_MODULE_OPEN()
{
	AttachConsole("Console");
	mainThread = CreateThread(nullptr,0, (LPTHREAD_START_ROUTINE)main, GetModuleHandleA(MODULENAME), 0, nullptr);
	return 1;
}

GMOD_MODULE_CLOSE()
{
	auto lol = hooks;
	hooks->~Hooks();
	g_pInterfaces->~Interfaces();
	if (TerminateThread(mainThread, 0)) {
		g_pInterfaces->ConColorMsg(1,Color(255,0,0),"terminating thread\n");
	}
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
		int entitycnt = g_pInterfaces->EngineServer()->GetEntityCount();
		for (int i = 1; i < entitycnt; i++)
		{
			edict_t* entedict = g_pInterfaces->EngineServer()->PEntityOfEntIndex(i);
			if (entedict) {
				CBaseEntity* ent = (CBaseEntity*)entedict->GetUnknown();
				if (ent && ent->IsSWEP()) {
					//printf("ent %s:    0x%X\n", ent->m_iClassname, ent);
				}
			}
		}
		Sleep((int)(1000 * g_pInterfaces->Globals()->interval_per_tick)); // who cares we just want to loop shit for it's values etc
	} while (1);
}

int main() {
#ifdef __INJECT
	//AttachConsole("Console");
#endif
	g_pInterfaces = new Interfaces();
	hooks = new Hooks();
	//Loop();

	return 1;
}