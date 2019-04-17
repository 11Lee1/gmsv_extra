#ifndef SERVERTOCLIENT_H
#define SERVERTOCLIENT_H

// most of this shit is from what I can remember from the clientside realm
// so I'm going to assume it's basically the same thing for the server.

// Also going to put my little twist on it.

#include "../../Source SDK/engine/net_chan.h"
#include "../../Source SDK/netmessages.h"
#include "../../Source SDK/networkstringtabledefs.h"
#include "../../Source SDK/tier1/utlvector.h"
#include "../../Source SDK/tier1/color.h"
#include "../../Source SDK/recipientfilter.h"
#include "../../Source SDK/server/player.h"

class CBaseClient;
class GMod_ServerToClient
{
public:
	GMod_ServerToClient() { m_pCurrentOutGoing = nullptr; }

	bool	StartNetMessage(char const* NetMsgName, bool Reliable = true); // returns false on fail.
	bool	StartNetMessage(unsigned short NetworkstringID, bool Reliable = true); // returns false on fail.
	bool	SendNetMsg(CBasePlayer* player);
	bool	SendNetMsg(CBaseClient* client);
	bool	SendNetMsg(CRecipientFilter& filter);
	bool	BroadcastMsg();

	void	WriteAngle(QAngle angle);
	void	WriteBit(BYTE val);
	void	WriteBool(bool state);
	void	WriteColor(Color color);
	void	WriteData(unsigned char* data);
	void	WriteDouble(double val);
	void	WriteEntity(CBaseEntity* ent);
	void	WriteFloat(float val);
	void	WriteInt(int val, int bitcount);
	void	WriteMatrix(VMatrix matrix);
	void	WriteNormal(Vector val);
	void	WriteString(char const* string);
	void	WriteUInt(unsigned int val, int bitcount);
	void	WriteVector(Vector val);
protected:
	void	RemoveCurrentMessage();
	CBaseClient* FindClient(int entindex);
	CBaseClient* FindClient(CBasePlayer* player);
private:
	BYTE	m_WriteBuffer[0xFFFF];
	bool	m_bReliable;
	SVC_GMod_ServerToClient*	m_pCurrentOutGoing;
};
extern GMod_ServerToClient* g_pGMod_ServerToClient;

#define net_Start(NetMsgName,unreliable)							\
	g_pGMod_ServerToClient->StartNetMessage(NetMsgName,!unreliable);\

#define net_Send(obj)						\
	g_pGMod_ServerToClient->SendNetMsg(obj);\

#define net_Broadcast()						\
	g_pGMod_ServerToClient->BroadcastMsg();	\



#define net_WriteAngle(QAngle)					\
	g_pGMod_ServerToClient->WriteAngle(QAngle);	\

#define net_WriteBit(BYTE)						\
	g_pGMod_ServerToClient->WriteBit(BYTE);		\

#define net_WriteBool(bool)						\
	g_pGMod_ServerToClient->WriteBool(bool);	\

#define net_WriteColor(Color)					\
	g_pGMod_ServerToClient->WriteColor(Color);	\

#define net_WriteData(Data)						\
	g_pGMod_ServerToClient->WriteData(Data);	\

#define net_WriteDouble(double)					\
	g_pGMod_ServerToClient->WriteDouble(double);\

#define net_WriteEntity(CBaseEntity)			\
	g_pGMod_ServerToClient->WriteEntity(CBaseEntity);\

#define net_WriteFloat(float)					\
	g_pGMod_ServerToClient->WriteFloat(float);	\

#define net_WriteInt(value, bitcount)			\
	g_pGMod_ServerToClient->WriteInt(value, bitcount);\

#define net_WriteMatrix(VMatrix)				\
	g_pGMod_ServerToClient->WriteMatrix(VMatrix);\

#define net_WriteNormal(Vector)					\
	g_pGMod_ServerToClient->WriteNormal(Vector);\

#define net_WriteString(string)					\
	g_pGMod_ServerToClient->WriteString(string);\

#define net_WriteUInt(val, bitcount)			\
	g_pGMod_ServerToClient->WriteUInt(val, bitcount);\

#define net_WriteVector(Vector)					\
	g_pGMod_ServerToClient->WriteVector(Vector);\

#endif