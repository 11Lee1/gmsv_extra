#include "hook.h"
#include "../interfaces.h"
#include "../util/vmthook.h"

Hooks::Hooks() {
	h_IServerGameClients = nullptr;
}
void Hooks::SetupHooks() {
	h_IServerGameClients = new VMTHook(g_pInterfaces->ServerGameClients());
}
void Hooks::HookFunctions() {
	// IServerGameClients
	HookClientConnect();
}
void Hooks::UnhookFunctions() {
	// IServerGameClients
	UnhookClientConnect();
}