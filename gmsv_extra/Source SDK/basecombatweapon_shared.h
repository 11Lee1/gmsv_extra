//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//===========================================================================//

#ifndef COMBATWEAPON_SHARED_H
#define COMBATWEAPON_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#include "vphysics_interface.h"
#include "predictable_entity.h"
#include "soundflags.h"
#include "weapon_parse.h"
#include "baseviewmodel_shared.h"
#include "weapon_proficiency.h"
#include "tier1/utlmap.h"

#if defined( CLIENT_DLL )
#define CBaseCombatWeapon C_BaseCombatWeapon
#endif

// Hacky
#if defined ( TF_CLIENT_DLL ) || defined ( TF_DLL )
#include "econ_entity.h"
#endif // TF_CLIENT_DLL || TF_DLL

#if !defined( CLIENT_DLL )
extern void OnBaseCombatWeaponCreated(CBaseCombatWeapon *);
extern void OnBaseCombatWeaponDestroyed(CBaseCombatWeapon *);

void *SendProxy_SendLocalWeaponDataTable(const SendProp *pProp, const void *pStruct, const void *pVarData, CSendProxyRecipients *pRecipients, int objectID);
#endif

class CBasePlayer;
class CBaseCombatCharacter;
class IPhysicsConstraint;
class CUserCmd;

// How many times to display altfire hud hints (per weapon)
#define WEAPON_ALTFIRE_HUD_HINT_COUNT	1
#define WEAPON_RELOAD_HUD_HINT_COUNT	1

//Start with a constraint in place (don't drop to floor)
#define	SF_WEAPON_START_CONSTRAINED	(1<<0)	
#define SF_WEAPON_NO_PLAYER_PICKUP	(1<<1)
#define SF_WEAPON_NO_PHYSCANNON_PUNT (1<<2)

//Percent
#define	CLIP_PERC_THRESHOLD		0.75f	

// Put this in your derived class definition to declare it's activity table
// UNDONE: Cascade these?
#define DECLARE_ACTTABLE()		static acttable_t m_acttable[];\
	acttable_t *ActivityList( void );\
	int ActivityListCount( void );

// You also need to include the activity table itself in your class' implementation:
// e.g.
//	acttable_t	CWeaponStunstick::m_acttable[] = 
//	{
//		{ ACT_MELEE_ATTACK1, ACT_MELEE_ATTACK_SWING, TRUE },
//	};
//
// The stunstick overrides the ACT_MELEE_ATTACK1 activity, replacing it with ACT_MELEE_ATTACK_SWING.
// This animation is required for this weapon's operation.
//

// Put this after your derived class' definition to implement the accessors for the
// activity table.
// UNDONE: Cascade these?
#define IMPLEMENT_ACTTABLE(className) \
	acttable_t *className::ActivityList( void ) { return m_acttable; } \
	int className::ActivityListCount( void ) { return ARRAYSIZE(m_acttable); } \

typedef struct
{
	int			baseAct;
	int			weaponAct;
	bool		required;
} acttable_t;

class CHudTexture;
class Color;

namespace vgui2
{
	typedef unsigned long HFont;
}

// -----------------------------------------
//	Vector cones
// -----------------------------------------
// VECTOR_CONE_PRECALCULATED - this resolves to vec3_origin, but adds some
// context indicating that the person writing the code is not allowing
// FireBullets() to modify the direction of the shot because the shot direction
// being passed into the function has already been modified by another piece of
// code and should be fired as specified. See GetActualShotTrajectory(). 

