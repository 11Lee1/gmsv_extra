#include "include.h"




#define ___DLL
#ifdef ___DLL
#define __INJECT


#ifdef __INJECT
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

/*

	do stuff for gm_module_open here later.

*/


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
