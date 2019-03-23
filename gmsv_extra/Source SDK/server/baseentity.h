#ifndef BASEENTITY_H
#define BASEENTITY_H
#ifdef _WIN32
#pragma once
#endif

#define TEAMNUM_NUM_BITS	6

#include "../string_t.h"
#include "../iserverentity.h"
#include "ServerNetworkProperty.h"
#include "../shareddefs.h"
#include "../predictableid.h"
#include "variant_t.h"
#include "../tier1/utllinkedlist.h"
#include "../collisionproperty.h"
#include "../entityoutput.h"
#include "../takedamageinfo.h"
#include "../../GLUA/LuaObject/CLuaGameObject.h"
//entitylist.h
enum notify_system_event_t
{
	NOTIFY_EVENT_TELEPORT = 0,
	NOTIFY_EVENT_DESTROY,
};
struct notify_teleport_params_t
{
	Vector prevOrigin;
	QAngle prevAngles;
	bool physicsRotate;
};
struct notify_destroy_params_t
{
};

struct notify_system_event_params_t
{
	union
	{
		const notify_teleport_params_t *pTeleport;
		const notify_destroy_params_t *pDestroy;
	};
	notify_system_event_params_t(const notify_teleport_params_t *pInTeleport) { pTeleport = pInTeleport; }
	notify_system_event_params_t(const notify_destroy_params_t *pInDestroy) { pDestroy = pInDestroy; }
};

// end entitylist.h

#define DECLARE_PREDICTABLE()											\
	public:																\
		static typedescription_t m_PredDesc[];							\
		static datamap_t m_PredMap;										\
		virtual datamap_t *GetPredDescMap( void );						\
template <typename T> friend datamap_t *PredMapInit(T *)

class CDamageModifier;

//-----------------------------------------------------------------------------
// Entity events... targetted to a particular entity
// Each event has a well defined structure to use for parameters
//-----------------------------------------------------------------------------
enum EntityEvent_t
{
	ENTITY_EVENT_WATER_TOUCH = 0,		// No data needed
	ENTITY_EVENT_WATER_UNTOUCH,			// No data needed
	ENTITY_EVENT_PARENT_CHANGED,		// No data needed
};


//-----------------------------------------------------------------------------
typedef void (CBaseEntity::*BASEPTR)(void);
typedef void (CBaseEntity::*ENTITYFUNCPTR)(CBaseEntity *pOther);
typedef void (CBaseEntity::*USEPTR)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#define DEFINE_THINKFUNC( function ) DEFINE_FUNCTION_RAW( function, BASEPTR )
#define DEFINE_ENTITYFUNC( function ) DEFINE_FUNCTION_RAW( function, ENTITYFUNCPTR )
#define DEFINE_USEFUNC( function ) DEFINE_FUNCTION_RAW( function, USEPTR )


// For CLASSIFY
enum Class_T
{
	CLASS_NONE = 0,
	CLASS_PLAYER,
	CLASS_PLAYER_ALLY,
	CLASS_PLAYER_ALLY_VITAL,
	CLASS_ANTLION,
	CLASS_BARNACLE,
	CLASS_BULLSEYE,
	//CLASS_BULLSQUID,	
	CLASS_CITIZEN_PASSIVE,
	CLASS_CITIZEN_REBEL,
	CLASS_COMBINE,
	CLASS_COMBINE_GUNSHIP,
	CLASS_CONSCRIPT,
	CLASS_HEADCRAB,
	//CLASS_HOUNDEYE,
	CLASS_MANHACK,
	CLASS_METROPOLICE,
	CLASS_MILITARY,
	CLASS_SCANNER,
	CLASS_STALKER,
	CLASS_VORTIGAUNT,
	CLASS_ZOMBIE,
	CLASS_PROTOSNIPER,
	CLASS_MISSILE,
	CLASS_FLARE,
	CLASS_EARTH_FAUNA,
	CLASS_HACKED_ROLLERMINE,
	CLASS_COMBINE_HUNTER,

	NUM_AI_CLASSES
};

