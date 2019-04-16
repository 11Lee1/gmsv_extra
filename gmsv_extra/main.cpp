#include "project/project.h"
HANDLE thread = nullptr;
Hooks* hooks = nullptr;
void main();
void AttachConsole(char const* name);
void detatch(HANDLE thread);

/*

	see project/project.h for everything, not reccomended you touch anything in here.

*/

#define __ATTACH_CONSOLE
#define __INJECT
#ifdef __INJECT
BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { 
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr);
	if (ul_reason_for_call == DLL_PROCESS_DETACH) 
		detatch(thread);

	return true;
}
#else
GMOD_MODULE_OPEN()
{
	thread = CreateThread(nullptr,0, (LPTHREAD_START_ROUTINE)main, GetModuleHandleA(NULL), 0, nullptr);
	return 1;
}

GMOD_MODULE_CLOSE()
{
	detatch(thread);
	return 1;
}
#endif // __INJECT

void main() {
#ifdef __ATTACH_CONSOLE
	AttachConsole("Console");
#endif
	exports::FillExports();
	g_pInterfaces = new Interfaces();
	NetworkstringTableID = g_pInterfaces->NetworkStringTableContainer()->FindTable("networkstring")->GetTableId();
	g_pGModNetMsgReceiver = new GMod_NetReceive();
	g_pGMod_ServerToClient = new GMod_ServerToClient();
	hooks = new Hooks();
	projectMain();
}

void detatch(HANDLE thread) {
	if (!thread)
		return;
	hooks->~Hooks();
	g_pInterfaces->~Interfaces();
	delete g_pGModNetMsgReceiver;
	delete g_pGMod_ServerToClient;
	if (TerminateThread(thread, 0)) {
		printf("terminating thread\n");
	}
}
void AttachConsole(char const* name) {
	AllocConsole();
	FILE* fp;
	fp = freopen("CONOUT$", "w", stdout);

	SetConsoleTitleA(name);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x7);
}