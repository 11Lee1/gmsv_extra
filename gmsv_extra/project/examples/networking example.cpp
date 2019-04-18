#include "networking example.h"
#include "../../everything.h"

// Net messages:
void TestCallBack(edict_t* pPlayer) {
	char* str = net_ReadString();
	printf("out: %s\n", str);
}

void Examples::NetWorking::NetMessageExample() {
	// Sending net messages:
	unsigned short Test_send_ID = util_AddNetworkString("Test send");
	// Add the network string so we can start the netmessage. 
	/*
	* setting reliable to false so the netmessage gets sent on the same packet as the SVC_UpdateStringTable 
	* (networkstring dictionary update) net message, since we're doing this all at the same time.
	* Also if the packet with the dictionary update has already been sent/arrived then you can
	* set it to false since setting "unreliable" to true creates a new packet, and the packet containing the
	* SVC_UpdateStringTable netmessage will get processed and the dictionary will get updated in time before
	* the SVC_GMod_ServerToClient netmessage gets processed.
	*/
	net_Start(Test_send_ID, true);	// net_Start can be initialized with either a network string ID or cstring. 
	{ // you don't need to wrap this, I just find it easier to read.
		net_WriteString("Test Net Message");
		net_WriteVector(Vector(1002, 2001, 3000));
		net_WriteFloat(0.1337f);
	}
	net_Broadcast(); // send to all players on the server.
	// net_Send works with both CBaseEntity & CBaseClient object pointers, aswell as CRecipientFilter.


	// Receiving net messages:
	util_AddNetworkString("Test Receive");			// Add a networkstring for our receiving net message.
	net_Receive("Test Receive", TestCallBack);		// can be initialized with either a network string ID or cstring. 
	// if using a cstring and the string doesn't exist it will add a networkstring with that name, feel free to edit the
	// macro if you don't like it.
}

// Network Vars:
void Examples::NetWorking::NetWorkVarExample() {
	CBaseEntity* ply = UTIL_Entity(1); // Entity indices ranging from 1-maxplayercount are reserved for players.

	g_pInterfaces->LuaNetworkedVars()->SetNWInt(ply, "Example Name", 100);					// setting NWVars doesn't care if the Name matches the type.
	int example_out = g_pInterfaces->LuaNetworkedVars()->GetNWInt(ply, "Example Name");		// getting NWVars cares if the name matches the type to make it more friendly to use here.
}