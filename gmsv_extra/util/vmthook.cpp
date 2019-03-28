#include "vmthook.h"

// now hop off my dick laxol
VMTHook::VMTHook(void* instance) {
	if (!instance)
		return;

	m_pVMT = *(void**)instance;
	VMTInfo = new CUtlVector<vmthooks_t>;
}

VMTHook::~VMTHook() {
	for (int i = 0; i < VMTInfo->Size(); i++) {
		UnhookFunction(VMTInfo->Element(i).index);
	}
	delete VMTInfo;
}
bool VMTHook::FindHookWithIndex(int index, vmthooks_t& hook) {
	if (!VMTInfo->Size())
		return false;

	for (int i = 0; i < VMTInfo->Size(); i++) {
		if (VMTInfo->Element(i).index != index)
			continue;

		hook = VMTInfo->Element(i);
		return true;
	}
	return false;
}
void VMTHook::DeleteObjectWithIndex(int index) {
	if (!VMTInfo->Size())
		return;

	for (int i = 0; i < VMTInfo->Size(); i++) {
		if (VMTInfo->Element(i).index != index)
			continue;

		VMTInfo->Remove(i);
		return;
	}
}
void* VMTHook::HookFunction(int index, void* pfnHook) {
	DWORD OldProtect, OldProtect2;
	if (!((unsigned int*)m_pVMT)[index])
		return nullptr;

	unsigned int OriginalFunctionPtr = ((unsigned int*)m_pVMT)[index];
	VMTInfo->AddToTail(vmthooks_t{ index,OriginalFunctionPtr });

	void* writelocation = (void*)((unsigned int)m_pVMT + (0x4 * index));
	VirtualProtect(writelocation, 0x4, PAGE_EXECUTE_READWRITE, &OldProtect);
	((unsigned int*)m_pVMT)[index] = (unsigned int)pfnHook;
	VirtualProtect(writelocation, 0x4, OldProtect, &OldProtect2);
	FlushInstructionCache(GetCurrentProcess(), 0, 0);
	return (void*)OriginalFunctionPtr;
}

void* VMTHook::UnhookFunction(int index) {
	DWORD OldProtect, OldProtect2;
	vmthooks_t hook;
	if (!VMTInfo->Size() || !FindHookWithIndex(index,hook))
		return nullptr;



	void* writelocation = (void*)((unsigned int)m_pVMT + (0x4 * index));
	VirtualProtect(writelocation, 0x4, PAGE_EXECUTE_READWRITE, &OldProtect);
	((unsigned int*)m_pVMT)[index] = hook.OriginalFunctionPtr;
	VirtualProtect(writelocation, 0x4, OldProtect, &OldProtect2);
	FlushInstructionCache(GetCurrentProcess(), 0, 0);
	DeleteObjectWithIndex(index);
	return nullptr;
}