// NOTE: The way these are calculated is that each component == sin (degrees/2)
#define VECTOR_CONE_PRECALCULATED	vec3_origin
#define VECTOR_CONE_1DEGREES		Vector( 0.00873, 0.00873, 0.00873 )
#define VECTOR_CONE_2DEGREES		Vector( 0.01745, 0.01745, 0.01745 )
#define VECTOR_CONE_3DEGREES		Vector( 0.02618, 0.02618, 0.02618 )
#define VECTOR_CONE_4DEGREES		Vector( 0.03490, 0.03490, 0.03490 )
#define VECTOR_CONE_5DEGREES		Vector( 0.04362, 0.04362, 0.04362 )
#define VECTOR_CONE_6DEGREES		Vector( 0.05234, 0.05234, 0.05234 )
#define VECTOR_CONE_7DEGREES		Vector( 0.06105, 0.06105, 0.06105 )
#define VECTOR_CONE_8DEGREES		Vector( 0.06976, 0.06976, 0.06976 )
#define VECTOR_CONE_9DEGREES		Vector( 0.07846, 0.07846, 0.07846 )
#define VECTOR_CONE_10DEGREES		Vector( 0.08716, 0.08716, 0.08716 )
#define VECTOR_CONE_15DEGREES		Vector( 0.13053, 0.13053, 0.13053 )
#define VECTOR_CONE_20DEGREES		Vector( 0.17365, 0.17365, 0.17365 )

//-----------------------------------------------------------------------------
// Purpose: Base weapon class, shared on client and server
//-----------------------------------------------------------------------------

#if defined USES_ECON_ITEMS
#define BASECOMBATWEAPON_DERIVED_FROM		CEconEntity
#else 
#define BASECOMBATWEAPON_DERIVED_FROM		CBaseAnimating
#endif 

//-----------------------------------------------------------------------------
// Collect trace attacks for weapons that fire multiple projectiles per attack that also penetrate
//-----------------------------------------------------------------------------
class CDmgAccumulator
{
public:
	CDmgAccumulator(void);
	~CDmgAccumulator();

#ifdef GAME_DLL
	virtual void Start(void) { m_bActive = true; }
	virtual void AccumulateMultiDamage(const CTakeDamageInfo &info, CBaseEntity *pEntity);
	virtual void Process(void);

private:
	CTakeDamageInfo					m_updatedInfo;
	CUtlMap< int, CTakeDamageInfo >	m_TargetsDmgInfo;
#endif	// GAME_DLL

private:
	bool							m_bActive;

};

//-----------------------------------------------------------------------------
// Purpose: Client side rep of CBaseTFCombatWeapon 
//-----------------------------------------------------------------------------
// Hacky
class CBaseCombatWeapon : public BASECOMBATWEAPON_DERIVED_FROM
{
public:
	DECLARE_CLASS(CBaseCombatWeapon, BASECOMBATWEAPON_DERIVED_FROM);
	DECLARE_NETWORKCLASS();
public:
	virtual 				~CBaseCombatWeapon();



	// Subtypes are used to manage multiple weapons of the same type on the player.
	/*273*/virtual int				GetSubType(void) { return m_iSubType; }
	/*274*/virtual void			SetSubType(int iType) { m_iSubType = iType; }

	/*275*/virtual void			Equip(CBaseCombatCharacter *pOwner);
	/*276*/virtual void			Drop(const Vector &vecVelocity);

	/*277*/virtual	int				UpdateClientData(CBasePlayer *pPlayer);

	/*278*/virtual bool			IsAllowedToSwitch(void);
	/*279*/virtual bool			CanBeSelected(void);
	/*280*/virtual bool			VisibleInWeaponSelection(void);
	/*281*/virtual bool			HasAmmo(void);

	// Weapon Pickup For Player
	/*282*/virtual void			SetPickupTouch(void);
	/*283*/virtual void 			DefaultTouch(CBaseEntity *pOther);	// default weapon touch
	/*284*/virtual void			GiveTo(CBaseEntity *pOther);

	// HUD Hints
	/*285*/virtual bool			ShouldDisplayAltFireHUDHint();
	/*286*/virtual void			DisplayAltFireHudHint();
	/*287*/virtual void			RescindAltFireHudHint(); ///< undisplay the hud hint and pretend it never showed.

	/*288*/virtual bool			ShouldDisplayReloadHUDHint();
	/*289*/virtual void			DisplayReloadHudHint();
	/*290*/virtual void			RescindReloadHudHint();

