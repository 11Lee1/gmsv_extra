#include "hook.h"
#include "../interfaces.h"
#include "../util/vmthook.h"

Hooks::Hooks() {
	h_IServerGameClients = nullptr;
	SetupHooks();
	HookFunctions();
}
Hooks::~Hooks() {
	UnhookFunctions();
	if (h_IServerGameClients)
		h_IServerGameClients->~VMTHook();

	delete this;
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