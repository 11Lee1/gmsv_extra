#include "../hook.h"
#include <stdio.h>
#include "../../Source SDK/server/baseentity.h"

typedef CBaseEntity CGMOD_Player; // till I finish CGMOD_Player

typedef void(__thiscall* CGMOD_Player__FireBulletsFn)(CGMOD_Player*, const FireBulletsInfo_t &);
CGMOD_Player__FireBulletsFn orgCGMOD_Player__FireBullets = nullptr;

void __fastcall hookCGMOD_Player__FireBullets(CGMOD_Player* thisptr, void* edx, const FireBulletsInfo_t & fb) {
	printf("someone shot a bullet\n");
	return orgCGMOD_Player__FireBullets(thisptr, fb);
}

void Hooks::Hook_CGMOD_Player__FireBullets() {
	if (!orgCGMOD_Player__FireBullets)
		orgCGMOD_Player__FireBullets = (CGMOD_Player__FireBulletsFn)h_CGMOD_Player->HookFunction(114/*function index*/, hookCGMOD_Player__FireBullets);
}
void Hooks::Unhook_CGMOD_Player__FireBullets() {
	if (orgCGMOD_Player__FireBullets) {
		orgCGMOD_Player__FireBullets = nullptr;
		h_CGMOD_Player->UnhookFunction(114);
	}
}