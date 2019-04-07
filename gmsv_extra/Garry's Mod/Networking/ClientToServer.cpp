#include "ClientToServer.h"
#include "../../interfaces.h"
GMod_NetReceive* g_pGModNetMsgReceiver = nullptr;
GMod_NetReceive::GMod_NetReceive() {
	Receivers = new CUtlVector<GModNetMsgReceive_t>;
}
GMod_NetReceive::~GMod_NetReceive() {
	if (Receivers) {
		Receivers->~CUtlVector();
	}
}
void GMod_NetReceive::AddReceiver(char const* NetMsgName, GModNetMsgReceiveCallBackFn fn, bool CreateNewString) {
	if (!NetMsgName || !fn)
		return;

	INetworkStringTable* networkstringtbl = g_pInterfaces->NetworkStringTableContainer()->FindTable("networkstring");
	if (!networkstringtbl)
		return;

	unsigned short index = networkstringtbl->FindStringIndex(NetMsgName);
	if (index == INVALID_STRING_INDEX && CreateNewString) {
		index = networkstringtbl->AddString(1, NetMsgName);
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
	length = length - 8;
	if (length < 8 || Type >= 5) {
		printf("Blocking invalid GMod packet - Length: %i Type: %i\n", length, Type);
		return;
	}
	else if (Type == 0) {
		this->FillData(dunno, pPlayer, data, length);
		short NetworkStringID = data->ReadShort();
		char const* netnsgname = g_pInterfaces->NetworkStringTableContainer()->FindTable("networkstring")->GetString(NetworkStringID);
		this->CallReceivers(pPlayer, NetworkStringID);
	}
	data->m_iCurBit = SaveCurBit;
	this->ResetData();
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
		CurrentData.m_pData->m_iCurBit = SaveCurBit;
	}
}