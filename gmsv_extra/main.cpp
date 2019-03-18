#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <vector>
#include <Psapi.h>
#include <intrin.h>
#include <iterator>
#include <string>
#include <math.h>
#include <assert.h>
#include <cstdint>
#include <xmmintrin.h>
#include <d3d9.h>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <random>

void main() {
	printf("");
}


BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}