#ifndef ILUAGAMECALLBACK_H
#define ILUAGAMECALLBACK_H

namespace GarrysMod
{
	namespace Lua
	{
		class ILuaObject;
		class CLuaObject;
	};
};

class Color;
class CLuaError;
class ILuaInterface;
class ILuaGameCallback
{
public:
	virtual GarrysMod::Lua::CLuaObject* CreateLuaObject() = 0;
	virtual void		DestroyLuaObject(GarrysMod::Lua::ILuaObject* pObj) = 0;
	virtual void		ErrorPrint(char const* msg, bool) = 0;
	virtual void		Msg(char const* msg, bool) = 0;
	virtual void		MsgColour(char const* msg, const Color&) = 0;
	virtual void		LuaError(CLuaError*) = 0;
	virtual void		InterfaceCreated(ILuaInterface*) = 0;
};


#endif