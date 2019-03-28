#ifndef SENTANIM_H
#define SENTANIM_H

#include "../BaseAnimatingOverlay.h"
#include "../../../GLUA/CScriptedEntity.h"

// Reasons behind a pickup
enum PhysGunPickup_t
{
	PICKED_UP_BY_CANNON,
	PUNTED_BY_CANNON,
	PICKED_UP_BY_PLAYER, // Picked up by +USE, not physgun.
};

// Reasons behind a drop
enum PhysGunDrop_t
{
	DROPPED_BY_PLAYER,
	THROWN_BY_PLAYER,
	DROPPED_BY_CANNON,
	LAUNCHED_BY_CANNON,
};

enum PhysGunForce_t
{
	PHYSGUN_FORCE_DROPPED,	// Dropped by +USE
	PHYSGUN_FORCE_THROWN,	// Thrown from +USE
	PHYSGUN_FORCE_PUNTED,	// Punted by cannon
	PHYSGUN_FORCE_LAUNCHED,	// Launched by cannon
};

class CSENT_anim : public CBaseAnimatingOverlay
{
public:
	virtual ~CSENT_anim();

	/*273*/virtual void		ScriptThink();
	/*274*/virtual void		Simulate(IPhysicsMotionController *, IPhysicsObject *, float, Vector &, Vector &);
	/*275*/virtual void		ScriptUse(CBaseEntity *, CBaseEntity *, USE_TYPE, float);
	/*276*/virtual void		OnPhysGunPickup(CBasePlayer *, PhysGunPickup_t);
	/*277*/virtual void		OnPhysGunDrop(CBasePlayer *, PhysGunDrop_t);

public:
	BYTE pad_VMT[0x8]; // two vmt's, I'll look into it later.

	CScriptedEntity		m_ScriptedEntity;

	// there's more but I can't figure out what literally any of it means lol.
};
#endif