struct thinkfunc_t
{
	BASEPTR		m_pfnThink;
	string_t	m_iszContext;
	int			m_nNextThinkTick;
	int			m_nLastThinkTick;

	DECLARE_SIMPLE_DATADESC();
};


//
// Structure passed to input handlers.
//
struct inputdata_t
{
	CBaseEntity *pActivator;		// The entity that initially caused this chain of output events.
	CBaseEntity *pCaller;			// The entity that fired this particular output.
	variant_t value;				// The data parameter for this output.
	int nOutputID;					// The unique ID of the output that was fired.
};

// Serializable list of context as set by entity i/o and used for deducing proper
//  speech state, et al.
struct ResponseContext_t
{
	DECLARE_SIMPLE_DATADESC();

	string_t		m_iszName;
	string_t		m_iszValue;
	float			m_fExpirationTime;		// when to expire context (0 == never)
};


struct TimedOverlay_t
{
	char 			*msg;
	int				msgEndTime;
	int				msgStartTime;
	TimedOverlay_t	*pNextTimedOverlay;
};


class CBasePlayer;
class CStudioHdr;
class CEntityMapData;
class IEntitySaveUtils;
class CBaseAnimating;
class CBaseAnimatingOverlay;
class IResponseSystem;
class CDmgAccumulator;
class CBaseCombatCharacter;
class INextBot;
class CBaseCombatWeapon;
class IServerVehicle;
class AI_CriteriaSet;
class CAI_BaseNPC;
class gamevcollisionevent_t;
class ILuaObject;
class CBaseEntity : public IServerEntity
{
public:
	DECLARE_CLASS_NOBASE(CBaseEntity);
	virtual ~CBaseEntity();
	
	// prediction system
	DECLARE_PREDICTABLE();
	// network data
	DECLARE_SERVERCLASS();
	// data description
	DECLARE_DATADESC();

	/*
		GetDataDescMap() // index 11
	*/