	// Weapon client handling
	/*291*/virtual void			SetViewModelIndex(int index = 0);
	/*292*/virtual bool			SendWeaponAnim(int iActivity);
	/*293*/virtual void			SendViewModelAnim(int nSequence);

	/*294*/virtual void			SetViewModel();

	/*295*/virtual bool			HasWeaponIdleTimeElapsed(void);
	/*296*/virtual void			SetWeaponIdleTime(float time);
	/*297*/virtual float			GetWeaponIdleTime(void);

	// Weapon selection
	/*298*/virtual bool			HasAnyAmmo(void);							// Returns true is weapon has ammo
	/*299*/virtual bool			HasPrimaryAmmo(void);						// Returns true is weapon has ammo
	/*300*/virtual bool			HasSecondaryAmmo(void);					// Returns true is weapon has ammo

	/*301*/virtual bool			CanHolster(void) { return TRUE; };		// returns true if the weapon can be holstered
	/*302*/virtual bool			DefaultDeploy(char *szViewModel, char *szWeaponModel, int iActivity, char *szAnimExt);
	/*303*/virtual bool			CanDeploy(void) { return true; }			// return true if the weapon's allowed to deploy
	/*304*/virtual bool			Deploy(void);								// returns true is deploy was successful
	/*305*/virtual bool			Holster(CBaseCombatWeapon *pSwitchingTo = NULL);
	/*306*/virtual CBaseCombatWeapon *GetLastWeapon(void) { return this; }
	/*307*/virtual void			SetWeaponVisible(bool visible);
	/*308*/virtual bool			IsWeaponVisible(void);
	/*309*/virtual bool			ReloadOrSwitchWeapons(void);
	/*310*/virtual void			OnActiveStateChanged(int iOldState) { return; }
	/*311*/virtual bool			HolsterOnDetach() { return false; }
	/*312*/virtual bool			IsHolstered() { return false; }
	/*313*/virtual void			Detach() {}

	// Weapon behaviour
	/*314*/virtual void			ItemPreFrame(void);					// called each frame by the player PreThink
	/*315*/virtual void			ItemPostFrame(void);					// called each frame by the player PostThink
	/*316*/virtual void			ItemBusyFrame(void);					// called each frame by the player PostThink, if the player's not ready to attack yet
	/*317*/virtual void			ItemHolsterFrame(void) {};			// called each frame by the player PreThink, if the weapon is holstered
	/*318*/virtual void			WeaponIdle(void);						// called when no buttons pressed
	/*319*/virtual void			HandleFireOnEmpty();					// Called when they have the attack button down


	/*320*/virtual bool			CanPerformSecondaryAttack();
	/*321*/virtual bool			ShouldBlockPrimaryFire() { return false; }

	/*322*/virtual bool			IsWeaponZoomed() { return false; }		// Is this weapon in its 'zoomed in' mode?

	// Reloading
	/*323*/virtual	void			CheckReload(void);
	/*324*/virtual void			FinishReload(void);
	/*325*/virtual void			AbortReload(void);
	/*326*/virtual bool			Reload(void);

	/*327*/virtual bool			AutoFiresFullClip(void) { return false; }
	/*328*/virtual void			UpdateAutoFire(void);

	// Weapon firing
	/*329*/virtual void			PrimaryAttack(void);						// do "+ATTACK"
	/*330*/virtual void			SecondaryAttack(void) { return; }			// do "+ATTACK2"

	// Firing animations
	/*331*/virtual Activity		GetPrimaryAttackActivity(void);
	/*332*/virtual Activity		GetSecondaryAttackActivity(void);
	/*333*/virtual Activity		GetDrawActivity(void);
	/*334*/virtual float			GetDefaultAnimSpeed(void) { return 1.0; }

