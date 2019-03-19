//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: The worldspawn entity. This spawns first when each level begins.
//
// $NoKeywords: $
//=============================================================================//

#ifndef WORLD_H
#define WORLD_H
#ifdef _WIN32
#pragma once
#endif

#include "../serverclass.h"
#include "../mathlib/mathlib.h"
#include "../string_t.h"
#include "../networkvar.h"
#include "../server/baseentity.h"

class CBaseEntity;
class gamevcollisionevent_t;
class IPhysicsObject;
class CWorld : public CBaseEntity
{
public:

	CWorld();
	~CWorld();

	DECLARE_SERVERCLASS();

	virtual int RequiredEdictIndex(void) { return 0; }   // the world always needs to be in slot 0

	static void RegisterSharedActivities(void);
	static void RegisterSharedEvents(void);
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual bool KeyValue(const char *szKeyName, const char *szValue);
	virtual void DecalTrace(trace_t *pTrace, char const *decalName);
	virtual void VPhysicsCollision(int index, gamevcollisionevent_t *pEvent) {}
	virtual void VPhysicsFriction(IPhysicsObject *pObject, float energy, int surfaceProps, int surfacePropsHit) {}

	inline void GetWorldBounds(Vector &vecMins, Vector &vecMaxs)
	{
		VectorCopy(m_WorldMins, vecMins);
		VectorCopy(m_WorldMaxs, vecMaxs);
	}

	inline float GetWaveHeight() const
	{
		return (float)m_flWaveHeight;
	}

	bool GetDisplayTitle() const;
	bool GetStartDark() const;

	void SetDisplayTitle(bool display);
	void SetStartDark(bool startdark);

	bool IsColdWorld(void);

private:
	string_t m_iszChapterTitle;

	float m_flWaveHeight;
	Vector m_WorldMins; 
	Vector m_WorldMaxs;
	float m_flMaxOccludeeArea;
	float m_flMinOccluderArea;
	float m_flMinPropScreenSpaceWidth;
	float m_flMaxPropScreenSpaceWidth;
	string_t m_iszDetailSpriteMaterial;
	bool m_bStartDark;
	bool m_bColdWorld;
	bool m_bDisplayTitle;
};


CWorld* GetWorldEntity();
extern const char *GetDefaultLightstyleString(int styleIndex);


#endif // WORLD_H