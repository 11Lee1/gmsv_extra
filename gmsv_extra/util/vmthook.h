#ifndef VMTHOOK_H
#define VMTHOOK_H
#include "../include/baseinclude.h"
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
	std::vector<vmthooks_t> VMTInfo;
};
#endif