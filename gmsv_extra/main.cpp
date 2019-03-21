#define INCLCONSOLE
#define __DLL


#include "include.h"


class CLuaNetworkedVars
{
public:
	struct LuaNetworkedVar_t
	{
		GarrysMod::Lua::CLuaGameObject m_LuaGameObject;
		BYTE pad_unk00[0x8];
	};

	struct LuaNetworkedVarEnts_t
	{
		CBaseHandle EntityRefHandle;
		CUtlRBTree<CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t, unsigned short, CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::CKeyLess, CUtlMemory<UtlRBTreeNode_t<CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t, unsigned short>, unsigned short>> NetVars;
	};


	int FindEntityVar(const CBaseHandle& EntityRefHandle, char const* VarName, int type = GarrysMod::Lua::Type::STRING); // just for testing.
private:
	LuaNetworkedVarEnts_t Ents[ENT_ENTRY_MASK];
};


int CLuaNetworkedVars::FindEntityVar(const CBaseHandle& EntityRefHandle, char const* VarName, int type) {
	if (!EntityRefHandle.IsValid())
		return 0;

	// holy expensive function...

	for (int i = 0; i < Ents[1].NetVars.Count(); i++) {
		CUtlMap<char const*, LuaNetworkedVar_t, unsigned short>::Node_t Element = Ents[EntityRefHandle.GetEntryIndex()].NetVars.Element(i);

		if (Element.elem.m_LuaGameObject.m_iLUA_TYPE != type)
			continue;

		if (!V_stricmp(Element.key, VarName)) {
			char const* str = Element.elem.m_LuaGameObject.GetString();
			if (str)
				printf("Found var %s     VALUE: %s\n", VarName, str);
		}
	}
	return 0;
}











#ifdef __DLL

#ifdef INCLCONSOLE
void AttachConsole(char const* name) {
	AllocConsole();
	FILE* fp;
	fp = freopen("CONOUT$", "w", stdout);

	SetConsoleTitleA(name);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 0x7);
}
#endif

void Loop()
{

	do {
		IVEngineServer* engineserver = g_pInterfaces->EngineServer();
		edict_t* entedict = engineserver->PEntityOfEntIndex(1);
		
		if (entedict) {
			CBaseEntity* player = (CBaseEntity*)entedict->GetUnknown();
			if (player && player->IsPlayer()) {
#ifdef INCLCONSOLE
				printf("player = 0x%X\n", player);
#endif

				/*
				
					you WILL crash if you do something like this with lua.
					do stuff that accesses lua inside of the game's loop
					ie within a hooked function.

				*/


				g_pInterfaces->g_LuaNetworkedVars->FindEntityVar(player->GetRefEHandle(), "UserGroup", false);
			}
		}
		

		Sleep(1000); // who cares we just want to loop shit for it's values etc
	} while (1);
}

int main() {
#ifdef INCLCONSOLE
	AttachConsole("Console");
#endif
	g_pInterfaces = new Interfaces;
	g_pInterfaces->_SetupInterfaces();

	Loop();

	return 1;
}

#define __INJECT
#ifdef __INJECT // note: calling require("extra") in lua will run the module but spit out an error via lua

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

#else
GMOD_MODULE_OPEN()
{
	main();
	return 1;
}
//lua_openscript sv.lua
GMOD_MODULE_CLOSE()
{
	return 1;
}

#endif // __INJECT
#else
int main() {
	Vector lol(0,0,0);
	Vector lol2(0, 0, 100);

	printf("X: %f      Y: %f      Z: %f\n", lol.x, lol.y, lol.z);

	printf("dist: %f\n", lol.DistTo(lol2));
	Sleep(100000);
	return 1;
}
#endif // __DLL