#ifndef INCLUDE_H
#define INCLUDE_H
#ifdef _WIN32
#pragma once
#endif
// for now.
#include "include/baseinclude.h"


// mind aswell make this like cbase.h

#include "Source SDK/const.h"
// tier 0 
#include "Source SDK/tier0/commonmacros.h"
#include "Source SDK/tier0/basetypes.h"
#include "Source SDK/tier0/annotations.h"
#include "Source SDK/tier0/platform.h"
#include "Source SDK/tier0/dbgflag.h"
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
#include "Source SDK/tier1/utlrbtree.h"
#include "Source SDK/tier1/utlmap.h"
#include "Source SDK/eiface.h"

#include "Source SDK/usercmd.h"

#include "Source SDK/tier1/KeyValues.h"
#include "Garry's Mod/LUA/LuaInterface.h"


#include "Garry's Mod/GLUA/CGMODDataTable.h"
#include "Garry's Mod/GLUA/LuaNetworkedVars.h"
#include "Garry's Mod/GLUA/CScriptedEntity.h"


#include "Source SDK/server/gmod/gmodplayer.h"
#include "Source SDK/server/gmod/weaponswep.h"
#include "Source SDK/server/gmod/sentanim.h"
#include "Source SDK/engine/net_chan.h"

#include "Source SDK/engine/sv_client.h"
#include "Source SDK/engine/server.h"
#endif