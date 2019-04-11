#include "../hook.h"
#include "../../Source SDK/eiface.h"
#include "../../Garry's Mod/Networking/ClientToServer.h"
#include <stdio.h>

typedef void(__thiscall* ServerGameClients__GMOD_ReceiveClientMessageFn)(IServerGameClients*, int /*dunno*/, edict_t* /*pPlayer*/, bf_read* /*data*/, int /*length*/);
ServerGameClients__GMOD_ReceiveClientMessageFn orgServerGameClients__GMOD_ReceiveClientMessage = nullptr;

void __fastcall hookServerGameClients__GMOD_ReceiveClientMessage(IServerGameClients* thisptr, void* edx, int dunno, edict_t* pPlayer, bf_read* data, int length) {
	g_pGModNetMsgReceiver->ProcessNetMsg(dunno, pPlayer, data, length);
	return orgServerGameClients__GMOD_ReceiveClientMessage(thisptr, dunno, pPlayer, data, length);
}
void Hooks::HookGMOD_ReceiveClientMessage() {
	if (!orgServerGameClients__GMOD_ReceiveClientMessage)
		orgServerGameClients__GMOD_ReceiveClientMessage = (ServerGameClients__GMOD_ReceiveClientMessageFn)h_IServerGameClients->HookFunction(18/*function index*/, hookServerGameClients__GMOD_ReceiveClientMessage);
}
void Hooks::UnHookGMOD_ReceiveClientMessage() {
	if (orgServerGameClients__GMOD_ReceiveClientMessage) {
		orgServerGameClients__GMOD_ReceiveClientMessage = nullptr;
		h_IServerGameClients->UnhookFunction(18);
	}
}