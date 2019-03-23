#define INCLCONSOLE
#include "interfaces.h" // interfaces.
Interfaces* g_pInterfaces = nullptr;
#include "include.h"

#ifdef INCLCONSOLE
void AttachConsole(char const* name) {
	AllocConsole();
	FILE* fp;
	fp = freopen("CONOUT$", "w", stdout);

	SetConsoleTitleA(name);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x7);
}
#endif

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
#ifdef INCLCONSOLE
					printf("ent #%i:  %s      = 0x%X\n",i, ent->m_iClassname, ent);
					if (ent->IsPlayer()) {
						printf("studiohdr = 0x%X\n", &ent->m_pStudioHdr);
					}
#endif
				}
			}
		}
		Sleep(1000); // who cares we just want to loop shit for it's values etc
	} while (1);
}

int main() {
#ifdef INCLCONSOLE
	AttachConsole("Console");
#endif
	g_pInterfaces = new Interfaces();

	Loop();

	return 1;
}

#define __INJECT
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
	main();
	return 1;
}
//lua_openscript sv.lua
GMOD_MODULE_CLOSE()
{
	return 1;
}

#endif // __INJECT