	// Bullet launch information
	/*335*/virtual int				GetBulletType(void);
	/*336*/virtual const Vector&	GetBulletSpread(void);
	/*337*/virtual Vector			GetBulletSpread(WeaponProficiency_t proficiency) { return GetBulletSpread(); }
	/*338*/virtual float			GetSpreadBias(WeaponProficiency_t proficiency) { return 1.0; }
	/*339*/virtual float			GetFireRate(void);
	/*340*/virtual int				GetMinBurst() { return 1; }
	/*341*/virtual int				GetMaxBurst() { return 1; }
	/*342*/virtual float			GetMinRestTime() { return 0.3; }
	/*343*/virtual float			GetMaxRestTime() { return 0.6; }
	/*344*/virtual int				GetRandomBurst();
	/*345*/virtual void			WeaponSound(WeaponSound_t sound_type, float soundtime = 0.0f);
	/*346*/virtual void			StopWeaponSound(WeaponSound_t sound_type);
	/*347*/virtual const WeaponProficiencyInfo_t *GetProficiencyValues();

	// Autoaim
	/*348*/virtual float			GetMaxAutoAimDeflection() { return 0.99f; }
	/*349*/virtual float			WeaponAutoAimScale() { return 1.0f; } // allows a weapon to influence the perceived size of the target's autoaim radius.

	// TF Sprinting functions
	/*350*/virtual bool			StartSprinting(void) { return false; };
	/*351*/virtual bool			StopSprinting(void) { return false; };

	// TF Injury functions
	/*352*/virtual float			GetDamage(float flDistance, int iLocation) { return 0.0; };

	/*353*/virtual void			SetActivity(Activity act, float duration);

	/*354*/virtual void			AddViewKick(void); // Add in the view kick for the weapon

	/*355*/virtual char*			GetDeathNoticeName(void);	// Get the string to print death notices with

	/*356*/virtual void			OnPickedUp(CBaseCombatCharacter *pNewOwner);

	/*367*/virtual void			AddViewmodelBob(CBaseViewModel *viewmodel, Vector &origin, QAngle &angles) {};
	/*358*/virtual float			CalcViewmodelBob(void) { return 0.0f; };

	// Returns information about the various control panels
	/*359*/virtual void 			GetControlPanelInfo(int nPanelIndex, const char *&pPanelName);
	/*360*/virtual void			GetControlPanelClassName(int nPanelIndex, const char *&pPanelName);

	/*361*/virtual bool			ShouldShowControlPanels(void) { return true; }

	//All weapons can be picked up by NPCs by default
	/*362*/virtual bool			CanBePickedUpByNPCs(void) { return true; }

	/*363*/virtual int				GetSkinOverride() const { return -1; }


	// Weapon info accessors for data in the weapon's data file
	/*364*/virtual const char*		GetViewModel(int viewmodelindex = 0) const;
	/*365*/virtual const char*		GetWorldModel(void) const;
	/*366*/virtual const char*		GetAnimPrefix(void) const;
	/*367*/virtual int				GetMaxClip1(void) const;
	/*368*/virtual int				GetMaxClip2(void) const;
	/*369*/virtual int				GetDefaultClip1(void) const;
	/*370*/virtual int				GetDefaultClip2(void) const;
	/*371*/virtual int				GetWeight(void) const;
	/*372*/virtual bool			AllowsAutoSwitchTo(void) const;
	/*373*/virtual bool			AllowsAutoSwitchFrom(void) const;
	/*374*/virtual void			ForceWeaponSwitch();
	/*375*/virtual int				GetWeaponFlags(void) const;
	/*376*/virtual int				GetSlot(void) const;
	/*377*/virtual int				GetPosition(void) const;
	/*378*/virtual char const*		GetName(void) const;
	/*379*/virtual char const*		GetPrintName(void) const;
	/*380*/virtual char const*		GetShootSound(int iIndex) const;
	/*381*/virtual int				GetRumbleEffect() const;
	/*382*/virtual bool			UsesClipsForAmmo1(void) const;
	/*383*/virtual bool			UsesClipsForAmmo2(void) const;

	/*384*/virtual char const*		GetHoldType();
	/*385*/virtual void			SetHoldType(char const*);

