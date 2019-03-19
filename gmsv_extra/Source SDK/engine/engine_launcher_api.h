class CAppSystemGroup;
struct StartupInfo_t
{
	void *m_pInstance;
	const char *m_pBaseDirectory;	// Executable directory ("c:/program files/half-life 2", for example)
	const char *m_pInitialMod;		// Mod name ("cstrike", for example)
	const char *m_pInitialGame;		// Root game name ("hl2", for example, in the case of cstrike)
	CAppSystemGroup *m_pParentAppSystemGroup;
	bool m_bTextMode;
};
//-----------------------------------------------------------------------------
// Return values from the initialization stage of the application framework
//-----------------------------------------------------------------------------
enum
{
	INIT_RESTART = INIT_LAST_VAL,
	RUN_FIRST_VAL,
};


//-----------------------------------------------------------------------------
// Return values from IEngineAPI::Run.
//-----------------------------------------------------------------------------
enum
{
	RUN_OK = RUN_FIRST_VAL,
	RUN_RESTART,
};

//-----------------------------------------------------------------------------
// Main engine interface to launcher + tools
//-----------------------------------------------------------------------------
class CEngineAPI : public IAppSystem
{
public:
	virtual void SetStartupInfo(StartupInfo_t &info) = 0;
	virtual int Run() = 0;
	virtual void SetEngineWindow(void *hWnd) = 0;
	virtual void PostConsoleCommand(const char *pConsoleCommand) = 0;
	virtual bool IsRunningSimulation() const = 0;
	virtual void ActivateSimulation(bool bActive) = 0;
	virtual void SetMap(const char *pMapName) = 0;
};