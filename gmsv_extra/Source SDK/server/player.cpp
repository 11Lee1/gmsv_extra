#include "player.h"



//-----------------------------------------------------------------------------
// Purpose: Returns the nearest COLLIBALE entity in front of the player
//			that has a clear line of sight. If HULL is true, the trace will
//			hit the collision hull of entities. Otherwise, the trace will hit
//			hitboxes.
// Input  :
// Output :
//-----------------------------------------------------------------------------
CBaseEntity *FindEntityForward(CBasePlayer *pMe, bool fHull)
{
	if (pMe)
	{
		trace_t tr;
		Vector forward;
		int mask;

		if (fHull)
		{
			mask = MASK_SOLID;
		}
		else
		{
			mask = MASK_SHOT;
		}

		pMe->EyeVectors(&forward);
		UTIL_TraceLine(pMe->EyePosition(),
			pMe->EyePosition() + forward * MAX_COORD_RANGE,
			mask, pMe, COLLISION_GROUP_NONE, &tr);
		if (tr.fraction != 1.0 && tr.DidHitNonWorldEntity())
		{
			return tr.m_pEnt;
		}
	}
	return NULL;

}