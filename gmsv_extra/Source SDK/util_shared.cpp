//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

/*

	Finish me.

	-Lee

*/
#include "../interfaces.h" 
#include "vstdlib/random.h"


#include "server/cbase.h"
#include "mathlib/mathlib.h"
#include "util_shared.h"
#include "model_types.h"
#include "tier1/convar.h"
#include "IEffects.h"
#include "vphysics/object_hash.h"
#include "mathlib/IceKey.H"
#include "tier1/checksum_crc.h"
#ifdef TF_CLIENT_DLL
#include "cdll_util.h"
#endif
#include "particle_parse.h"
#include "tier1/KeyValues.h"
#include "time.h"

#ifdef USES_ECON_ITEMS
#include "econ_item_constants.h"
#include "econ_holidays.h"
#include "rtime.h"
#endif // USES_ECON_ITEMS

#ifdef CLIENT_DLL
#include "c_te_effect_dispatch.h"
#else
bool NPC_CheckBrushExclude(CBaseEntity *pEntity, CBaseEntity *pBrush);
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#include "eiface.h"
#include "server/player.h"

float UTIL_VecToYaw(const Vector &vec)
{
	if (vec.y == 0 && vec.x == 0)
		return 0;

	float yaw = atan2(vec.y, vec.x);

	yaw = RAD2DEG(yaw);

	if (yaw < 0)
		yaw += 360;

	return yaw;
}


float UTIL_VecToPitch(const Vector &vec)
{
	if (vec.y == 0 && vec.x == 0)
	{
		if (vec.z < 0)
			return 180.0;
		else
			return -180.0;
	}

	float dist = vec.Length2D();
	float pitch = atan2(-vec.z, dist);

	pitch = RAD2DEG(pitch);

	return pitch;
}

float UTIL_VecToYaw(const matrix3x4_t &matrix, const Vector &vec)
{
	Vector tmp = vec;
	VectorNormalize(tmp);

	float x = matrix[0][0] * tmp.x + matrix[1][0] * tmp.y + matrix[2][0] * tmp.z;
	float y = matrix[0][1] * tmp.x + matrix[1][1] * tmp.y + matrix[2][1] * tmp.z;

	if (x == 0.0f && y == 0.0f)
		return 0.0f;

	float yaw = atan2(-y, x);

	yaw = RAD2DEG(yaw);

	if (yaw < 0)
		yaw += 360;

	return yaw;
}


float UTIL_VecToPitch(const matrix3x4_t &matrix, const Vector &vec)
{
	Vector tmp = vec;
	VectorNormalize(tmp);

	float x = matrix[0][0] * tmp.x + matrix[1][0] * tmp.y + matrix[2][0] * tmp.z;
	float z = matrix[0][2] * tmp.x + matrix[1][2] * tmp.y + matrix[2][2] * tmp.z;

	if (x == 0.0f && z == 0.0f)
		return 0.0f;

	float pitch = atan2(z, x);

	pitch = RAD2DEG(pitch);

	if (pitch < 0)
		pitch += 360;

	return pitch;
}

Vector UTIL_YawToVector(float yaw)
{
	Vector ret;

	ret.z = 0;
	float angle = DEG2RAD(yaw);
	SinCos(angle, &ret.y, &ret.x);

	return ret;
}

CBasePlayer *UTIL_PlayerByIndex(int entindex)
{
	return (CBasePlayer*)g_pInterfaces->EngineServer()->PEntityOfEntIndex(entindex)->GetUnknown();
}
CBasePlayer* UTIL_PlayerByUserId(int userID)
{
	for (int i = 1; i <= g_pInterfaces->Globals()->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!pPlayer)
			continue;

		if (pPlayer->GetUserID() == userID)
		{
			return pPlayer;
		}
	}

	return nullptr;
}