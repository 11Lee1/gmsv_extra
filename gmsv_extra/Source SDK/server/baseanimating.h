#ifndef BASEANIMATING_H
#define BASEANIMATING_H

#include "baseentity.h"
#include "../entityoutput.h"
#include "../studio.h"
#include "../ai_activity.h"

struct animevent_t;
struct matrix3x4_t;
class CIKContext;
class KeyValues;
FORWARD_DECLARE_HANDLE(memhandle_t);

#define	BCF_NO_ANIMATION_SKIP	( 1 << 0 )	// Do not allow PVS animation skipping (mostly for attachments being critical to an entity)
#define	BCF_IS_IN_SPAWN			( 1 << 1 )	// Is currently inside of spawn, always evaluate animations

class CBaseAnimating : public CBaseEntity // Do baseanimating.cpp
{
public:
	DECLARE_CLASS(CBaseAnimating, CBaseEntity);

	CBaseAnimating();
	~CBaseAnimating();

	enum
	{
		NUM_POSEPAREMETERS = 24,
		NUM_BONECTRLS = 4
	};

	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();
public:
	// Basic NPC Animation functions
	/*238*/virtual float		GetIdealSpeed() const;
	/*239*/virtual float		GetIdealAccel() const;
	/*240*/virtual void		StudioFrameAdvance(); // advance animation frame to some time in the future

	/*241*/virtual void		SetSequence(int nSequence);
	/*242*/virtual bool		IsActivityFinished(void) { return m_bSequenceFinished; }
	/*243*/virtual float		GetSequenceGroundSpeed(CStudioHdr *pStudioHdr, int iSequence);

	/*244*/virtual void		ClampRagdollForce(const Vector &vecForceIn, Vector *vecForceOut) { *vecForceOut = vecForceIn; } // Base class does nothing.
	/*245*/virtual bool		BecomeRagdollOnClient(const Vector &force);
	/*246*/virtual bool		IsRagdoll();
	/*247*/virtual bool		CanBecomeRagdoll(void); //Check if this entity will ragdoll when dead.

	/*248*/virtual	void		GetSkeleton(CStudioHdr *pStudioHdr, Vector pos[], Quaternion q[], int boneMask);

	/*249*/virtual void		GetBoneTransform(int iBone, matrix3x4_t &pBoneToWorld);
	/*250*/virtual void		SetupBones(matrix3x4_t *pBoneToWorld, int boneMask);
	/*251*/virtual void		CalculateIKLocks(float currentTime);

	/*252*/virtual	void		DispatchAnimEvents(CBaseAnimating *eventHandler); // Handle events that have happend since last time called up until X seconds into the future
	/*253*/virtual void		HandleAnimEvent(animevent_t *pEvent);

	/*254*/virtual void		PopulatePoseParameters(void);

	/*255*/virtual bool		GetAttachment(int iAttachment, matrix3x4_t &attachmentToWorld);

	/*256*/virtual	void		InitBoneControllers(void);

	/*257*/virtual	Vector		GetGroundSpeedVelocity(void);

	/*258*/virtual void		RefreshCollisionBounds(void);
	/*259*/virtual bool		TestCollision(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr);
	/*260*/virtual bool		TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr);

	// Fire
	/*261*/virtual void		Ignite(float flFlameLifetime, bool bNPCOnly = true, float flSize = 0.0f, bool bCalledByLevelDesigner = false);
	/*262*/virtual void		IgniteLifetime(float flFlameLifetime);
	/*263*/virtual void		IgniteNumHitboxFires(int iNumHitBoxFires);
	/*264*/virtual void		IgniteHitboxFireScale(float flHitboxFireScale);
	/*265*/virtual void		Extinguish();

	/*266*/virtual void		SetLightingOriginRelative(CBaseEntity *pLightingOriginRelative);
	/*267*/virtual void		SetLightingOrigin(CBaseEntity *pLightingOrigin);

	/*268*/virtual int			GetPhysBoneNumber(int);
	/*269*/virtual void		SetBoneManipulator(CBaseEntity*);
	/*270*/virtual CBaseEntity*GetBoneManipulator(bool);
	/*271*/virtual void		SetFlexManipulator(CBaseEntity*);
	/*272*/virtual CBaseEntity*GetFlexManipulator(bool);
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

	BYTE	pad_unk03[0xB0];

	CStudioHdr*			m_pStudioHdr; // 0x153C

	CThreadFastMutex	m_StudioHdrInitLock;
	CThreadFastMutex	m_BoneSetupMutex;
	BYTE	pad_unk04[0x4];
};


#endif