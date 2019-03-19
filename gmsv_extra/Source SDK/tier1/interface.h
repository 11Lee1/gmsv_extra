typedef void* (*CreateInterfaceFn)(const char *Name, int *ReturnCode);
typedef void* (*InstantiateInterfaceFn)();
class IBaseInterface
{
public:
	virtual	~IBaseInterface() {}
};
class InterfaceReg
{
public:
	BYTE			m_CreateFn[4];
	const char		*m_pName;
	InterfaceReg	*m_pNext;
};
enum
{
	IFACE_OK = 0,
	IFACE_FAILED
};
enum Sys_Flags
{
	SYS_NOFLAGS = 0x00,
	SYS_NOLOAD = 0x01   // no loading, no ref-counting, only returns handle if lib is loaded. 
};
class CSysModule;
class CDllDemandLoader;