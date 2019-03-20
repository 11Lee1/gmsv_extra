#define INCLCONSOLE
#define __DLL


#include "include.h"




#ifdef __DLL

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
		edict_t* entedict = engineserver->PEntityOfEntIndex(1);
		
		if (entedict) {
			CBaseEntity* player = (CBaseEntity*)entedict->GetUnknown();
			if (player && player->IsPlayer()) {
#ifdef INCLCONSOLE
				printf("player = 0x%X\n", player);
#endif
			}
		}



		Sleep(1000); // who cares we just want to loop shit for it's values etc
	} while (1);
}

int main() {
#ifdef INCLCONSOLE
	AttachConsole("Console");
#endif
	g_pInterfaces = new Interfaces;
	g_pInterfaces->_SetupInterfaces();

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
#else
int main() {
	Vector lol(0,0,0);
	Vector lol2(0, 0, 100);

	printf("X: %f      Y: %f      Z: %f\n", lol.x, lol.y, lol.z);

	printf("dist: %f\n", lol.DistTo(lol2));
	Sleep(100000);
	return 1;
}
#endif // __DLL