	/*12*/virtual void			SetModelIndexOverride(int index, int nValue);
	/*13*/virtual bool			TestCollision(const Ray_t& ray, unsigned int mask, trace_t& trace);
	/*14*/virtual bool			TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr);
	/*15*/virtual void			ComputeWorldSpaceSurroundingBox(Vector *pWorldMins, Vector *pWorldMaxs);
	/*16*/virtual	bool		ShouldCollide(int collisionGroup, int contentsMask) const;
	/*17*/virtual void			SetOwnerEntity(CBaseEntity* pOwner);
	/*18*/virtual int			ShouldTransmit(const CCheckTransmitInfo *pInfo);
	/*19*/virtual int			UpdateTransmitState();
	/*20*/virtual void			SetTransmit(CCheckTransmitInfo *pInfo, bool bAlways);
	/*21*/virtual const char*	GetTracerType(void);
	// initialization
	/*22*/virtual void			Spawn(void);
	/*23*/virtual void			Precache(void) {}
	/*24*/virtual void			SetModel(const char *szModelName);
	/*25*/virtual CStudioHdr *	OnNewModel();
	/*26*/virtual void			PostConstructor(const char *szClassname);
	/*27*/virtual void			PostClientActive(void);
	/*28*/virtual void			ParseMapData(CEntityMapData *mapData);
	/*29*/virtual bool			KeyValue(const char *szKeyName, const char *szValue);
	/*30*/virtual bool			KeyValue(const char *szKeyName, float flValue);
	/*31*/virtual bool			KeyValue(const char *szKeyName, const Vector &vecValue);
	/*32*/virtual bool			GetKeyValue(const char *szKeyName, char *szValue, int iMaxLen);
	// Activate - called for each entity after each load game and level load
	/*33*/virtual void			Activate(void);
	/*34*/virtual void			SetParent(CBaseEntity* pNewParent, int iAttachment = -1);
	/*35*/virtual int			ObjectCaps(void);
	/*36*/virtual bool			AcceptInput(const char *szInputName, CBaseEntity *pActivator, CBaseEntity *pCaller, variant_t Value, int outputID);
	/*37*/virtual void			GetInputDispatchEffectPosition(const char *sInputString, Vector &pOrigin, QAngle &pAngles);
	/*38*/virtual	void		DrawDebugGeometryOverlays(void);
	/*39*/virtual int			DrawDebugTextOverlays(void);
	// save/restore
	// only overload these if you have special data to serialize
	/*40*/virtual int			Save(ISave &save);
	/*41*/virtual int			Restore(IRestore &restore);
	/*42*/virtual bool			ShouldSavePhysics();

	// handler to reset stuff before you are restored
	// NOTE: Always chain to base class when implementing this!
	/*43*/virtual void			OnSave(IEntitySaveUtils *pSaveUtils);

	// handler to reset stuff after you are restored
	// called after all entities have been loaded from all affected levels
	// called before activate
	// NOTE: Always chain to base class when implementing this!
	/*44*/virtual void			OnRestore();
	/*45*/virtual int			RequiredEdictIndex(void) { return -1; }
	/*46*/virtual void			MoveDone(void);
	/*47*/virtual void			Think(void);
	/*48*/virtual void			NetworkStateChanged_m_nNextThinkTick();
	/*49*/virtual void			NetworkStateChanged_m_nNextThinkTick(void*);
	/*50*/virtual CBaseAnimating* GetBaseAnimating() { return 0; }
	/*51*/virtual CBaseAnimatingOverlay* GetBaseAnimatingOverlay() { return 0; }
	/*52*/virtual IResponseSystem *GetResponseSystem();
	/*53*/virtual void			DispatchResponse(const char *conceptName);
	// Classify - returns the type of group (i.e, "houndeye", or "human military" so that NPCs with different classnames
	// still realize that they are teammates. (overridden for NPCs that form groups)
	/*54*/virtual Class_T 		Classify(void);
	/*55*/virtual void			DeathNotice(CBaseEntity *pVictim) {}// NPC maker children use this to tell the NPC maker that they have died.
	/*56*/virtual bool			ShouldAttractAutoAim(CBaseEntity *pAimingEnt) { }
	/*57*/virtual float			GetAutoAimRadius();
	/*58*/virtual Vector		GetAutoAimCenter() { }
	/*59*/virtual ITraceFilter*	GetBeamTraceFilter(void);
	/*60*/virtual bool			PassesDamageFilter(const CTakeDamageInfo &info);
	/*61*/virtual void			TraceAttack(const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr, CDmgAccumulator *pAccumulator = NULL);
	/*62*/virtual bool			CanBeHitByMeleeAttack(CBaseEntity *pAttacker) { return true; }
	/*63*/virtual int			OnTakeDamage(const CTakeDamageInfo &info);
	/*64*/virtual void			AdjustDamageDirection(const CTakeDamageInfo &info, Vector &dir, CBaseEntity *pEnt) {}
	/*65*/virtual int			TakeHealth(float flHealth, int bitsDamageType);

	/*66*/virtual bool			IsAlive(void);
	// Entity killed (only fired once)
	/*67*/virtual void			Event_Killed(const CTakeDamageInfo &info);
	/*68*/virtual void			Event_KilledOther(CBaseEntity *pVictim, const CTakeDamageInfo &info) { return; }
	/*69*/virtual int			BloodColor(void);
	/*70*/virtual bool			IsTriggered(CBaseEntity *pActivator) { return true; }
	/*71*/virtual bool			IsNPC(void) const { return false; }
	/*72*/virtual CBaseCombatCharacter *MyCombatCharacterPointer(void) { return NULL; }
	/*73*/virtual INextBot *	MyNextBotPointer(void) { return NULL; }
	/*74*/virtual float			GetDelay(void) { return 0; }
	/*75*/virtual bool			IsMoving(void);
	/*76*/virtual char const*	DamageDecal(int bitsDamageType, int gameMaterial);
	/*77*/virtual void			DecalTrace(trace_t *pTrace, char const *decalName);
	/*78*/virtual void			ImpactTrace(trace_t *pTrace, int iDamageType, const char *pCustomImpactName = NULL);
	/*79*/virtual bool			OnControls(CBaseEntity *pControls) { return false; }
	/*80*/virtual bool			HasTarget(string_t targetname);
	/*81*/virtual bool			IsPlayer(void) const { return false; }
	/*82*/virtual bool			IsNetClient(void) const { return false; }
	/*83*/virtual bool			IsTemplate(void) { return false; }
	/*84*/virtual bool			IsBaseObject(void) const { return false; }
	/*85*/virtual bool			IsBaseTrain(void) const { return false; }
	/*86*/virtual bool			IsCombatItem(void) const { return false; }
	/*87*/virtual bool			IsBaseCombatWeapon(void) const { return false; }
	/*88*/virtual bool			IsWearable(void) const { return false; }
	/*89*/virtual CBaseCombatWeapon *MyCombatWeaponPointer(void) { return NULL; }
	// If this is a vehicle, returns the vehicle interface
	/*90*/virtual IServerVehicle*	 GetServerVehicle() { return NULL; }

	// UNDONE: Make this data instead of procedural?
	/*91*/virtual bool			IsViewable(void);					// is this something that would be looked at (model, sprite, etc.)?
	/*92*/virtual void			ChangeTeam(int iTeamNum); // Assign this entity to a team.
	/*93*/virtual void			OnEntityEvent(EntityEvent_t event, void *pEventData);


	// UNDONE: Do these three functions actually need to be virtual???
	/*94*/virtual bool			CanStandOn(CBaseEntity *pSurface);
	/*95*/virtual bool			CanStandOn(edict_t	*ent);
	/*96*/virtual CBaseEntity	*GetEnemy(void) { return NULL; }
	/*97*/virtual CBaseEntity *GetEnemy(void) const { return NULL; }
	/*98*/virtual void			ViewPunch(const QAngle &angleOffset);
	/*99*/virtual void			Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	/*100*/virtual void			StartTouch(CBaseEntity *pOther);
	/*101*/virtual void			Touch(CBaseEntity *pOther);
	/*102*/virtual void			EndTouch(CBaseEntity *pOther);
	/*103*/virtual void			StartBlocked(CBaseEntity *pOther) {}
	/*104*/virtual void			Blocked(CBaseEntity *pOther);
	/*105*/virtual void			EndBlocked(void) {}

	// Physics simulation
	/*106*/virtual void			PhysicsSimulate(void);

	/*107*/virtual void			UpdateOnRemove(void);
	/*108*/virtual void			StopLoopingSounds(void) {}
	/*109*/virtual	bool		SUB_AllowedToFade(void);
	// change position, velocity, orientation instantly
	// passing NULL means no change
	/*110*/virtual void			Teleport(const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity);
	// notify that another entity (that you were watching) was teleported
	/*111*/virtual void			NotifySystemEvent(CBaseEntity *pNotify, notify_system_event_t eventType, const notify_system_event_params_t &params);

	/*112*/virtual void			MakeTracer(const Vector &vecTracerSrc, const trace_t &tr, int iTracerType);
	/*113*/virtual int			GetTracerAttachment(void);
	/*114*/virtual void			FireBullets(const FireBulletsInfo_t &info);
	/*115*/virtual void			DoImpactEffect(trace_t &tr, int nDamageType); // give shooter a chance to do a custom impact.
	/*116*/virtual void			ModifyFireBulletsDamage(CTakeDamageInfo* dmgInfo) {}
	/*117*/virtual CBaseEntity *Respawn(void) { return NULL; }
	/*118*/virtual bool			IsLockedByMaster(void) { return false; }
	/*119*/virtual int			GetMaxHealth() const { return m_iMaxHealth; }
	/*120*/virtual void			ModifyOrAppendCriteria(AI_CriteriaSet& set);
	/*121*/virtual void			NetworkStateChanged_m_iMaxHealth(void);
	/*122*/virtual void			NetworkStateChanged_m_iMaxHealth(void*);
	/*123*/virtual void			NetworkStateChanged_m_iHealth(void);
	/*124*/virtual void			NetworkStateChanged_m_iHealth(void*);
	/*125*/virtual void			NetworkStateChanged_m_lifeState(void);
	/*126*/virtual void			NetworkStateChanged_m_lifeState(void*);
	/*127*/virtual void			NetworkStateChanged_m_takedamage(void);
	/*128*/virtual void			NetworkStateChanged_m_takedamage(void*);
	// Damage accessors
	/*129*/virtual int			GetDamageType() const;
	/*130*/virtual float		GetDamage() { return 0; }
	/*131*/virtual void			SetDamage(float flDamage) {}

	/*132*/virtual Vector		EyePosition(void);			// position of eyes
	/*133*/virtual const QAngle &EyeAngles(void);		// Direction of eyes in world space
	/*134*/virtual const QAngle &LocalEyeAngles(void);	// Direction of eyes
	/*135*/virtual Vector 		EarPosition(void); // position of ears

	/*136*/virtual Vector		BodyTarget(const Vector &posSrc, bool bNoisy = true);		// position to shoot at
	/*137*/virtual Vector		HeadTarget(const Vector &posSrc);
	/*138*/virtual void			GetVectors(Vector* forward, Vector* right, Vector* up) const;

	/*139*/virtual const Vector&GetViewOffset() const;
	/*140*/virtual void			SetViewOffset(const Vector &v);

	/*141*/virtual Vector		GetSmoothedVelocity(void);
	// FIXME: Figure out what to do about this
	/*142*/virtual void			GetVelocity(Vector *vVelocity, AngularImpulse *vAngVelocity = NULL);
	/*143*/virtual	bool		FVisible(CBaseEntity *pEntity, int traceMask = MASK_BLOCKLOS, CBaseEntity **ppBlocker = NULL);
	/*144*/virtual bool			FVisible(const Vector &vecTarget, int traceMask = MASK_BLOCKLOS, CBaseEntity **ppBlocker = NULL);

	/*145*/virtual bool			CanBeSeenBy(CAI_BaseNPC *pNPC) { return true; } // allows entities to be 'invisible' to NPC senses.
	// This function returns a value that scales all damage done by this entity.
	// Use CDamageModifier to hook in damage modifiers on a guy.
	/*146*/virtual float		GetAttackDamageScale(CBaseEntity *pVictim);
	// This returns a value that scales all damage done to this entity
	// Use CDamageModifier to hook in damage modifiers on a guy.
	/*147*/virtual float		GetReceivedDamageScale(CBaseEntity *pAttacker);
	// Gets the velocity we impart to a player standing on us
	/*148*/virtual void			GetGroundVelocityToApply(Vector &vecGroundVel) { vecGroundVel = vec3_origin; }
	/*149*/virtual bool			PhysicsSplash(const Vector &centerPoint, const Vector &normal, float rawSpeed, float scaledSpeed) { return false; }
	/*150*/virtual void			Splash() {}
	/*151*/virtual const Vector&WorldSpaceCenter() const;
	/*152*/virtual Vector		GetSoundEmissionOrigin() const;
	/*153*/virtual void			ModifyEmitSoundParams(EmitSound_t &params);
	/*154*/virtual bool			IsDeflectable() { return false; }
	/*155*/virtual void			Deflected(CBaseEntity *pDeflectedBy, Vector &vecDir) {}
	/*156*/virtual bool			CreateVPhysics();
	/*157*/virtual bool			ForceVPhysicsCollide(CBaseEntity *pEntity) { return false; }
	/*158*/virtual void			VPhysicsDestroyObject(void);
	/*159*/virtual bool			GMOD_VPhysicsTest(IPhysicsObject *pPhysics);
	/*160*/virtual void			VPhysicsUpdate(IPhysicsObject *pPhysics);
	/*161*/virtual int			VPhysicsTakeDamage(const CTakeDamageInfo &info);
	/*162*/virtual void			VPhysicsShadowCollision(int index, gamevcollisionevent_t *pEvent);
	/*163*/virtual void			VPhysicsShadowUpdate(IPhysicsObject *pPhysics) {}
	/*164*/virtual void			VPhysicsCollision(int index, gamevcollisionevent_t *pEvent);
	/*165*/virtual void			GMOD_VPhysicsCollision(int index, gamevcollisionevent_t *pEvent);
	/*166*/virtual void			GMOD_GetPhysBoneMatrix(int); /////////////////////////////////////////////////////////////////////////// <---- look into
	/*167*/virtual void			VPhysicsFriction(IPhysicsObject *pObject, float energy, int surfaceProps, int surfacePropsHit);
	/*168*/virtual void			UpdatePhysicsShadowToCurrentPosition(float deltaTime);
	/*169*/virtual int			VPhysicsGetObjectList(IPhysicsObject **pList, int listMax);
	/*170*/virtual bool			VPhysicsIsFlesh(void);
	/*171*/virtual	CBasePlayer *HasPhysicsAttacker(float dt) { return NULL; }
	// UNDONE: Make this data?
	/*172*/virtual unsigned int	PhysicsSolidMaskForEntity(void) const;
	/*173*/virtual void			ResolveFlyCollisionCustom(trace_t &trace, Vector &vecVelocity);
	/*174*/virtual void			PerformCustomPhysics(Vector *pNewPosition, Vector *pNewVelocity, QAngle *pNewAngles, QAngle *pNewAngVelocity);
	/*175*/virtual	Vector		GetStepOrigin(void) const;
	/*176*/virtual	QAngle		GetStepAngles(void) const;
	/*177*/virtual bool			ShouldDrawWaterImpacts() { return true; }
	/*178*/virtual void			NetworkStateChanged_m_fFlags(void);
	/*179*/virtual void			NetworkStateChanged_m_fFlags(void*);
	/*180*/virtual void			NetworkStateChanged_m_nWaterLevel(void);
	/*181*/virtual void			NetworkStateChanged_m_nWaterLevel(void*);
	/*182*/virtual void			NetworkStateChanged_m_hGroundEntity(void);
	/*183*/virtual void			NetworkStateChanged_m_hGroundEntity(void*);
	/*184*/virtual void			NetworkStateChanged_m_vecBaseVelocity(void);
	/*185*/virtual void			NetworkStateChanged_m_vecBaseVelocity(void*);
	/*186*/virtual void			NetworkStateChanged_m_flFriction(void);
	/*187*/virtual void			NetworkStateChanged_m_flFriction(void*);
	/*188*/virtual void			NetworkStateChanged_m_vecViewOffset(void);
	/*189*/virtual void			NetworkStateChanged_m_vecViewOffset(void*);
	/*190*/virtual bool			ShouldBlockNav() const { return true; }
	/*191*/virtual bool			ShouldForceTransmitsForTeam(int iTeamNum);
	/*192*/virtual void			VPhysicsGetElement(int);
	/*193*/virtual void			OnOwnerChanged(void);
	/*194*/virtual bool			IsARagdoll(void);
	/*195*/virtual void			SetMaterialOverride(char const*);
	/*196*/virtual char const*	GetMaterialOverride(void);
	/*197*/virtual bool			IsPredicted(void);
	/*198*/virtual bool			IsWeapon(void);
	/*199*/virtual bool			IsVehicle(void);
	/*200*/virtual bool			IsJeep(void);
	/*201*/virtual bool			UsesLua(void);
	/*202*/virtual int			GetLuaEntityType(void);
	/*203*/virtual	void		PushEntity(void);
	/*204*/virtual void			Push_This_Entity(void);
	/*205*/virtual	void		SetPhysObject(int, IPhysicsObject*);
	/*206*/virtual void			SetEntity(char const*, CBaseEntity*);
	/*207*/virtual void			DeleteOnRemove(CBaseEntity*);
	/*208*/virtual void			DontDeleteOnRemove(CBaseEntity*);
	/*209*/virtual int			GetParentPhysicsNum(void);
	/*210*/virtual void			SetParentPhysicsNum(int);
	/*211*/virtual float		GetCreationTime(void);
	/*212*/virtual void			StartMotionController(void);
	/*213*/virtual void			StopMotionController(void);
	/*214*/virtual void			AttachObjectToMotionController(IPhysicsObject* pPhysics);
	/*215*/virtual void			DetachObjectFromMotionController(IPhysicsObject* pPhysics);
	/*216*/virtual void			SaveLua(ISave*);
	/*217*/virtual void			LoadLua(IRestore*);
	/*218*/virtual void			SetUseType(USE_TYPE type);
	/*219*/virtual void			UpdateBeforeRemove(int);
	/*220*/virtual char const*	GetLuaScriptName(void);
	/*221*/virtual bool			SpawnedViaLua(void);
	/*222*/virtual void			OverridePosition(void);
	/*223*/virtual void			InitializeScriptedEntity(char const*);
	/*224*/virtual void			ClearLuaData(void);
	/*225*/virtual void*		GetLuaTable(void);	/////////////////////// FIX ME
	/*226*/virtual void*		GetLuaEntity(void); /////////////////////// FIX ME
	/*227*/virtual void			Lua_OnEntityInitialized(void);
	/*228*/virtual void			SetLuaTable(ILuaObject*);
	/*229*/virtual	bool		HasLuatable(void);
	/*230*/virtual void			ForcePhysicsDropObject(void);
	/*231*/virtual void			StartDriving(CBasePlayer*);
	/*232*/virtual void			FinishDriving(CBasePlayer*);
	/*233*/virtual bool			GMOD_ShouldPreventTransmitToPlayer(CBasePlayer* pPlayer);
	/*234*/virtual bool			GMOD_SetShouldPreventTransmitToPlayer(CBasePlayer* pPlayer, bool state);
	/*235*/virtual bool			GMOD_ShouldPlayPhysicsSounds(void);
	/*236*/virtual void* 		Lua_GetLuaClass(void); /////////////////////// FIX ME
	/*237*/virtual INextBot* 	GetNextBot(void);