	// derive this function if you mod uses encrypted weapon info files
	/*386*/virtual const unsigned char *GetEncryptionKey(void);

	/*387*/virtual int				GetPrimaryAmmoType(void)  const { return m_iPrimaryAmmoType; }
	/*388*/virtual int				GetSecondaryAmmoType(void) const { return m_iSecondaryAmmoType; }
	/*389*/virtual int				Clip1() { return m_iClip1; }
	/*390*/virtual int				Clip2() { return m_iClip2; }

	/*391*/virtual CHudTexture const	*GetSpriteActive(void) const;
	/*392*/virtual CHudTexture const	*GetSpriteInactive(void) const;
	/*393*/virtual CHudTexture const	*GetSpriteAmmo(void) const;
	/*394*/virtual CHudTexture const	*GetSpriteAmmo2(void) const;
	/*395*/virtual CHudTexture const	*GetSpriteCrosshair(void) const;
	/*396*/virtual CHudTexture const	*GetSpriteAutoaim(void) const;
	/*397*/virtual CHudTexture const	*GetSpriteZoomedCrosshair(void) const;
	/*398*/virtual CHudTexture const	*GetSpriteZoomedAutoaim(void) const;

	/*399*/virtual Activity		ActivityOverride(Activity baseAct, bool *pRequired);
	/*400*/virtual	acttable_t*		ActivityList(void) { return NULL; }
	/*401*/virtual	int				ActivityListCount(void) { return 0; }

	/*402*/virtual void			PoseParameterOverride(bool);
	/*403*/virtual void			PoseParamList(int &);

	/*404*/virtual bool			ShouldUseLargeViewModelVROverride() { return false; }


	/*405*/virtual void			FallInit(void);						// prepare to fall to the ground
	/*406*/virtual void			FallThink(void);						// make the weapon fall to the ground after spawning

	/*407*/virtual void			Materialize(void);					// make a weapon visible and tangible
	/*408*/virtual void			CheckRespawn(void);					// see if this weapon should respawn after being picked up

	// Weapon dropping / destruction
	/*409*/virtual void			Delete(void);
	/*410*/virtual void			Kill(void);

	/*411*/virtual int				CapabilitiesGet(void) { return 0; }

	// Returns bits for	weapon conditions
	/*412*/virtual bool			WeaponLOSCondition(const Vector &ownerPos, const Vector &targetPos, bool bSetConditions);
	/*413*/virtual	int				WeaponRangeAttack1Condition(float flDot, float flDist);
	/*414*/virtual	int				WeaponRangeAttack2Condition(float flDot, float flDist);
	/*415*/virtual	int				WeaponMeleeAttack1Condition(float flDot, float flDist);
	/*416*/virtual	int				WeaponMeleeAttack2Condition(float flDot, float flDist);

	/*417*/virtual void			Operator_FrameUpdate(CBaseCombatCharacter  *pOperator);
	/*418*/virtual void			Operator_HandleAnimEvent(animevent_t *pEvent, CBaseCombatCharacter *pOperator);
	/*419*/virtual void			Operator_ForceNPCFire(CBaseCombatCharacter  *pOperator, bool bSecondary) { return; }


	/*420 LMAO DUDE 420*/virtual CDmgAccumulator *GetDmgAccumulator(void) { return NULL; }

	/*421*/virtual bool			CanLower(void) { return false; }
	/*422*/virtual bool			Ready(void) { return false; }
	/*423*/virtual bool			Lower(void) { return false; }

	/*424*/virtual void			HideThink(void);
	/*425*/virtual bool			CanReload(void);

	

	/*426*/virtual int		GetPlayerDamage();
	/*427*/virtual void	EquipAmmo(CBaseEntity*);
	/*428*/virtual bool	ShouldDropOnDie();
	/*429*/virtual bool	ShouldDrawViewModel();
	/*430*/virtual float	GetLastShootTime();
	/*431*/virtual void	UpdateLastShootTime(float);
	/*432*/virtual void	ForcePlayerPickup(CBasePlayer*);
	/*433*/virtual void	OnRangeAttack1();
	/*434*/virtual void	GModNPCAttackHack();

public:
	typedef CHandle< CBaseCombatCharacter > CBaseCombatCharacterHandle;
	CBaseCombatCharacterHandle		m_hOwner;				// Player carrying this weapon


