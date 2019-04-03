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
			CLuaGameObject();
			/*68 - 272*/virtual CBaseEntity*	GetMemberEntity(char const*, CBaseEntity*);
			/*69 - 276*/virtual void			SetMemberEntity_0(char const*, CBaseEntity*);
			/*70 - 280*/virtual void			SetMemberEntity_1(float, CBaseEntity*);
			/*71 - 284*/virtual bool			IsEntity();
			/*72 - 288*/virtual CBaseEntity*	GetEntity();
			/*73 - 292*/virtual void			SetEntity(CBaseEntity*);
			/*74 - 396*/virtual void			SetMemberVector_0(float, Vector*);
			/*75 - 300*/virtual void			SetMemberVector_1(char const*, Vector&);
			/*76 - 304*/virtual void			SetMemberVector_2(char const*, Vector*);
			/*77 - 308*/virtual Vector&			GetMemberVector_0(int);
			/*78 - 312*/virtual	Vector&			GetMemberVector_1(char const*, Vector*);
			/*79 - 316*/virtual Vector&			GetVector();
			/*80 - 320*/virtual bool			IsVector();
			/*81 - 324*/virtual void			SetMemberAngle(char const*, QAngle*);
			/*82 - 328*/virtual QAngle&			GetMemberAngle(char const*, QAngle*);
			/*83 - 332*/virtual QAngle&			GetAngle();
			/*84 - 336*/virtual bool			IsAngle();
		public:
			CLuaObject luaobj;
		};
	};
};

#endif