#ifndef CLUAGAMEOBJECT_H
#define CLUAGAMEOBJECT_H

#include "CLuaObject.h"

class CBaseEntity;
namespace GarrysMod
{
	namespace Lua
	{
		class CLuaGameObject : public CLuaObject
		{
		public:
			CLuaGameObject() : CLuaObject() {}
			/*67 - 276*/virtual CBaseEntity*	GetMemberEntity(char const*, CBaseEntity*);
			/*68 - 280*/virtual void			SetMemberEntity(char const*, CBaseEntity*);
			/*69 - 284*/virtual void			SetMemberEntity(float, CBaseEntity*);
			/*70 - 288*/virtual bool			IsEntity();
			/*71 - 292*/virtual CBaseEntity*	GetEntity();
			/*72 - 296*/virtual void			SetEntity(CBaseEntity*);
			/*73 - 300*/virtual void			SetMemberVector(float, Vector*);
			/*74 - 304*/virtual void			SetMemberVector(char const*, Vector&);
			/*75 - 308*/virtual void			SetMemberVector(char const*, Vector*);
			/*76 - 312*/virtual Vector&			GetMemberVector(int);
			/*77 - 316*/virtual	Vector&			GetMemberVector(char const*, Vector*);
			/*78 - 320*/virtual Vector&			GetVector();
			/*79 - 324*/virtual bool			IsVector();
			/*80 - 328*/virtual void			SetMemberAngle(char const*, QAngle*);
			/*81 - 332*/virtual QAngle&			GetMemberAngle(char const*, QAngle*);
			/*82 - 336*/virtual QAngle&			GetAngle();
			/*83 - 340*/virtual bool			IsAngle();
		};
	};
};

#endif