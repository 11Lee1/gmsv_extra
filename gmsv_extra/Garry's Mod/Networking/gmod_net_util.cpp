#include "gmod_net_util.h"
#include "../../interfaces.h"
#include "../../Source SDK/networkstringtabledefs.h"

int NetworkstringTableID = NULL;

void GUTIL_AddNetworkString(char const* name) {
	INetworkStringTable* nwstringtbl = g_pInterfaces->NetworkStringTableContainer()->GetTable(NetworkstringTableID);
	if (nwstringtbl) {
		nwstringtbl->GetTableId();
		nwstringtbl->AddString(true,name);
	}
}