public:
	BYTE	pad_unk00[0x8];

	CServerNetworkProperty m_Network;

	// members
	string_t m_iClassname;  // identifier for entity creation and save/restore
	string_t m_iGlobalname; // identifier for carrying entity across level transitions
	string_t m_iParent;	// the name of the entities parent; linked into m_pParent during Activate()

	int	m_iHammerID; // Hammer unique edit id number

	// was pev->speed
	float			m_flSpeed;
	// was pev->renderfx
	unsigned char	m_nRenderFX;
	// was pev->rendermode
	unsigned char	m_nRenderMode;
	short			m_nModelIndex;

	// was pev->rendercolor
	color32			m_clrRender;

	// was pev->animtime:  consider moving to CBaseAnimating
	float			m_flPrevAnimTime;
	float			m_flAnimTime;
	float			m_flSimulationTime;
	int				m_ubInterpolationFrame;
	int				m_nLastThinkTick;

	// Certain entities (projectiles) can be created on the client and thus need a matching id number
	CPredictableId  m_PredictableID;

	// used so we know when things are no longer touching
	int				touchStamp;

	CUtlVector< thinkfunc_t >	m_aThinkFunctions;

	int	m_iCurrentThinkContext;

	CUtlVector< ResponseContext_t > m_ResponseContexts;

	BYTE	pad_unk01[0x8];


	// Map defined context sets
	string_t		m_iszResponseContext;

	// was pev->nextthink
	int				m_nNextThinkTick;
	// was pev->effects
	int				m_fEffects;

	CBaseEntity*	m_pLink;// used for temporary link-list operations. 

	// variables promoted from edict_t
	string_t		m_target;

	int				m_iMaxHealth; // CBaseEntity doesn't care about changes to this variable, but there are derived classes that do.
	int				m_iHealth;

	char			m_lifeState;
	char			m_takedamage;

	// Damage filtering
	string_t		m_iszDamageFilterName;	// The name of the entity to use as our damage filter.
	EHANDLE			m_hDamageFilter; // The entity that controls who can damage us.

	// Debugging / devolopment fields
	int				m_debugOverlays;	// For debug only (bitfields)
	TimedOverlay_t* m_pTimedOverlay; // For debug only

	// Which frame did I simulate?
	int				m_nSimulationTick;

	// FIXME: Make this private! Still too many references to do so...
	int				m_spawnflags;

	int				m_iEFlags; // entity flags EFL_*

	// was pev->flags
	int				m_fFlags;
	string_t		m_iName;

	CUtlLinkedList<CDamageModifier*, int> m_DamageModifiers;

	EHANDLE			m_pParent;  // for movement hierarchy
	BYTE			m_nTransmitStateOwnedCounter;

	unsigned char	m_iParentAttachment;
	unsigned char	m_MoveType;
	unsigned char	m_MoveCollide;

	// Our immediate parent in the movement hierarchy.
