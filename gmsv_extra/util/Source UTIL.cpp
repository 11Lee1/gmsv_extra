#include "Source UTIL.h"

#include "../interfaces.h"
#include "../Source SDK/server/baseentity.h"
#include "../Source SDK/server/entitylist.h"


CBaseEntity* UTIL_Entity(int index) {
	return (CBaseEntity*)g_pInterfaces->EntityList()->LookupEntityByNetworkIndex(index);
}