#ifndef PROJECT_H
#define PROJECT_H
#include "../interfaces.h"
#include "../include.h"
#include "../Hooks/hook.h"

void TestCallBack(edict_t* pPlayer) {
	char* str = net_ReadString();
	printf("out: %s\n", str);

	net_DisposeString(str);		// so we don't have memory leaks
}


void projectMain() {
	net_Receive("test_12", TestCallBack);
}
#endif