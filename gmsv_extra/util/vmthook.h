#ifndef VMTHOOK_H
#define VMTHOOK_H
#include "../include/baseinclude.h"
#include "../Source SDK/tier1/utlvector.h"
class VMTHook
{
public:
	struct vmthooks_t
	{
		int	index = 0;
		unsigned int OriginalFunctionPtr = 0;
	};
	VMTHook(void* instance);
	~VMTHook();

	void*	HookFunction(int index, void* pfnHook);
	void*	UnhookFunction(int index);
private:
	bool FindHookWithIndex(int index, vmthooks_t& hook);
	void DeleteObjectWithIndex(int index);
private:
	void* m_pVMT = nullptr;
	int size = 0;
	CUtlVector<vmthooks_t>*	VMTInfo = nullptr;	
};
#endif