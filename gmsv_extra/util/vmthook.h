#ifndef VMTHOOK_H
#define VMTHOOK_H
/*

	credits to whoever made this so I don't have to lol

*/
#include "../include/baseinclude.h"
class VMTHook
{
public:
	void** m_pOriginalVTable;
	void** m_pNewVTable;
	void*** m_pInstance;

	int m_iNumIndices;

	VMTHook(void* instance);
	~VMTHook();

	int tellCount();

	void* hookFunction(int iIndex, void* pfnHook);
	void* unhookFunction(int iIndex);
	void* GetMethod(int iIndex);
	void* GetHookedMethod(int iIndex);
	void SetPadding(int pad);

	int padding;

};
#endif