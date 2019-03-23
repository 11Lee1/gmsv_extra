#ifndef BASEANIMATING_H
#define BASEANIMATING_H

#include "baseentity.h"
#include "../entityoutput.h"
#include "../studio.h"

struct animevent_t;
struct matrix3x4_t;
class CIKContext;
class KeyValues;
FORWARD_DECLARE_HANDLE(memhandle_t);

#define	BCF_NO_ANIMATION_SKIP	( 1 << 0 )	// Do not allow PVS animation skipping (mostly for attachments being critical to an entity)
#define	BCF_IS_IN_SPAWN			( 1 << 1 )	// Is currently inside of spawn, always evaluate animations

class CBaseAnimating : public CBaseEntity
{
public:
	DECLARE_CLASS(CBaseAnimating, CBaseEntity);

	CBaseAnimating();
	~CBaseAnimating();

	DECLARE_PREDICTABLE();

	enum
	{
		NUM_POSEPAREMETERS = 24,
		NUM_BONECTRLS = 4
	};

	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

public:
	// animation needs
	float				m_flGroundSpeed;	// computed linear movement rate for current sequence
	float				m_flLastEventCheck; // cycle index of when events were last checked

	int					m_nForceBone;
	Vector				m_vecForce;
	
	int					m_nSkin;
	int					m_nBody;
	int					m_nHitboxSet;

	// For making things thin during barnacle swallowing, e.g.
	float				m_flModelScale;
	// was pev->framerate
	float				m_flPlaybackRate;


	float				m_flIKGroundContactTime;
	float				m_flIKGroundMinHeight;
	float				m_flIKGroundMaxHeight;

	float				m_flEstIkFloor; // debounced
	float				m_flEstIkOffset;

	CIKContext			*m_pIk;
	int					m_iIKCounter;

	bool				m_bSequenceFinished;// flag set when StudioAdvanceFrame moves across a frame boundry
	bool				m_bSequenceLoops;	// true if the sequence loops
	bool				m_bResetSequenceInfoOnLoad; // true if a ResetSequenceInfo was queued up during dynamic load
	float				m_flDissolveStartTime;

	// was pev->frame
	float				m_flCycle;
	int					m_nSequence;
	float				m_flPoseParameter[NUM_POSEPAREMETERS];
	float				m_flEncodedController[NUM_BONECTRLS];

	// Client-side animation (useful for looping animation objects)
	bool				m_bClientSideAnimation;
	bool				m_bClientSideFrameReset;

	int					m_nNewSequenceParity;
	int					m_nResetEventsParity;
	// Incremented each time the entity is told to do a muzzle flash.
	// The client picks up the change and draws the flash.
	unsigned char		m_nMuzzleFlashParity;


	EHANDLE				m_hLightingOrigin;
	EHANDLE				m_hLightingOriginRelative;

	string_t			m_iszLightingOriginRelative;	// for reading from the file only
	string_t			m_iszLightingOrigin; // for reading from the file only

	memhandle_t			m_boneCacheHandle;
	unsigned short		m_fBoneCacheFlags; // Used for bone cache state on model

	float				m_fadeMinDist;	// Point at which fading is absolute
	float				m_fadeMaxDist;	// Point at which fading is inactive
	float				m_flFadeScale;	// Scale applied to min / max

	BYTE		pad_unk03[0xB0];

	CStudioHdr*			m_pStudioHdr; // 0x153C

	CThreadFastMutex	m_StudioHdrInitLock;
	CThreadFastMutex	m_BoneSetupMutex;
};


#endif