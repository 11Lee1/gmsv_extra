#ifndef GMODPLAYER_H
#define GMODPLAYER_H

#include "../hl2mp/hl2mp_player.h"


class CGMOD_Player : public CHL2MP_Player // wow what a pain in the ass to get to this point.
{
public:
	virtual void	SetPlayerColor(Vector);
	virtual void	SetWeaponColor(Vector);
};

#endif