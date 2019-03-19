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
#include "Source SDK/mathlib/math_pfns.h"
#include "Source SDK/mathlib/vector2d.h"
#include "Source SDK/mathlib/vector.h"
#include "Source SDK/mathlib/mathlib.h"
#include "Source SDK/mathlib/vector4d.h"
#include "Source SDK/mathlib/vplane.h"
#include "Source SDK/mathlib/vmatrix.h"
#include "Source SDK/mathlib/compressed_vector.h"

//more tier 1 stuff
#include "Source SDK/tier1/bitbuff.h"
#include "Source SDK/eiface.h"
#include "LUA/LuaInterface.h"
/*
#include "Source SDK/tier1/bitvec.h"
#include "Source SDK/tier1/bitbuf2.h"
#include "Source SDK/tier1/utllinkedlist.h"
#include "Source SDK/tier1/utlmemory.h"
#include "Source SDK/tier1/utlvector.h"
#include "Source SDK/tier1/utlbuffer.h"
*/


#include "Source SDK/usercmd.h"