	BYTE pad_unk05[0x4];

	int								m_nViewModelIndex;

	float							m_flNextPrimaryAttack;						// soonest time ItemPostFrame will call PrimaryAttack
	float							m_flNextSecondaryAttack;					// soonest time ItemPostFrame will call SecondaryAttack
	float							m_flTimeWeaponIdle;							// soonest time ItemPostFrame will call WeaponIdle
	// Weapon state
	bool							m_bInReload;			// Are we in the middle of a reload;
	bool							m_bFireOnEmpty;			// True when the gun is empty and the player is still holding down the attack key(s)
	bool							m_bFiringWholeClip;		// Are we in the middle of firing the whole clip;
	// Weapon art
	int								m_iViewModelIndex;
	int								m_iWorldModelIndex;
	// Sounds
	float							m_flNextEmptySoundTime;				// delay on empty sound playing


	Activity						m_Activity;
	int								m_nIdealSequence;
	Activity						m_IdealActivity;

	bool							m_bRemoveable;

	int								m_iPrimaryAmmoCount;
	int								m_iSecondaryAmmoCount;

	// Weapon data
	int								m_iState;				// See WEAPON_* definition
	string_t						m_iszName;				// Classname of this weapon.
	int								m_iPrimaryAmmoType;		// "primary" ammo index into the ammo info array 
	int								m_iSecondaryAmmoType;	// "secondary" ammo index into the ammo info array
	int								m_iClip1;				// number of shots left in the primary weapon clip, -1 it not used
	int								m_iClip2;				// number of shots left in the secondary weapon clip, -1 it not used
	bool							m_bFiresUnderwater;		// true if this weapon can fire underwater
	bool							m_bAltFiresUnderwater;		// true if this weapon can fire underwater
	float							m_fMinRange1;			// What's the closest this weapon can be used?
	float							m_fMinRange2;			// What's the closest this weapon can be used?
	float							m_fMaxRange1;			// What's the furthest this weapon can be used?
	float							m_fMaxRange2;			// What's the furthest this weapon can be used?
	bool							m_bReloadsSingly;		// True if this weapon reloads 1 round at a time
	float							m_fFireDuration;		// The amount of time that the weapon has sustained firing
	int								m_iSubType;

	float							m_flUnlockTime;
	EHANDLE							m_hLocker;				// Who locked this weapon.

	bool							m_bFlipViewModel;

	WEAPON_FILE_INFO_HANDLE			m_hWeaponFileInfo;
	IPhysicsConstraint*				m_pConstraint;

	int								m_iAltFireHudHintCount;		// How many times has this weapon displayed its alt-fire HUD hint?
	int								m_iReloadHudHintCount;		// How many times has this weapon displayed its reload HUD hint?
	bool							m_bAltFireHudHintDisplayed;	// Have we displayed an alt-fire HUD hint since this weapon was deployed?
	bool							m_bReloadHudHintDisplayed;	// Have we displayed a reload HUD hint since this weapon was deployed?
	float							m_flHudHintPollTime;	// When to poll the weapon again for whether it should display a hud hint.
	float							m_flHudHintMinDisplayTime; // if the hint is squelched before this, reset my counter so we'll display it again.


	// Outputs
	COutputEvent					m_OnPlayerUse;		// Fired when the player uses the weapon.
	COutputEvent					m_OnPlayerPickup;	// Fired when the player picks up the weapon.
	COutputEvent					m_OnNPCPickup;		// Fired when an NPC picks up the weapon.
	COutputEvent					m_OnCacheInteraction;	// For awarding lambda cache achievements in HL2 on 360. See .FGD file for details 

};

#endif // COMBATWEAPON_SHARED_H