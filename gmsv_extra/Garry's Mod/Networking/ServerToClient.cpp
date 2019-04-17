#include "ServerToClient.h"
#include "gmod_net_util.h"
#include "../../interfaces.h"
#include "../../Source SDK/engine/server.h"

GMod_ServerToClient* g_pGMod_ServerToClient = nullptr;
bool GMod_ServerToClient::StartNetMessage(char const* NetMsgName, bool Reliable) {
	RemoveCurrentMessage();

	m_pCurrentOutGoing = new SVC_GMod_ServerToClient();
	if (!m_pCurrentOutGoing)
		return false;

	this->m_bReliable = Reliable;
	INetworkStringTable* netstringtbl = g_pInterfaces->NetworkStringTableContainer()->GetTable(NetworkstringTableID);
	if (!netstringtbl)
		return false;

	short NetworkstringID = netstringtbl->FindStringIndex(NetMsgName);
	if (NetworkstringID == INVALID_STRING_INDEX) {
		printf("couldn't find netmsg: \"%s\"!\n", NetMsgName);
		return false;
	}
	m_pCurrentOutGoing->m_DataOut.StartWriting(m_WriteBuffer, sizeof(m_WriteBuffer));
	m_pCurrentOutGoing->m_DataOut.WriteByte(0);
	m_pCurrentOutGoing->m_DataOut.WriteWord(NetworkstringID);
	return true;
}

bool GMod_ServerToClient::StartNetMessage(unsigned short NetworkstringID, bool Reliable) {
	RemoveCurrentMessage();

	m_pCurrentOutGoing = new SVC_GMod_ServerToClient();
	if (!m_pCurrentOutGoing)
		return false;

	this->m_bReliable = Reliable;

	if (NetworkstringID == INVALID_STRING_INDEX) {
		printf("invalid networkstringID : \"%i\"!\n", NetworkstringID);
		return false;
	}
	m_pCurrentOutGoing->m_DataOut.StartWriting(m_WriteBuffer, sizeof(m_WriteBuffer));
	m_pCurrentOutGoing->m_DataOut.WriteByte(0);
	m_pCurrentOutGoing->m_DataOut.WriteWord(NetworkstringID);
	return true;
}

void GMod_ServerToClient::RemoveCurrentMessage() {
	if (m_pCurrentOutGoing)
		delete m_pCurrentOutGoing;

	memset(m_WriteBuffer, 0, sizeof(m_WriteBuffer));
	m_bReliable = false;
}

bool GMod_ServerToClient::SendNetMsg(CBasePlayer* player) {
	if (!m_pCurrentOutGoing)
		return false;

	CBaseClient* client = this->FindClient(player);
	bool success = client->SendNetMsg(*m_pCurrentOutGoing,this->m_bReliable);
	this->RemoveCurrentMessage();
	return success;
}

bool GMod_ServerToClient::SendNetMsg(CBaseClient* client) {
	if (!m_pCurrentOutGoing)
		return false;

	bool success = client->SendNetMsg(*m_pCurrentOutGoing, this->m_bReliable);
	this->RemoveCurrentMessage();
	return success;
}

bool GMod_ServerToClient::SendNetMsg(CRecipientFilter& filter) {
	if (!m_pCurrentOutGoing)
		return false;

	filter.m_bReliable = this->m_bReliable;
	g_pInterfaces->GameServer()->BroadcastMessage(*m_pCurrentOutGoing, filter);
	this->RemoveCurrentMessage();
	return true;
}

bool GMod_ServerToClient::BroadcastMsg() {
	if (!m_pCurrentOutGoing)
		return false;

	CRecipientFilter filter;
	filter.AddAllPlayers();
	filter.m_bReliable = this->m_bReliable;

	g_pInterfaces->GameServer()->BroadcastMessage(*m_pCurrentOutGoing, filter);
	this->RemoveCurrentMessage();
	return true;
}

CBaseClient* GMod_ServerToClient::FindClient(int entindex) {
	for (int i = 0; i < g_pInterfaces->GameServer()->m_Clients.Count(); i++) {
		CBaseClient* client = g_pInterfaces->GameServer()->m_Clients[i];
		if (client->m_nEntityIndex != entindex)
			continue;

		return client;
	}
	return nullptr;
}

CBaseClient* GMod_ServerToClient::FindClient(CBasePlayer* player) {
	return this->FindClient(player->entindex());
}

void GMod_ServerToClient::WriteAngle(QAngle angle) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteBitAngles(angle);
}

void GMod_ServerToClient::WriteBit(BYTE val) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteOneBit(val);
}

void GMod_ServerToClient::WriteBool(bool state) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteOneBit(state);
}

void GMod_ServerToClient::WriteColor(Color color) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteByte(color[0]);
	m_pCurrentOutGoing->m_DataOut.WriteByte(color[1]);
	m_pCurrentOutGoing->m_DataOut.WriteByte(color[2]);
	m_pCurrentOutGoing->m_DataOut.WriteByte(color[3]);
}

void GMod_ServerToClient::WriteData(unsigned char* data) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteBytes(data,strlen((char*)data));
}

void GMod_ServerToClient::WriteDouble(double val) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteBits(&val, 64);
}

void GMod_ServerToClient::WriteEntity(CBaseEntity* ent) {
	if (!m_pCurrentOutGoing)
		return;

	if (!ent)
		m_pCurrentOutGoing->m_DataOut.WriteShort(0);
	else
		m_pCurrentOutGoing->m_DataOut.WriteShort(ent->entindex());
}

void GMod_ServerToClient::WriteFloat(float val) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteBits(&val, 32);
}

void GMod_ServerToClient::WriteInt(int val, int bitcount) {
	if (!m_pCurrentOutGoing || bitcount <= 0)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteSBitLong(val, bitcount);
}

void GMod_ServerToClient::WriteMatrix(VMatrix matrix) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[0][0]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[0][1]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[0][2]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[0][3]);

	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[1][0]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[1][1]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[1][2]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[1][3]);

	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[2][0]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[2][1]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[2][2]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[2][3]);

	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[3][0]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[3][1]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[3][2]);
	m_pCurrentOutGoing->m_DataOut.WriteFloat(matrix[3][3]);
}

void GMod_ServerToClient::WriteNormal(Vector val) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteBitVec3Normal(val);
}

void GMod_ServerToClient::WriteString(char const* string) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteString(string);
}

void GMod_ServerToClient::WriteUInt(unsigned int val, int bitcount) {
	if (!m_pCurrentOutGoing || bitcount <= 0)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteUBitLong(val, bitcount);
}

void GMod_ServerToClient::WriteVector(Vector val) {
	if (!m_pCurrentOutGoing)
		return;

	m_pCurrentOutGoing->m_DataOut.WriteBitVec3Coord(val);
}
