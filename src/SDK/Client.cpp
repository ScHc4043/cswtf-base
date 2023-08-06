#include "Client.h"
#include "SDK.h"
#include "../Offsets.h"

CClient::CClient()
{
	this->address = SDK->Memory->Read<DWORD>(SDK->Memory->EngineBase + signatures::dwClientState);
}

DWORD CClient::GetState()
{
	return SDK->Memory->Read<DWORD>(this->address + signatures::dwClientState_State);
}

void CClient::Jump(int SleepMS)
{
	SDK->Memory->Write<int>(SDK->Memory->ClientBase + signatures::dwForceJump, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(SleepMS));
	SDK->Memory->Write<int>(SDK->Memory->ClientBase + signatures::dwForceJump, 0);
}

void CClient::Attack(int SleepMS)
{
	SDK->Memory->Write<int>(SDK->Memory->ClientBase + signatures::dwForceAttack, 5);
	std::this_thread::sleep_for(std::chrono::milliseconds(SleepMS));
	SDK->Memory->Write<int>(SDK->Memory->ClientBase + signatures::dwForceAttack, 4);
}

Vector3 CClient::GetViewAngles()
{
	return SDK->Memory->Read<Vector3>(this->address + signatures::dwClientState_ViewAngles);
}

void CClient::SetViewAngles(Vector3 Angles)
{
	SDK->Memory->Write<Vector3>(this->address + signatures::dwClientState_ViewAngles, Angles);
}

CEntity CClient::GetLocalPlayer()
{
	DWORD Address = SDK->Memory->Read<DWORD>(SDK->Memory->ClientBase + signatures::dwLocalPlayer);
	return CEntity(Address);
}

std::vector<CEntity> CClient::GetEntityList(bool RemoveDead)
{
	std::vector<CEntity> ReturnList;

	DWORD EntityList = SDK->Memory->Read<DWORD>(SDK->Memory->ClientBase + signatures::dwEntityList);

	for (int i = 0; i <= 64; i++)
	{
		DWORD CurrentEntityAddress = SDK->Memory->Read<DWORD>(EntityList + (i * 0x10));
		CEntity Entity = CEntity(CurrentEntityAddress);

		if (RemoveDead && Entity.GetHealth() <= 0) continue;

		ReturnList.push_back(Entity);
	}

	return ReturnList;
}
