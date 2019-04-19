#ifndef GMOD_GAMERULES_H
#define GMOD_GAMERULES_H
#include "../hl2mp/hl2mp_gamerules.h"
#include "../../Garry's Mod/GLUA/LuaObject/CLuaObject.h"

/*

	members in inherited by classes are mostlikely incorrect judging by how much space
	this takes up in memory.

*/
class CGMODRules : public CHL2MPRules
{
public:
	/*163 - 652*/virtual void CleanUpMap(GarrysMod::Lua::CLuaObject&);
};

#endif