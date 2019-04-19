//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//

#ifndef TEAMPLAY_GAMERULES_H
#define TEAMPLAY_GAMERULES_H
#pragma once

#include "gamerules.h"
#include "multiplay_gamerules.h"

#ifdef CLIENT_DLL

#define CTeamplayRules C_TeamplayRules

#else

#include "takedamageinfo.h"

#endif


//
// teamplay_gamerules.h
//


#define MAX_TEAMNAME_LENGTH	16
#define MAX_TEAMS			32

#define TEAMPLAY_TEAMLISTLENGTH		MAX_TEAMS*MAX_TEAMNAME_LENGTH


class CTeamplayRules : public CMultiplayRules
{
public:
	DECLARE_CLASS(CTeamplayRules, CMultiplayRules);

	// Return the value of this player towards capturing a point
	/*147 - 588*/virtual int	 GetCaptureValueForPlayer(CBasePlayer *pPlayer) { return 1; }
	/*148 - 592*/virtual bool	TeamMayCapturePoint(int iTeam, int iPointIndex) { return true; }
	/*149 - 596*/virtual bool PlayerMayCapturePoint(CBasePlayer *pPlayer, int iPointIndex, char *pszReason = NULL, int iMaxReasonLength = 0) { return true; }
	/*150 - 600*/virtual bool PlayerMayBlockPoint(CBasePlayer *pPlayer, int iPointIndex, char *pszReason = NULL, int iMaxReasonLength = 0) { return false; }

	// Return false if players aren't allowed to cap points at this time (i.e. in WaitingForPlayers)
	/*151 - 604*/virtual bool PointsMayBeCaptured(void) { return true; }
	/*152 - 608*/virtual void SetLastCapPointChanged(int iIndex) { return; }

#ifdef CLIENT_DLL

#else

	CTeamplayRules();
	/*13 - 52*/virtual ~CTeamplayRules() {};

	/*42 - 168*/virtual void Precache(void);

	/*76 - 304*/virtual bool ClientCommand(CBaseEntity *pEdict, const CCommand &args);
	/*77 - 308*/virtual void ClientSettingsChanged(CBasePlayer *pPlayer);
	/*54 - 216*/virtual bool IsTeamplay(void);
	/*61 - 244*/virtual bool FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker, const CTakeDamageInfo &info);
	/*106 - 424*/virtual int PlayerRelationship(CBaseEntity *pPlayer, CBaseEntity *pTarget);
	/*107 - 428*/virtual bool PlayerCanHearChat(CBasePlayer *pListener, CBasePlayer *pSpeaker);
	/*105 - 420*/virtual const char *GetTeamID(CBaseEntity *pEntity);
	/*62 - 248*/virtual bool ShouldAutoAim(CBasePlayer *pPlayer, edict_t *target);
	/*78 - 312*/virtual int IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled);
	/*58 - 232*/virtual void InitHUD(CBasePlayer *pl);
	/*80 - 320*/virtual void DeathNotice(CBasePlayer *pVictim, const CTakeDamageInfo &info);
	/*56 - 224*/virtual const char *GetGameDescription(void) { return "Teamplay"; }  // this is the game name that gets seen in the server browser
	/*79 - 316*/virtual void PlayerKilled(CBasePlayer *pVictim, const CTakeDamageInfo &info);
	/*44 - 176*/virtual void Think(void);
	/*109 - 436*/virtual int GetTeamIndex(const char *pTeamName);
	/*110 - 440*/virtual const char *GetIndexedTeamName(int teamIndex);
	/*111 - 444*/virtual bool IsValidTeam(const char *pTeamName);
	/*113 - 452*/virtual const char *SetDefaultPlayerTeam(CBasePlayer *pPlayer);
	/*112 - 448*/virtual void ChangePlayerTeam(CBasePlayer *pPlayer, const char *pTeamName, bool bKill, bool bGib);
	/*59 - 236*/virtual void ClientDisconnected(edict_t *pClient);
	/*153 - 612*/virtual bool TimerMayExpire(void) { return true; }

	// A game has been won by the specified team
	/*154 - 616*/virtual void SetWinningTeam(int team, int iWinReason, bool bForceMapReset = true, bool bSwitchTeams = false, bool bDontAddScore = false, bool bFinal = false) { return; }
	/*155 - 620*/virtual void SetStalemate(int iReason, bool bForceMapReset = true, bool bSwitchTeams = false) { return; }

	// Used to determine if all players should switch teams
	/*156 - 624*/virtual void SetSwitchTeams(bool bSwitch) { m_bSwitchTeams = bSwitch; }
	/*157 - 628*/virtual bool ShouldSwitchTeams(void) { return m_bSwitchTeams; }
	/*158 - 632*/virtual void HandleSwitchTeams(void) { return; }

	// Used to determine if we should scramble the teams
	/*159 - 636*/virtual void SetScrambleTeams(bool bScramble) { m_bScrambleTeams = bScramble; }
	/*160 - 640*/virtual bool ShouldScrambleTeams(void) { return m_bScrambleTeams; }
	/*161 - 644*/virtual void HandleScrambleTeams(void) { return; }

	/*162 - 648*/virtual bool PointsMayAlwaysBeBlocked() { return false; }

protected:
	bool m_DisableDeathMessages;

private:
	void RecountTeams(void);
	const char *TeamWithFewestPlayers(void);

	bool m_DisableDeathPenalty;
	bool m_teamLimit;				// This means the server set only some teams as valid
	char m_szTeamList[TEAMPLAY_TEAMLISTLENGTH];
	bool m_bSwitchTeams;
	bool m_bScrambleTeams;

#endif
};

#endif // TEAMPLAY_GAMERULES_H