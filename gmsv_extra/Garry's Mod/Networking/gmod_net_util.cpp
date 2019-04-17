#include "gmod_net_util.h"
#include "../../interfaces.h"
#include "../../Source SDK/networkstringtabledefs.h"

int NetworkstringTableID = NULL;

unsigned short GUTIL_AddNetworkString(char const* name) {
	INetworkStringTable* nwstringtbl = g_pInterfaces->NetworkStringTableContainer()->GetTable(NetworkstringTableID);
	if (nwstringtbl) {
		return nwstringtbl->AddString(true,name);
	}
	return INVALID_STRING_INDEX;
}