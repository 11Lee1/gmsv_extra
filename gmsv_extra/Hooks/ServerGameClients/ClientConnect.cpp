#include "../hook.h"
#include "../../Source SDK/eiface.h"
#include <stdio.h>

typedef bool(__thiscall* ServerGameClients__ClientConnectFn)(IServerGameClients*, edict_t* /*pEntity*/, char const*/*pszName*/, char const*/*pszAddress*/, char*/*reject*/, int/*maxrejectlen*/);
ServerGameClients__ClientConnectFn orgServerGameClients__ClientConnect = nullptr;

bool __fastcall hookServerGameClients__ClientConnect(IServerGameClients* thisptr, void* edx, edict_t* pEntity, char const* pszName, char const* pszAddress, char* reject, int maxrejectlen) {
	printf("client \"%s\" is connecting\n", pszName);
	return orgServerGameClients__ClientConnect(thisptr, pEntity, pszName, pszAddress, reject, maxrejectlen);
}
void Hooks::HookClientConnect() { 
	if(!orgServerGameClients__ClientConnect)
		orgServerGameClients__ClientConnect = (ServerGameClients__ClientConnectFn)h_IServerGameClients->HookFunction(1/*function index*/, hookServerGameClients__ClientConnect);
}
void Hooks::UnhookClientConnect() {
	if (orgServerGameClients__ClientConnect) {
		orgServerGameClients__ClientConnect = nullptr;
		h_IServerGameClients->UnhookFunction(1);
	}
}