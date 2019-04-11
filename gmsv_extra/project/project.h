#ifndef PROJECT_H
#define PROJECT_H
#include "../interfaces.h"
#include "../include.h"
#include "../Hooks/hook.h"

void TestCallBack(edict_t* pPlayer) {
	char* str = net_ReadString();
	printf("out: %s\n", str);

	net_DisposeString(str);		// so we don't have memory leaks
}

void projectMain() {
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