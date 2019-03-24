#ifndef HOOK_H
#define HOOK_H
/*

	I'll give you guys a BASIC rundown on vmt hooking so you can do it yourself.

	functions with the "virtual" keyword have thier pointer stored within that object's
	virtual method table (or VMT for short) which is pretty much just an array of pointers
	that point to the functions with the "virtual" keyword as I stated earlier.  What you're 
	doing when you're hooking onto one of those functions is just replacing the pointer to
	the function with one of your own.  Incase you don't understand what I mean or I explained
	it poorly (which is probably the case) I'll do a little visual below.


	class SomeClass
	{
	public:
		virtual bool IsActive() { return Active; }
		virtual void RandomFunction() {
			if(this->IsActive())
				printf("RandomNumber = %i\n",RandomNumber);
		}
		virtual void RandomFunction2() {
			if(this->IsActive())
				printf("RandomNumber2 = %i\n",RandomNumber2);
		}
	public:
		int		RandomNumber = 1337;
		bool	Active = true;
		short	RandomNumber2 = 2448;
	};

	pointer to object as an example
	0x10000000	= 0x20000000

	what the class would look like in memory
	0x20000000	= 0x50000000	<--	the classes VMT	(4 bytes in size)
	0x20000004	= 1337			<--	RandomNumber	(4 bytes in size)
	0x20000008	= 1				<--	Active			(1 byte in size)
	0x20000009	= 0				<--|
	0x2000000A	= 0				<--|
	0x2000000B	= 0				<--+-- unoccupied
	0x2000000C	= 2448			<--	RandomNumber2	(2 bytes in size)
	0x2000000E	= 0				<--|
	0x2000000F	= 0				<--+-- unoccupied


	Inside the VMT
	0x50000000	= 0x00001000	<-- IsActive			index 0 
	0x50000004	= 0x00002000	<-- RandomFunction		index 1
	0x50000008	= 0x00003000	<-- RandomFunction2		index 2

	
	Lets hook onto on of the functions.
	__stdcall bool hookRandomFunction2(SomeClass* ObjectPTR, void* NotImportant(you don't need to care about this.)) { 
		
		OriginalFunction(ObjectPTR);				calling the oirignal function at the top of the hook will cause the function to be called before yours.

		if(playcount == 0) {
			printf("hello\n");						This will cause "hello" to be printed and nothing else if the player count is 0
			return;		
		}
		if(playercount <= 10) {
			printf("hello2\n);						will cause "hello2" to be printed if the player count is <= 10 then return with 
			return OriginalFunction(ObjectPTR);		original function that will do invoke printf("RandomNumber2 = %i\n",ObjectPTR->RandomNumber2);
		}							

		return OriginalFunction(ObjectPTR);			you can choose whether or not to call the function at all in the hook but, if you call it at the bottom 
													of the hook your stuff we be run before the function is called.	
	}

	now what we do is we replace the pointer to the function in the VMT to our own function
	so that would look like this 

	BEFORE:
	0x50000000	= 0x00001000	<-- IsActive			index 0
	0x50000004	= 0x00002000	<-- RandomFunction		index 1
	0x50000008	= 0x00003000	<-- RandomFunction2		index 2

	AFTER:
	0x50000000	= 0x00001000	<-- IsActive			index 0
	0x50000004	= 0x00002000	<-- RandomFunction		index 1
	0x50000008	= 0x00005555	<-- OurHookedFunction	index 2

	so whenever the function in the VMT is called our function is called.


	and if that still isn't enough you can just look at how I do it below.
*/

class VMTHook;
class Hooks
{
public:
	Hooks();
	void SetupHooks();
	void HookFunctions();
protected:
	// IserverGameClients
	void HookClientConnect();
protected:
	VMTHook* h_IServerGameClients;
};
extern Hooks* hooks;

#endif