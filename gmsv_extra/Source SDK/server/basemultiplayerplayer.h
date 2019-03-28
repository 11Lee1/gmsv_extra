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

	/*526*/virtual bool			SpeakIfAllowed(AIConcept_t concept, const char *modifiers = NULL, char *pszOutResponseChosen = NULL, size_t bufsize = 0, IRecipientFilter *filter = NULL);
	/*527*/virtual bool			SpeakConceptIfAllowed(int iConcept, const char *modifiers = NULL, char *pszOutResponseChosen = NULL, size_t bufsize = 0, IRecipientFilter *filter = NULL);
	/*528*/virtual bool			CanBeAutobalanced() { return true; }
	/*529*/virtual bool			CanSpeakVoiceCommand(void) { return true; }
	/*530*/virtual bool			ShouldShowVoiceSubtitleToEnemy(void);
	/*531*/virtual void			NoteSpokeVoiceCommand(const char *pszScenePlayed) {}
	/*532*/virtual void			OnAchievementEarned(int iAchievement) {}
	/*533*/virtual CMultiplayer_Expresser *GetMultiplayerExpresser() { return m_pExpresser; }
	/*534*/virtual int				CalculateTeamBalanceScore(void);
	/*535*/virtual CAI_Expresser*	CreateExpresser(void);



public:

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