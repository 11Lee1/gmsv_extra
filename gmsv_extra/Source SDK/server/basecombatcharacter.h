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
#include "../util_shared.h"

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

public:
	virtual const impactdamagetable_t&	GetPhysicsImpactDamageTable(void);
	virtual bool				FInViewCone(CBaseEntity *pEntity);
	virtual bool				FInViewCone(const Vector &vecSpot);
	virtual bool				FInAimCone(CBaseEntity *pEntity);
	virtual bool				FInAimCone(const Vector &vecSpot);
	virtual bool				ShouldShootMissTarget(CBaseCombatCharacter *pAttacker);
	virtual CBaseEntity*		FindMissTarget(void);
	// Do not call HandleInteraction directly, use DispatchInteraction
	virtual bool				HandleInteraction(int interactionType, void *data, CBaseCombatCharacter* sourceEnt);

	virtual QAngle				BodyAngles();
	virtual Vector				BodyDirection2D(void);
	virtual Vector				BodyDirection3D(void);
	virtual Vector				HeadDirection2D(void) { return BodyDirection2D(); }; // No head motion so just return body dir
	virtual Vector				HeadDirection3D(void) { return BodyDirection2D(); }; // No head motion so just return body dir
	virtual Vector				EyeDirection2D(void) { return HeadDirection2D(); }; // No eye motion so just return head dir
	virtual Vector				EyeDirection3D(void) { return HeadDirection3D(); }; // No eye motion so just return head dir

	// -----------------------
	// Fog
	// -----------------------
	virtual bool				IsHiddenByFog(const Vector &target) const;	///< return true if given target cant be seen because of fog
	virtual bool				IsHiddenByFog(CBaseEntity *target) const;		///< return true if given target cant be seen because of fog
	virtual bool				IsHiddenByFog(float range) const;				///< return true if given distance is too far to see through the fog
	virtual float				GetFogObscuredRatio(const Vector &target) const;///< return 0-1 ratio where zero is not obscured, and 1 is completely obscured
	virtual float				GetFogObscuredRatio(CBaseEntity *target) const;	///< return 0-1 ratio where zero is not obscured, and 1 is completely obscured
	virtual float				GetFogObscuredRatio(float range) const;		///< return 0-1 ratio where zero is not obscured, and 1 is completely obscured

	// -----------------------
	// Vision
	// -----------------------
	enum FieldOfViewCheckType { USE_FOV, DISREGARD_FOV };

	virtual bool				IsLookingTowards(const CBaseEntity *target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const;	// return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.
	virtual bool				IsLookingTowards(const Vector &target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const;	// return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.

	virtual bool				IsInFieldOfView(CBaseEntity *entity) const;	// Calls IsLookingTowards with the current field of view.  
	virtual bool				IsInFieldOfView(const Vector &pos) const;

	enum LineOfSightCheckType
	{
		IGNORE_NOTHING,
		IGNORE_ACTORS
	};
	virtual bool				IsLineOfSightClear(CBaseEntity *entity, LineOfSightCheckType checkType = IGNORE_NOTHING) const;// strictly LOS check with no other considerations
	virtual bool				IsLineOfSightClear(const Vector &pos, LineOfSightCheckType checkType = IGNORE_NOTHING, CBaseEntity *entityToIgnore = NULL) const;

	// -----------------------
	// Ammo
	// -----------------------
	virtual int					GiveAmmo(int iCount, int iAmmoIndex, bool bSuppressSound = false);
	virtual void				RemoveAmmo(int iCount, int iAmmoIndex);
	virtual void				RemoveAmmo(int iCount, const char *szName);
	virtual int					GetAmmoCount(int iAmmoIndex) const;
	virtual Activity			NPC_TranslateActivity(Activity baseAct);



	// -----------------------
	// Weapons
	// -----------------------
	virtual Activity			Weapon_TranslateActivity(Activity baseAct, bool *pRequired = NULL);
	virtual void				Weapon_FrameUpdate(void);
	virtual void				Weapon_HandleAnimEvent(animevent_t *pEvent);
	virtual bool				Weapon_CanUse(CBaseCombatWeapon *pWeapon);		// True is allowed to use this class of weapon
	virtual void				Weapon_Equip(CBaseCombatWeapon *pWeapon);			// Adds weapon to player
	virtual bool				Weapon_EquipAmmoOnly(CBaseCombatWeapon *pWeapon);	// Adds weapon ammo to player, leaves weapon
	virtual void				Weapon_Drop(CBaseCombatWeapon *pWeapon, const Vector *pvecTarget = NULL, const Vector *pVelocity = NULL);
	virtual	bool				Weapon_Switch(CBaseCombatWeapon *pWeapon, int viewmodelindex = 0);		// Switch to given weapon if has ammo (false if failed)
	virtual	Vector				Weapon_ShootPosition();		// gun position at current position/orientation
	virtual	bool				Weapon_CanSwitchTo(CBaseCombatWeapon *pWeapon);
	virtual bool				Weapon_SlotOccupied(CBaseCombatWeapon *pWeapon);
	virtual CBaseCombatWeapon*	Weapon_GetSlot(int slot) const;

	// For weapon strip
	virtual bool				AddPlayerItem(CBaseCombatWeapon *pItem) { return false; }
	virtual bool				RemovePlayerItem(CBaseCombatWeapon *pItem) { return false; }

	virtual bool				CanBecomeServerRagdoll(void) { return true; }

	// -----------------------
	// Damage
	// -----------------------
	// Override these to control how your character takes damage in different states
	virtual int					OnTakeDamage_Alive(const CTakeDamageInfo &info);
	virtual int					OnTakeDamage_Dying(const CTakeDamageInfo &info);
	virtual int					OnTakeDamage_Dead(const CTakeDamageInfo &info);

	virtual float				GetAliveDuration(void) const;			// return time we have been alive (only valid when alive)

	virtual void 				OnFriendDamaged(CBaseCombatCharacter *pSquadmate, CBaseEntity *pAttacker) {}
	virtual void 				NotifyFriendsOfDamage(CBaseEntity *pAttackerEntity) {}
	virtual bool				HasEverBeenInjured(int team = TEAM_ANY) const;			// return true if we have ever been injured by a member of the given team
	virtual float				GetTimeSinceLastInjury(int team = TEAM_ANY) const;		// return time since we were hurt by a member of the given team

	virtual void				OnPlayerKilledOther(CBaseEntity *pVictim, const CTakeDamageInfo &info) {}

	virtual Activity			GetDeathActivity(void);

	virtual bool				CorpseGib(const CTakeDamageInfo &info);
	virtual void				CorpseFade(void);	// Called instead of GibNPC() when gibs are disabled
	virtual bool				HasHumanGibs(void);
	virtual bool				HasAlienGibs(void);
	virtual bool				ShouldGib(const CTakeDamageInfo &info) { return false; }	// Always ragdoll, unless specified by the leaf class


	virtual void				OnKilledNPC(CBaseCombatCharacter *pKilled) {};

	// Exactly one of these happens immediately after killed (gibbed may happen later when the corpse gibs)
	// Character gibbed or faded out (violence controls) (only fired once)
	// returns true if gibs were spawned
	virtual bool				Event_Gibbed(const CTakeDamageInfo &info);
	// Character entered the dying state without being gibbed (only fired once)
	virtual void				Event_Dying(const CTakeDamageInfo &info);
	virtual void				Event_Dying();
	// character died and should become a ragdoll now
	// return true if converted to a ragdoll, false to use AI death
	virtual bool				BecomeRagdoll(const CTakeDamageInfo &info, const Vector &forceVector);
	virtual void				FixupBurningServerRagdoll(CBaseEntity *pRagdoll);

	virtual bool				BecomeRagdollBoogie(CBaseEntity *pKiller, const Vector &forceVector, float duration, int flags);


	virtual CBaseEntity*		CheckTraceHullAttack(float flDist, const Vector &mins, const Vector &maxs, int iDamage, int iDmgType, float forceScale = 1.0f, bool bDamageAnyNPC = false);
	virtual CBaseEntity*		CheckTraceHullAttack(const Vector &vStart, const Vector &vEnd, const Vector &mins, const Vector &maxs, int iDamage, int iDmgType, float flForceScale = 1.0f, bool bDamageAnyNPC = false);

	virtual void				PushawayTouch(CBaseEntity *pOther) {}
	virtual Disposition_t		IRelationType(CBaseEntity *pTarget);
	virtual int					IRelationPriority(CBaseEntity *pTarget);
	// Vehicle queries
	virtual bool				IsInAVehicle(void) const { return false; }
	virtual IServerVehicle*		GetVehicle(void) { return NULL; }
	virtual CBaseEntity*		GetVehicleEntity(void) { return NULL; }
	virtual bool				ExitVehicle(void) { return false; }

	// Weapons..
	virtual void				RemoveAllWeapons();
	virtual WeaponProficiency_t CalcWeaponProficiency(CBaseCombatWeapon *pWeapon);
	virtual	Vector				GetAttackSpread(CBaseCombatWeapon *pWeapon, CBaseEntity *pTarget = NULL);
	virtual	float				GetSpreadBias(CBaseCombatWeapon *pWeapon, CBaseEntity *pTarget);
	virtual void				DoMuzzleFlash();


	// Relationships
	virtual void				AddEntityRelationship(CBaseEntity *pEntity, Disposition_t nDisposition, int nPriority);
	virtual bool				RemoveEntityRelationship(CBaseEntity *pEntity);
	virtual void				AddClassRelationship(Class_T nClass, Disposition_t nDisposition, int nPriority);

	// This is a hack to blat out the current active weapon...
	// Used by weapon_slam + game_ui
	virtual void				OnChangeActiveWeapon(CBaseCombatWeapon *pOldWeapon, CBaseCombatWeapon *pNewWeapon) {}


	virtual CNavArea*			GetLastKnownArea(void) const { return m_lastNavArea; }		// return the last nav area the player occupied - NULL if unknown
	virtual bool				IsAreaTraversable(const CNavArea *area) const;							// return true if we can use the given area 
	virtual void				ClearLastKnownArea(void);
	virtual void				UpdateLastKnownArea(void);										// invoke this to update our last known nav area (since there is no think method chained to CBaseCombatCharacter)
	virtual void				OnNavAreaChanged(CNavArea *enteredArea, CNavArea *leftArea) { }	// invoked (by UpdateLastKnownArea) when we enter a new nav area (or it is reset to NULL)
	virtual void				OnNavAreaRemoved(CNavArea *removedArea);

	// -----------------------
	// Notification from INextBots.
	// -----------------------
	virtual void				OnPursuedBy(INextBot * RESTRICT pPursuer) {} // called every frame while pursued by a bot in DirectChase.




	virtual void	NetworkStateChanged_m_iAmmo(void);
	virtual void	NetworkStateChanged_m_iAmmo(void*);







public:
	bool					m_bForceServerRagdoll;
	bool					m_bPreventWeaponPickup;

	float					m_flNextAttack;			// cannot attack again until this time

	Hull_t					m_eHull;

	int						m_bloodColor;			// color of blood particless

	// -------------------
	// combat ability data
	// -------------------
	float					m_flFieldOfView;		// cosine of field of view for this character
	Vector					m_HackedGunPos;			// HACK until we can query end of gun
	string_t				m_RelationshipString;	// Used to load up relationship keyvalues
	float					m_impactEnergyScale;// scale the amount of energy used to calculate damage this ent takes due to physics

	int						m_LastHitGroup;			// the last body region that took damage
	float					m_flDamageAccumulator;	// so very small amounts of damage do not get lost.
	int						m_iDamageCount;			// # of times NPC has been damaged.  used for tracking 1-shot kills.

	// Weapon proficiency gets calculated each time an NPC changes his weapon, and then
	// cached off as the CurrentWeaponProficiency.
	WeaponProficiency_t		m_CurrentWeaponProficiency;

	// ---------------
	//  Relationships
	// ---------------
	CUtlVector<Relationship_t>	m_Relationship;	// Array of relationships

	// shared ammo slots
	int m_iAmmo[MAX_AMMO_SLOTS];

	// Usable character items 
	CBaseCombatWeaponHandle	m_hMyWeapons[MAX_WEAPONS];

	CBaseCombatWeaponHandle	m_hActiveWeapon;


	IntervalTimer			m_aliveTimer;

	unsigned int			m_hasBeenInjured;							// bitfield corresponding to team ID that did the injury	


	// we do this because MAX_TEAMS is 32, which is wasteful for most games
	enum { MAX_DAMAGE_TEAMS = 4 };
	struct DamageHistory
	{
		int team;					// which team hurt us (TEAM_INVALID means slot unused)
		IntervalTimer interval;		// how long has it been
	};
	DamageHistory			m_damageHistory[MAX_DAMAGE_TEAMS];

	// last known navigation area of player - NULL if unknown
	CNavArea*				m_lastNavArea;
	CAI_MoveMonitor			m_NavAreaUpdateMonitor;
	int						m_registeredNavTeam; // ugly, but needed to clean up player team counts in nav mesh
};

#endif // BASECOMBATCHARACTER_H