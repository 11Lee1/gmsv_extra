#include "exports.h"
#include "win32/lua_shared/lua_shared exports.h"

void exports::FillExports() {
#ifdef LUA_SHARED__EXPORTS_H
	lua_shared::FillExports();
#endif
}