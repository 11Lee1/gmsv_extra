#ifndef SERVERTOCLIENT_H
#define SERVERTOCLIENT_H

// most of this shit is from what I can remember from the clientside realm
// so I'm going to assume it's basically the same thing for the server.

// Also going to put my little twist on it.

#include "../../Source SDK/engine/net_chan.h"
#include "../../Source SDK/netmessages.h"
#include "../../Source SDK/networkstringtabledefs.h"
#include "../../Source SDK/tier1/utlvector.h"

class GMod_NetReceive
{
public:
	typedef void(*GModNetMsgReceiveCallBackFn)(edict_t*);
	struct GModNetMsgReceive_t {
		char const*			m_NetMessageName = nullptr;
		unsigned int		m_NetworkID = INVALID_STRING_INDEX;
		GModNetMsgReceiveCallBackFn m_CallBackFn = nullptr;
	};

	struct GModNetMsgData_t {
		int				m_iDunno = -1;
		edict_t*		m_pPlayer = nullptr;
		bf_read*		m_pData = nullptr;
		int				m_iLength = -1;
	};

	~GMod_NetReceive();
	GMod_NetReceive();

	void AddReceiver(char const* NetMsgName, GModNetMsgReceiveCallBackFn fn, bool CreateNewString = true /*create a new one if one isn't found*/);
	void ProcessNetMsg(int dunno, edict_t* pPlayer, bf_read* data, int length);
protected:
	void CallReceivers(edict_t* pPlayer, unsigned int NetworkID);
	void ResetData() { CurrentData.m_iDunno = -1; CurrentData.m_pPlayer = nullptr; CurrentData.m_pData = nullptr; CurrentData.m_iLength = -1; }
	void FillData(int dunno, edict_t* pPlayer, bf_read* data, int length) { CurrentData.m_iDunno = dunno; CurrentData.m_pPlayer = pPlayer; CurrentData.m_pData = data; CurrentData.m_iLength = length; }
	
protected:
	CUtlVector<GModNetMsgReceive_t>* Receivers = nullptr;
public:
	GModNetMsgData_t		CurrentData;
};
extern GMod_NetReceive* g_pGModNetMsgReceiver;


#define net_Receive(messageName,callbackfn)						\
	g_pGModNetMsgReceiver->AddReceiver(messageName,callbackfn);	\

#endif