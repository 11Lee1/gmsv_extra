//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H
#ifdef _WIN32
#pragma once
#endif

#include "edict.h"
#include "networkvar.h"

class CPlayerState
{
public:
	DECLARE_CLASS_NOBASE(CPlayerState);
	DECLARE_EMBEDDED_NETWORKVAR();

	// This virtual method is necessary to generate a vtable in all cases
	// (DECLARE_PREDICTABLE will generate a vtable also)!
	virtual ~CPlayerState() {}

	// true if the player is dead
	bool			deadflag;
	// Viewing angle (player only)
	QAngle			v_angle;


	// Player's network name
	string_t		netname;
	// 0:nothing, 1:force view angles, 2:add avelocity
	int				fixangle;
	// delta angle for fixangle == FIXANGLE_RELATIVE
	QAngle			anglechange;
	// flag to single the HLTV/Replay fake client, not transmitted
	bool			hltv;
	bool			replay;
	int				frags;
	int				deaths;
};

#endif // PLAYERSTATE_H