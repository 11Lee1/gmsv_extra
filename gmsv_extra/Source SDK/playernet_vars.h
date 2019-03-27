//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef PLAYERNET_VARS_H
#define PLAYERNET_VARS_H
#ifdef _WIN32
#pragma once
#endif

#define NUM_AUDIO_LOCAL_SOUNDS	8

// These structs are contained in each player's local data and shared by the client & server

struct fogparams_t
{
	DECLARE_CLASS_NOBASE(fogparams_t);
	DECLARE_EMBEDDED_NETWORKVAR();

#ifndef CLIENT_DLL
	DECLARE_SIMPLE_DATADESC();
#endif

	bool operator !=(const fogparams_t& other) const;

	Vector			dirPrimary;
	color32			colorPrimary;
	color32			colorSecondary;
	color32			colorPrimaryLerpTo;
	color32			colorSecondaryLerpTo;
	float			start;
	float			end;
	float			farz;
	float			maxdensity;

	float			startLerpTo;
	float			endLerpTo;
	float			lerptime;
	float			duration;
	bool			enable;
	bool			blend;
};

// Crappy. Needs to be here because it wants to use 
#ifdef CLIENT_DLL
#define CFogController C_FogController
#endif

class CFogController;

struct fogplayerparams_t
{
	DECLARE_CLASS_NOBASE(fogplayerparams_t);
	DECLARE_EMBEDDED_NETWORKVAR();

#ifndef CLIENT_DLL
	DECLARE_SIMPLE_DATADESC();
#endif

	EHANDLE					m_hCtrl;
	float					m_flTransitionTime;

	color32					m_OldColor;
	float					m_flOldStart;
	float					m_flOldEnd;

	color32					m_NewColor;
	float					m_flNewStart;
	float					m_flNewEnd;

	fogplayerparams_t()
	{
		m_hCtrl.Set(NULL);
		m_flTransitionTime = -1.0f;
		m_OldColor.r = m_OldColor.g = m_OldColor.b = m_OldColor.a = 0;
		m_flOldStart = 0.0f;
		m_flOldEnd = 0.0f;
		m_NewColor.r = m_NewColor.g = m_NewColor.b = m_NewColor.a = 0;
		m_flNewStart = 0.0f;
		m_flNewEnd = 0.0f;
	}
};

struct sky3dparams_t
{
	DECLARE_CLASS_NOBASE(sky3dparams_t);
	DECLARE_EMBEDDED_NETWORKVAR();

#ifndef CLIENT_DLL
	DECLARE_SIMPLE_DATADESC();
#endif

	// 3d skybox camera data
	int			scale;
	Vector		origin;
	int			area;

	// 3d skybox fog data
	fogparams_t fog;
};

struct audioparams_t
{
	DECLARE_CLASS_NOBASE(audioparams_t);
	DECLARE_EMBEDDED_NETWORKVAR();

#ifndef CLIENT_DLL
	DECLARE_SIMPLE_DATADESC();
#endif

	Vector				localSound[NUM_AUDIO_LOCAL_SOUNDS];
	int					soundscapeIndex;	// index of the current soundscape from soundscape.txt
	int					localBits;			// if bits 0,1,2,3 are set then position 0,1,2,3 are valid/used
	EHANDLE				ent;		// the entity setting the soundscape
};


#endif // PLAYERNET_VARS_H