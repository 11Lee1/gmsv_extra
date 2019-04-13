#ifndef SERVER__UTIL_H
#define SERVER__UTIL_H

#include "../../interfaces.h"
#include "../eiface.h"
class IServerNetworkable;
class CBaseEntity;

void UTIL_Remove(IServerNetworkable *oldObj);
void UTIL_Remove(CBaseEntity *oldObj);

inline bool FStrEq(const char *sz1, const char *sz2)
{
	return (sz1 == sz2 || stricmp(sz1, sz2) == 0);
}

inline edict_t* INDEXENT(int iEdictNum)
{
	return g_pInterfaces->EngineServer()->PEntityOfEntIndex(iEdictNum);
}
#endif