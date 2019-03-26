#include "hook.h"
#include "../interfaces.h"
#include "../Source SDK/eiface.h"
#include "../Source SDK/server/baseentity.h"
#include "../Source SDK/edict.h"
#include <windows.h>

Hooks::Hooks() {
	h_IServerGameClients = nullptr;
	h_CGMOD_Player = nullptr;
	SetupHooks();
	HookFunctions();
}
Hooks::~Hooks() {
	UnhookFunctions();
	if (h_IServerGameClients)
		h_IServerGameClients->~VMTHook();

	if (h_CGMOD_Player)
		h_CGMOD_Player->~VMTHook();

	delete this;
}
void Hooks::SetupHooks() {
	h_IServerGameClients = new VMTHook(g_pInterfaces->ServerGameClients());
	

	while (!h_CGMOD_Player) {
		for (int i = 1; i < g_pInterfaces->Globals()->maxClients; i++) {
			edict_t* ent = g_pInterfaces->EngineServer()->PEntityOfEntIndex(i);
			if (ent && ent->GetUnknown()) {
				if (((CBaseEntity*)ent->GetUnknown())->IsPlayer()) {
					h_CGMOD_Player = new VMTHook(ent->GetUnknown());
					break; 
				}
			}
		}
	Sleep(1000);
	} 

	/*

		kk so the first one is a little easier to understand, but the second one probably not.

		so since we're byte patching the original VMT for that object it will affect all objects that 
		use a pointer to that VMT.  What we're doing is looping through all the player slots
		(index 1->maxclients are reserved for players) to get a pointer to the objects VMT (because that's
		easier than sigscanning and would make it a million times easier for you guys reading this)

		stuff to keep in mind.

		an object that inherits virtual functions from other object will not share the same VMT pointer if
		new virtual functions are declared (that's why I did above) I'll do another visual because 
		I know I didn't explain that properly.


		class ISomething // interface class
		{
		public:
			virtual void PrintMSG(char const* msg) = 0;
			virtual void PrintSize() = 0;
		};

		class CSomething : public ISomething
		{
		public:
			void PrintMSG(char const* msg) {
				printf("%s\n",msg);
			}
			void PrintSize() {
				printf("%i\n",size);
			}
		public:
			int size = 12;
		};

		class CRandom : public CSomething
		{
		public:
			virtual void PrintRandomMessage() {
				printf("%s\n",RandomMessage);
			}
		public:
			char const* RandomMessage = "hello";
		};


		{ UNCHANGED
			CSomething in memory
			0x00001000	=	0x00006000
			0x00001004	=	12			<--- size

			CSomething VMT 
			0x00006000	=	0x00000100	<--- PrintMSG
			0x00006004	=	0x00000200	<--- PrintSize


			CRandom in memory
			0x00002000	=	0x00007000
			0x00002004	=	12			<--- size
			0x00002008	=	0x00001337	<--- RandomMessage

			CRandom VMT
			0x00007000	=	0x00000100	<--- inherited from CSomething
			0x00007004	=	0x00000200	<--- inherited from CSomething
			0x00007008	=	0x00000300	<--- PrintRandomMessage

		} UNCHANGED

		{ BYTE PATCHED VALUE TO CSomething
			
			CSomething in memory
			0x00001000	=	0x00006000
			0x00001004	=	12			<--- size

			CSomething VMT
			0x00006000	=	0x00000100	<--- PrintMSG
			0x00006004	=	0x00000321	<--- changed value


			CRandom in memory, unaffected by the changes made to CSomething VMT
			0x00002000	=	0x00007000
			0x00002004	=	12			<--- size
			0x00002008	=	0x00001337	<--- RandomMessage

			CRandom VMT
			0x00007000	=	0x00000100	<--- inherited from CSomething
			0x00007004	=	0x00000200	<--- inherited from CSomething
			0x00007008	=	0x00000300	<--- PrintRandomMessage

		} BYTE PATCHED VALUE TO CSomething


		so anyway basically we're making a hook on firebullets and will only be called if a player 
		shoots.
	*/
}
void Hooks::HookFunctions() {
	// IServerGameClients
	HookClientConnect();

	// CGMOD_Player
	Hook_CGMOD_Player__FireBullets();
}
void Hooks::UnhookFunctions() {
	// IServerGameClients
	UnhookClientConnect();
	Unhook_CGMOD_Player__FireBullets();
}