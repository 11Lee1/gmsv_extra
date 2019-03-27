//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef BASEFLEX_H
#define BASEFLEX_H
#ifdef _WIN32
#pragma once
#endif


#include "BaseAnimatingOverlay.h"
#include "../tier1/utlvector.h"
#include "../tier1/utlrbtree.h"
#include "../sceneentity_shared.h"

struct flexsettinghdr_t;
struct flexsetting_t;
class AI_Response;

//-----------------------------------------------------------------------------
// Purpose:  A .vfe referenced by a scene during .vcd playback
//-----------------------------------------------------------------------------
class CFlexSceneFile
{
public:
	enum
	{
		MAX_FLEX_FILENAME = 128,
	};

	char			filename[MAX_FLEX_FILENAME];
	void			*buffer;
};

//-----------------------------------------------------------------------------
// Purpose: Animated characters who have vertex flex capability (e.g., facial expressions)
//-----------------------------------------------------------------------------
class CBaseFlex : public CBaseAnimatingOverlay
{
	DECLARE_CLASS(CBaseFlex, CBaseAnimatingOverlay);
public:
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	DECLARE_PREDICTABLE();


public:
	float			m_flexWeight[MAXSTUDIOFLEXCTRL];	// indexed by model local flexcontroller

	// Vector from actor to eye target
	Vector			m_viewtarget;

	// Blink state
	int				m_blinktoggle;

	// Array of active SceneEvents, in order oldest to newest
	CUtlVector < CSceneEventInfo >		m_SceneEvents;

	// Mapping for each loaded scene file used by this actor
	struct FS_LocalToGlobal_t
	{
		explicit FS_LocalToGlobal_t() :
			m_Key(0),
			m_nCount(0),
			m_Mapping(0)
		{
		}

		explicit FS_LocalToGlobal_t(const flexsettinghdr_t *key) :
			m_Key(key),
			m_nCount(0),
			m_Mapping(0)
		{
		}

		void SetCount(int count)
		{
			m_nCount = count;
			m_Mapping = new LocalFlexController_t[m_nCount];
			Q_memset(m_Mapping, 0, m_nCount * sizeof(int));
		}

		FS_LocalToGlobal_t(const FS_LocalToGlobal_t& src)
		{
			m_Key = src.m_Key;
			delete m_Mapping;
			m_Mapping = new LocalFlexController_t[src.m_nCount];
			Q_memcpy(m_Mapping, src.m_Mapping, src.m_nCount * sizeof(int));

			m_nCount = src.m_nCount;
		}

		~FS_LocalToGlobal_t()
		{
			delete m_Mapping;
			m_nCount = 0;
			m_Mapping = 0;
		}

		const flexsettinghdr_t	*m_Key;
		int						m_nCount;
		LocalFlexController_t	*m_Mapping;
	};

	CUtlRBTree< FS_LocalToGlobal_t, unsigned short > m_LocalToGlobal;

	// The NPC is in a scene, but another .vcd (such as a short wave to say in response to the player doing something )
	//  can be layered on top of this actor (assuming duration matches, etc.
	float			m_flAllowResponsesEndTime;

	// List of actively playing scenes
	CUtlVector < CChoreoScene * >		m_ActiveChoreoScenes;
	bool			m_bUpdateLayerPriorities;

	// last time a foreground flex animation was played
	float			m_flLastFlexAnimationTime;

	Vector			m_vecPrevOrigin;
	Vector			m_vecPrevVelocity;
	Vector			m_vecLean;
	Vector			m_vecShift;
};


#endif // BASEFLEX_H