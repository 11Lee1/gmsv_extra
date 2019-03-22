#ifdef _WIN32
#pragma once
#endif
// another gigapaste
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x ) (getBits(x[0]) << 4 | getBits(x[1]))

namespace Util
{
	namespace Pattern
	{
		static uintptr_t FindPattern(std::string moduleName, std::string pattern)
		{
			const char* pat = pattern.c_str();
			uintptr_t firstMatch = 0;
			uintptr_t rangeStart = (uintptr_t)GetModuleHandleA(moduleName.c_str());
			MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
			uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;
			for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
				if (!*pat)
					return firstMatch;

				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch)
						firstMatch = pCur;

					if (!pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;

					else
						pat += 2;    //one ?
				}
				else {
					pat = pattern.c_str();
					firstMatch = 0;
				}
			}
			return 0;
		}
	};
};