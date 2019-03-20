//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "../gametrace.h"
#include "world.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "../tier0/memdbgon.h"

bool CGameTrace::DidHitWorld() const
{
	return 0;
	//return m_pEnt->m_Network.entindex();
}


bool CGameTrace::DidHitNonWorldEntity() const
{
	return 0;
	//return m_pEnt != NULL && !DidHitWorld();
}


int CGameTrace::GetEntityIndex() const
{
	return 0;
//	if (m_pEnt)
//		return m_pEnt->m_Network.entindex();
//	else
//		return -1;
}