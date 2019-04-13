#ifndef PROJECT_H
#define PROJECT_H
#include "../interfaces.h"
#include "../include.h"
#include "../Hooks/hook.h"
void TestCallBack(edict_t* pPlayer) {
	char* str = net_ReadString();
	printf("out: %s\n", str);

}

#include "../util/util.h"
void projectMain() {
	uintptr_t UpdateEntityVars = Util::Pattern::FindPattern("server.dll", "55 8B EC 51 57 8B 7D 08 89 4D FC");

	CGlobalEntityList* Entlist = **(CGlobalEntityList***)(UpdateEntityVars + 0x54 + 0x2);
	printf("thing = 0x%X\n", Entlist);


	printf("player = 0x%X\n", Entlist->FindEntityByClassname(Entlist->FirstEnt(), "player"));
	util_AddNetworkString("Test send");
	util_AddNetworkString("Test Receive");

	net_Receive("Test Receive", TestCallBack);
	// setting reliable to false so the netmessage gets sent on the same packet as the SVC_UpdateStringTable 
	// (networkstring dictionary update) net message, since we're doing this all at the same time.
	// Also if the packet with the dictionary update has already been sent/arrived then you can
	// set it to false since setting "unreliable" to true creates a new packet, and the packet containing the
	// SVC_UpdateStringTable netmessage will get processed and the dictionary will get updated in time before
	// the SVC_GMod_ServerToClient netmessage gets processed.
	net_Start("Test send", true);
	{
		net_WriteString("Test Net Message");
		net_WriteVector(Vector(1002, 2001, 3000));
		net_WriteFloat(0.1337f);
	}
	net_Broadcast();
}

#endif