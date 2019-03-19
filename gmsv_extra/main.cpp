#include "include.h"


#define ___DLL
#ifdef ___DLL

void main() {
	Interfaces::_SetupInterfaces();

	IVEngineServer* engineserver = Interfaces::EngineServer();
	if (engineserver) {
		printf("engine server pointer found\n");
		edict_t* entedict = engineserver->PEntityOfEntIndex(1);
		if (entedict) {
			printf("got player edict 0x%X\n", entedict);
		}
		else {
			printf("failed getting player edict\n");
		}
	}
	else {
		printf("failed finding engine server\n");
	}
}

//#define __INJECT
#ifdef __INJECT // note: calling require("extra") in lua will run the module but spit out an via lua

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

#endif

#else
int main() {
	Vector lol(0,0,0);
	Vector lol2(0, 0, 100);

	printf("X: %f      Y: %f      Z: %f\n", lol.x, lol.y, lol.z);

	printf("dist: %f\n", lol.DistTo(lol2));
	Sleep(100000);
	return 1;
}
#endif