// FIXME: clarify m_pParent vs. m_pMoveParent
	EHANDLE			m_hMoveParent;
	// cached child list
	EHANDLE			m_hMoveChild;
	// generated from m_pMoveParent
	EHANDLE			m_hMovePeer;


	CCollisionProperty m_Collision;

	EHANDLE			m_hOwnerEntity; // only used to point to an edict it won't collide with
	EHANDLE			m_hEffectEntity; // Fire/Dissolve entity.

	int				m_CollisionGroup; // used to cull collision tests

	IPhysicsObject *m_pPhysicsObject; // pointer to the entity's physics object (vphysics.dll)

	float			m_flShadowCastDistance;
	float			m_flDesiredShadowCastDistance;

	// Team handling
	int				m_iInitialTeamNum;		// Team number of this entity's team read from file
	int				m_iTeamNum;				// Team number of this entity's team. 

	// Sets water type + level for physics objects
	unsigned char	m_nWaterTouch;
	unsigned char	m_nSlimeTouch;
	unsigned char	m_nWaterType;
	unsigned char	m_nWaterLevel;
	float			m_flNavIgnoreUntilTime;

	EHANDLE			m_hGroundEntity;
	float			m_flGroundChangeTime; // Time that the ground entity changed

	string_t		m_ModelName;

	// Velocity of the thing we're standing on (world space)
	Vector			m_vecBaseVelocity;

	// Global velocity
	Vector			m_vecAbsVelocity;

	// Local angular velocity
	QAngle			m_vecAngVelocity;

	// local coordinate frame of entity
	matrix3x4_t		m_rgflCoordinateFrame;

	// Physics state
	EHANDLE			m_pBlocker;
	// was pev->gravity;
	float			m_flGravity;  // rename to m_flGravityScale;
	// was pev->friction
	float			m_flFriction;
	float			m_flElasticity;

	// was pev->ltime
	float			m_flLocalTime;
	// local time at the beginning of this frame
	float			m_flVPhysicsUpdateLocalTime;
	// local time the movement has ended
	float			m_flMoveDoneTime;

	// A counter to help quickly build a list of potentially pushed objects for physics
	int				m_nPushEnumCount;

	Vector			m_vecAbsOrigin;
	Vector			m_vecVelocity;



	unsigned char	m_iTextureFrameIndex;
	bool			m_bSimulatedEveryTick;
	bool			m_bAnimatedEveryTick;
	bool			m_bAlternateSorting;

	// User outputs. Fired when the "FireInputX" input is triggered.
	COutputEvent	m_OnUser1;
	COutputEvent	m_OnUser2;
	COutputEvent	m_OnUser3;
	COutputEvent	m_OnUser4;

	QAngle			m_angAbsRotation;
	Vector			m_vecOrigin;
	QAngle			m_angRotation;
	CBaseHandle		m_RefEHandle;


	// was pev->view_ofs ( FIXME:  Move somewhere up the hierarch, CBaseAnimating, etc. )
	Vector			m_vecViewOffset;

	// dynamic model state tracking
	bool			m_bDynamicModelAllowed;
	bool			m_bDynamicModelPending;
	bool			m_bDynamicModelSetBounds;
	bool			m_bIsPlayerSimulated;
	CHandle< CBasePlayer > m_hPlayerSimulationOwner;
	int				m_fDataObjectTypes; // 0x334

	BYTE	pad_unk02[0x328];

	GarrysMod::Lua::CLuaObject		m_LuaObject; // 0x660
	GarrysMod::Lua::CLuaGameObject* m_LuaGameObject_LuaTable;	// idk type is table
	GarrysMod::Lua::CLuaGameObject*	m_LuaGameObject_Entity;		// idk type is entity

	BYTE	pad_unk03[0xD14]; //0x1390  End of BaseEntity
};
#endif