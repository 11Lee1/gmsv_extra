#ifndef ISCRIPTEDENTITY_H
#define ISCRIPTEDENTITY_H

class IScriptedEntity
{
public: // fill out vmt later.
	virtual void NetworkStateChanged() = 0;
	virtual void NetworkStateChanged(void*) = 0;
};

#endif