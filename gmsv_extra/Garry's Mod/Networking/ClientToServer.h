#ifndef CLIENTTOSERVER_H
#define CLIENTTOSERVER_H

// most of this shit is from what I can remember from the clientside realm
// so I'm going to assume it's basically the same thing for the server.

#include "../../Source SDK/engine/net_chan.h"
#include "../../Source SDK/netmessages.h"
#include "../../Source SDK/networkstringtabledefs.h"
#include "../../Source SDK/tier1/utlvector.h"
#include "../../Source SDK/tier1/color.h"

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

	BYTE	ReadByte();
	char*	ReadString();
	Vector	ReadVector();
	QAngle	ReadAngle();
	BYTE	ReadBit();
	double	ReadDouble();
	Color	ReadColor();
	int		ReadInt(int bitcount);
	CBaseEntity* ReadEntity();


protected:
	void CallReceivers(edict_t* pPlayer, unsigned int NetworkID);
	void ResetData() { CurrentData.m_iDunno = -1; CurrentData.m_pPlayer = nullptr; CurrentData.m_pData = nullptr; CurrentData.m_iLength = -1; }
	void FillData(int dunno, edict_t* pPlayer, bf_read* data, int length) { CurrentData.m_iDunno = dunno; CurrentData.m_pPlayer = pPlayer; CurrentData.m_pData = data; CurrentData.m_iLength = length; }
	void AddString(char* str);
	void DeleteReadStrings();
protected:
	CUtlVector<GModNetMsgReceive_t>* Receivers = nullptr;
	char NetMsgStringBuffer[0xFFFF];
public:
	char* nullstr = "\0";
	GModNetMsgData_t		CurrentData;
	CUtlVector<char*>* ReadStrings = nullptr;
};
extern GMod_NetReceive* g_pGModNetMsgReceiver;


#define net_Receive(messageName,callbackfn)						\
	g_pGModNetMsgReceiver->AddReceiver(messageName,callbackfn);	\

#define net_ReadByte()							\
	g_pGModNetMsgReceiver->ReadByte();			\

#define net_ReadString()						\
	g_pGModNetMsgReceiver->ReadString();		\

#define net_ReadVector()						\
	g_pGModNetMsgReceiver->ReadVector();		\

#define net_ReadAngle()							\
	g_pGModNetMsgReceiver->ReadAngle();			\

#define net_ReadBit()							\
	g_pGModNetMsgReceiver->ReadBit();			\
	
#define net_ReadBool()							\
	g_pGModNetMsgReceiver->ReadBit();			\

#define net_ReadDouble()						\
	g_pGModNetMsgReceiver->ReadDouble();		\

#define net_ReadColor()							\
	g_pGModNetMsgReceiver->ReadColor();			\

#define net_ReadInt(bits)						\
	g_pGModNetMsgReceiver->ReadInt(bits);		\

#define net_ReadEntity()						\
	g_pGModNetMsgReceiver->ReadEntity();		\

#endif