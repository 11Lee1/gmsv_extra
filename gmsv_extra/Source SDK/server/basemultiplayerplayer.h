//========= Copyright Valve Corporation, All rights reserved. ============//
//
//=============================================================================
#ifndef BASEMULTIPLAYERPLAYER_H
#define BASEMULTIPLAYERPLAYER_H
#pragma once

#include "player.h"
#include "ai_speech.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CBaseMultiplayerPlayer : public CAI_ExpresserHost<CBasePlayer>
{

	DECLARE_CLASS(CBaseMultiplayerPlayer, CAI_ExpresserHost<CBasePlayer>);

public:
	enum
	{
		CHAT_IGNORE_NONE = 0,
		CHAT_IGNORE_ALL,
		CHAT_IGNORE_TEAM,
	};

	int							m_iIgnoreGlobalChat;
	float						m_flAreaCaptureScoreAccumulator;
	float						m_flCapPointScoreRate;
	int							m_iCurrentConcept;
	CMultiplayer_Expresser*		m_pExpresser;

	float						m_flConnectionTime;
	float						m_flLastForcedChangeTeamTime;

	int							m_iBalanceScore;	// a score used to determine which players are switched to balance the teams

	KeyValues*					m_pAchievementKV;

	// This lets us rate limit the commands the players can execute so they don't overflow things like reliable buffers.
	CUtlDict<float, int>		m_RateLimitLastCommandTimes;
};

//-----------------------------------------------------------------------------
// Inline methods
//-----------------------------------------------------------------------------
inline CBaseMultiplayerPlayer *ToBaseMultiplayerPlayer(CBaseEntity *pEntity)
{
	if (!pEntity || !pEntity->IsPlayer())
		return NULL;
#if _DEBUG
	return dynamic_cast<CBaseMultiplayerPlayer *>(pEntity);
#else
	return static_cast<CBaseMultiplayerPlayer *>(pEntity);
#endif
}

#endif	// BASEMULTIPLAYERPLAYER_H