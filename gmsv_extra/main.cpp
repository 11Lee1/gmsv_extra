#include "interfaces.h" // interfaces.
Interfaces* g_pInterfaces = nullptr;
#include "include.h"
#include "Hooks/hook.h"
Hooks* hooks = nullptr;

#define __INJECT
void AttachConsole(char const* name) {
	AllocConsole();
	FILE* fp;
	fp = freopen("CONOUT$", "w", stdout);

	SetConsoleTitleA(name);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x7);
}

void Loop()
{

	do {
		IVEngineServer* engineserver = g_pInterfaces->EngineServer();
		int entitycnt = engineserver->GetEntityCount();
		for (int i = 1; i < entitycnt; i++)
		{
			edict_t* entedict = engineserver->PEntityOfEntIndex(i);
			if (entedict) {
				CBaseAnimating* ent = (CBaseAnimating*)entedict->GetUnknown();
				if (ent && (ent->UsesLua() && !!ent->m_iClassname || ent->IsPlayer()) ) {
					printf("ent #%i:  %s      = 0x%X\n",i, ent->m_iClassname, ent);
					if (ent->IsPlayer()) {
						printf("player #%i: = 0x%X\n", i, ent);
						//printf("usergroup = %s\n", g_pInterfaces->g_LuaNetworkedVars->GetNWString(ent, "usergroup"));
					}
				}
			}
		}
		Sleep(1000); // who cares we just want to loop shit for it's values etc
	} while (1);
}

int main() {
#ifdef __INJECT
	AttachConsole("Console");
#endif
	g_pInterfaces = new Interfaces();
	hooks = new Hooks();
	
	Loop();

	return 1;
}
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
	printf("attaching\n");
	main();
	return 1;
}
//lua_openscript sv.lua
GMOD_MODULE_CLOSE()
{
	hooks->~Hooks();
	g_pInterfaces->~Interfaces();
	printf("unattaching\n");
	return 1;
}

#endif // __INJECT