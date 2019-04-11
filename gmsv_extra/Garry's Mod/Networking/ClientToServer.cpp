#include "ClientToServer.h"
#include "gmod_net_util.h"
#include "../../interfaces.h"
#include "../../Source SDK/eiface.h"
GMod_NetReceive* g_pGModNetMsgReceiver = nullptr;
GMod_NetReceive::GMod_NetReceive() {
	Receivers = new CUtlVector<GModNetMsgReceive_t>;
	ReadStrings = new CUtlVector<char*>;
}
GMod_NetReceive::~GMod_NetReceive() {
	if (Receivers) {
		Receivers->~CUtlVector();
	}
	if (ReadStrings) {
		ReadStrings->~CUtlVector();
	}
}
void GMod_NetReceive::AddReceiver(char const* NetMsgName, GModNetMsgReceiveCallBackFn fn, bool CreateNewString) {
	if (!NetMsgName || !fn)
		return;

	INetworkStringTable* networkstringtbl = g_pInterfaces->NetworkStringTableContainer()->GetTable(NetworkstringTableID);
	if (!networkstringtbl)
		return;

	unsigned short index = networkstringtbl->FindStringIndex(NetMsgName);
	if (index == INVALID_STRING_INDEX && CreateNewString) {
		index = networkstringtbl->AddString(true, NetMsgName);
	}
	else if (index == INVALID_STRING_INDEX && !CreateNewString)
		return;

	Receivers->AddToTail(GModNetMsgReceive_t{NetMsgName, index, fn});
}

void GMod_NetReceive::ProcessNetMsg(int dunno, edict_t* pPlayer, bf_read* data, int length) {
	this->ResetData();
	if (!data || !pPlayer)
		return;

	int SaveCurBit = data->m_iCurBit;

	BYTE Type = data->ReadByte();
	length -= 8;
	if (length < 8 || Type >= 5) {
		printf("Blocking invalid GMod packet - Length: %i Type: %i\n", length, Type);
		return;
	}
	else if (Type == 0) {
		short NetworkStringID = data->ReadShort();
		length -= 16;
		this->FillData(dunno, pPlayer, data, length);
		this->CallReceivers(pPlayer, NetworkStringID);
	}
	data->m_iCurBit = SaveCurBit;
	this->ResetData();
	this->DeleteReadStrings();
}
void GMod_NetReceive::CallReceivers(edict_t* pPlayer, unsigned int NetworkID) {
	if (!CurrentData.m_pData)
		return;

	int SaveCurBit = CurrentData.m_pData->m_iCurBit;

	for (int i = 0; i < Receivers->Size(); i++) {
		GModNetMsgReceive_t element = Receivers->Element(i);
		if (element.m_NetworkID != NetworkID || element.m_CallBackFn == nullptr)
			continue;

		element.m_CallBackFn(pPlayer);
		this->DeleteReadStrings();
		CurrentData.m_pData->m_iCurBit = SaveCurBit;
	}
}
void GMod_NetReceive::AddString(char* str) {
	ReadStrings->AddToTail(str);
}
void GMod_NetReceive::DeleteReadStrings() {
	for (int i = 0; i < ReadStrings->Size(); i++) {
		char* str = ReadStrings->Element(i);
		if (str)	
			delete[] str;									
	}
	ReadStrings->RemoveAll();
}

BYTE GMod_NetReceive::ReadByte() {
	if (!this->CurrentData.m_pData)
		return 0;

	return this->CurrentData.m_pData->ReadByte();
}

char* GMod_NetReceive::ReadString() {
	if (!this->CurrentData.m_pData)
		return this->nullstr;

	if (this->CurrentData.m_pData->ReadString(NetMsgStringBuffer, 0xFFFD)) {
		int len = V_strlen(NetMsgStringBuffer) + 1;
		char* out = new char[len];
		V_strncpy(out, NetMsgStringBuffer, len);
		AddString(out);
		return out;
	}

	return this->nullstr;
}

Vector GMod_NetReceive::ReadVector() {
	if (!this->CurrentData.m_pData)
		return vec3_origin;

	Vector out(0, 0, 0);

	this->CurrentData.m_pData->ReadBitVec3Coord(out);
	return out;
}

QAngle GMod_NetReceive::ReadAngle() {
	if (!this->CurrentData.m_pData)
		return vec3_angle;

	QAngle out(0, 0, 0);

	this->CurrentData.m_pData->ReadBitAngles(out);

	return out;
}

BYTE GMod_NetReceive::ReadBit() {
	if (!this->CurrentData.m_pData)
		return 0;

	return this->CurrentData.m_pData->ReadOneBit();
}

double GMod_NetReceive::ReadDouble() {
	if (!this->CurrentData.m_pData)
		return 0.0;

	double out;
	this->CurrentData.m_pData->ReadBits(&out, 64);
	return out;
}

Color GMod_NetReceive::ReadColor() {
	if (!this->CurrentData.m_pData)
		return Color(0,0,0,0);

	BYTE R = this->ReadByte();
	BYTE G = this->ReadByte();
	BYTE B = this->ReadByte();
	BYTE A = this->ReadByte();
	return Color(R,G,B,A);
}

int GMod_NetReceive::ReadInt(int bitcount) {
	if (!this->CurrentData.m_pData)
		return 0;

	return this->CurrentData.m_pData->ReadUBitLong(bitcount);
}

CBaseEntity* GMod_NetReceive::ReadEntity() {
	if (!this->CurrentData.m_pData)
		return nullptr;

	short index = net_ReadInt(16);

	edict_t* edict = g_pInterfaces->EngineServer()->PEntityOfEntIndex(index);
	if (!edict)
		return nullptr;

	return (CBaseEntity*)edict->GetUnknown();
}