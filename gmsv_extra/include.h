#ifndef INCLUDE_H
#define INCLUDE_H
#ifdef _WIN32
#pragma once
#endif
#include "include/baseinclude.h"
#include "Source SDK/const.h"
// tier 0 
#include "Source SDK/tier0/commonmacros.h"
#include "Source SDK/tier0/basetypes.h"
#include "Source SDK/tier0/annotations.h"
#include "Source SDK/tier0/dbgflag.h"
#include "Source SDK/tier0/platform.h"
#include "Source SDK/tier0/dbg.h"
#include "Source SDK/tier0/memalloc.h"
#include "Source SDK/tier0/l2cache.h"
// tier 1
#include "Source SDK/tier1/color.h"
#include "Source SDK/tier1/utlflags.h"
#include "Source SDK/tier1/checksum_crc.h"
#include "Source SDK/tier1/checksum_md5.h"
#include "Source SDK/tier1/interface.h"

#include "Source SDK/appframework/IAppSystem.h"
#include "Source SDK/engine/engine_launcher_api.h"


// mathlib
#include "Source SDK/mathlib/mathlib.h"

//more tier 1 stuff
#include "Source SDK/tier1/bitbuff.h"
#include "Source SDK/eiface.h"

#include "Source SDK/usercmd.h"

#include "Source SDK/server/baseentity.h"
#include "Source SDK/tier1/utlrbtree.h"
#include "Source SDK/tier1/utlmap.h"

#include "LUA/LuaInterface.h"
#include "GLUA/LuaObject/ILuaObject.h"
#include "GLUA/LuaNetworkedVars.h"
#endif