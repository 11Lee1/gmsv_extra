//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Base combat character with no AI
//
// $NoKeywords: $
//=============================================================================//

#ifndef BASECOMBATCHARACTER_H
#define BASECOMBATCHARACTER_H

#include <limits.h>
#include "../weapon_proficiency.h"

#ifdef _WIN32
#pragma once
#endif

#ifdef INVASION_DLL
#include "tf_shareddefs.h"

#define POWERUP_THINK_CONTEXT	"PowerupThink"
#endif

#include "cbase.h"
#include "baseentity.h"
#include "baseflex.h"
#include "damagemodifier.h"
#include "../tier1/utllinkedlist.h"
#include "ai_hull.h"
#include "ai_utils.h"
#include "physics_impact_damage.h"

class CNavArea;
class CScriptedTarget;
typedef CHandle<CBaseCombatWeapon> CBaseCombatWeaponHandle;

// -------------------------------------
//  Capability Bits
// -------------------------------------

enum Capability_t
{
	bits_CAP_MOVE_GROUND = 0x00000001, // walk/run
	bits_CAP_MOVE_JUMP = 0x00000002, // jump/leap
	bits_CAP_MOVE_FLY = 0x00000004, // can fly, move all around
	bits_CAP_MOVE_CLIMB = 0x00000008, // climb ladders
	bits_CAP_MOVE_SWIM = 0x00000010, // navigate in water			// UNDONE - not yet implemented
	bits_CAP_MOVE_CRAWL = 0x00000020, // crawl						// UNDONE - not yet implemented
	bits_CAP_MOVE_SHOOT = 0x00000040, // tries to shoot weapon while moving
	bits_CAP_SKIP_NAV_GROUND_CHECK = 0x00000080, // optimization - skips ground tests while computing navigation
	bits_CAP_USE = 0x00000100, // open doors/push buttons/pull levers
	//bits_CAP_HEAR					= 0x00000200, // can hear forced sounds
	bits_CAP_AUTO_DOORS = 0x00000400, // can trigger auto doors
	bits_CAP_OPEN_DOORS = 0x00000800, // can open manual doors
	bits_CAP_TURN_HEAD = 0x00001000, // can turn head, always bone controller 0
	bits_CAP_WEAPON_RANGE_ATTACK1 = 0x00002000, // can do a weapon range attack 1
	bits_CAP_WEAPON_RANGE_ATTACK2 = 0x00004000, // can do a weapon range attack 2
	bits_CAP_WEAPON_MELEE_ATTACK1 = 0x00008000, // can do a weapon melee attack 1
	bits_CAP_WEAPON_MELEE_ATTACK2 = 0x00010000, // can do a weapon melee attack 2
	bits_CAP_INNATE_RANGE_ATTACK1 = 0x00020000, // can do a innate range attack 1
	bits_CAP_INNATE_RANGE_ATTACK2 = 0x00040000, // can do a innate range attack 1
	bits_CAP_INNATE_MELEE_ATTACK1 = 0x00080000, // can do a innate melee attack 1
	bits_CAP_INNATE_MELEE_ATTACK2 = 0x00100000, // can do a innate melee attack 1
	bits_CAP_USE_WEAPONS = 0x00200000, // can use weapons (non-innate attacks)
	//bits_CAP_STRAFE					= 0x00400000, // strafe ( walk/run sideways)
	bits_CAP_ANIMATEDFACE = 0x00800000, // has animated eyes/face
	bits_CAP_USE_SHOT_REGULATOR = 0x01000000, // Uses the shot regulator for range attack1
	bits_CAP_FRIENDLY_DMG_IMMUNE = 0x02000000, // don't take damage from npc's that are D_LI
	bits_CAP_SQUAD = 0x04000000, // can form squads
	bits_CAP_DUCK = 0x08000000, // cover and reload ducking
	bits_CAP_NO_HIT_PLAYER = 0x10000000, // don't hit players
	bits_CAP_AIM_GUN = 0x20000000, // Use arms to aim gun, not just body
	bits_CAP_NO_HIT_SQUADMATES = 0x40000000, // none
	bits_CAP_SIMPLE_RADIUS_DAMAGE = 0x80000000, // Do not use robust radius damage model on this character.
};

#define bits_CAP_DOORS_GROUP    (bits_CAP_AUTO_DOORS | bits_CAP_OPEN_DOORS)
#define bits_CAP_RANGE_ATTACK_GROUP	(bits_CAP_WEAPON_RANGE_ATTACK1 | bits_CAP_WEAPON_RANGE_ATTACK2)
#define bits_CAP_MELEE_ATTACK_GROUP	(bits_CAP_WEAPON_MELEE_ATTACK1 | bits_CAP_WEAPON_MELEE_ATTACK2)


class CBaseCombatWeapon;

#define BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE 0.9f

enum Disposition_t
{
	D_ER,		// Undefined - error
	D_HT,		// Hate
	D_FR,		// Fear
	D_LI,		// Like
	D_NU		// Neutral
};

const int DEF_RELATIONSHIP_PRIORITY = INT_MIN;

struct Relationship_t
{
	EHANDLE			entity;			// Relationship to a particular entity
	Class_T			classType;		// Relationship to a class  CLASS_NONE = not class based (Def. in baseentity.h)
	Disposition_t	disposition;	// D_HT (Hate), D_FR (Fear), D_LI (Like), D_NT (Neutral)
	int				priority;		// Relative importance of this relationship (higher numbers mean more important)

	DECLARE_SIMPLE_DATADESC();
};

//-----------------------------------------------------------------------------
// Purpose: This should contain all of the combat entry points / functionality 
// that are common between NPCs and players
//-----------------------------------------------------------------------------
class CBaseCombatCharacter : public CBaseFlex
{
	DECLARE_CLASS(CBaseCombatCharacter, CBaseFlex);

public:
	CBaseCombatCharacter(void);
	~CBaseCombatCharacter(void);

	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	DECLARE_PREDICTABLE();

	enum FieldOfViewCheckType { USE_FOV, DISREGARD_FOV };
	enum LineOfSightCheckType
	{
		IGNORE_NOTHING,
		IGNORE_ACTORS
	};

	bool	m_bForceServerRagdoll;
	bool	m_bPreventWeaponPickup;

	float		m_flNextAttack;			// cannot attack again until this time

	Hull_t		m_eHull;

	int			m_bloodColor;			// color of blood particless

	// -------------------
	// combat ability data
	// -------------------
	float		m_flFieldOfView;		// cosine of field of view for this character
	Vector		m_HackedGunPos;			// HACK until we can query end of gun
	string_t	m_RelationshipString;	// Used to load up relationship keyvalues
	float		m_impactEnergyScale;// scale the amount of energy used to calculate damage this ent takes due to physics

	int					m_LastHitGroup;			// the last body region that took damage
	float				m_flDamageAccumulator;	// so very small amounts of damage do not get lost.
	int					m_iDamageCount;			// # of times NPC has been damaged.  used for tracking 1-shot kills.

	// Weapon proficiency gets calculated each time an NPC changes his weapon, and then
	// cached off as the CurrentWeaponProficiency.
	WeaponProficiency_t m_CurrentWeaponProficiency;

	// ---------------
	//  Relationships
	// ---------------
	CUtlVector<Relationship_t>		m_Relationship;						// Array of relationships

	// shared ammo slots
	int m_iAmmo[MAX_AMMO_SLOTS];

	// Usable character items 
	CBaseCombatWeaponHandle		m_hMyWeapons[MAX_WEAPONS];

	CBaseCombatWeaponHandle		m_hActiveWeapon;

};

#endif // BASECOMBATCHARACTER_H