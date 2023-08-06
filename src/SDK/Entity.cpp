#include "Entity.h"
#include "SDK.h"
#include "../Offsets.h"

CEntity::CEntity(DWORD _address)
{
	this->address = _address;
}

Vector3 CEntity::GetPosition()
{
	return SDK->Memory->Read<Vector3>(this->address + netvars::m_vecOrigin);
}

Vector3 CEntity::GetEyePosition()
{
	return this->GetPosition() + SDK->Memory->Read<Vector3>(this->address + netvars::m_vecViewOffset);
}

Vector3 CEntity::GetBonePosition(Bones Bone)
{
	Vector3 ReturnPosition = Vector3();

	DWORD BoneMatrix = this->GetBoneMatrix();

	ReturnPosition.x = SDK->Memory->Read<float>(BoneMatrix + 0x30 * Bone + 0x0C);
	ReturnPosition.y = SDK->Memory->Read<float>(BoneMatrix + 0x30 * Bone + 0x1C);
	ReturnPosition.z = SDK->Memory->Read<float>(BoneMatrix + 0x30 * Bone + 0x2C);

	return ReturnPosition;
}

Vector3 CEntity::GetVelocity()
{
	return SDK->Memory->Read<Vector3>(this->address + netvars::m_vecVelocity);
}

DWORD CEntity::GetBoneMatrix()
{
	return SDK->Memory->Read<DWORD>(this->address + netvars::m_dwBoneMatrix);
}

int CEntity::GetHealth()
{
	return SDK->Memory->Read<int>(this->address + netvars::m_iHealth);
}

int CEntity::GetShotsFired()
{
	return SDK->Memory->Read<int>(this->address + netvars::m_iShotsFired);
}

int CEntity::GetTeam()
{
	return SDK->Memory->Read<int>(this->address + netvars::m_iTeamNum);
}

int CEntity::GetObserverMode()
{
	return SDK->Memory->Read<int>(this->address + netvars::m_iObserverMode);
}

int CEntity::GetCrosshairID()
{
	return SDK->Memory->Read<int>(this->address + netvars::m_iCrosshairId);
}

bool CEntity::IsDormant()
{
	return SDK->Memory->Read<bool>(this->address + signatures::m_bDormant);
}

bool CEntity::IsLocalPlayer()
{
	return SDK->Memory->Read<bool>(this->address + signatures::m_bIsLocalPlayer);
}

bool CEntity::IsScoped()
{
	return SDK->Memory->Read<bool>(this->address + netvars::m_bIsScoped);
}

bool CEntity::IsSpotted()
{
	return SDK->Memory->Read<bool>(this->address + netvars::m_bSpotted);
}

bool CEntity::IsSpottedByMask()
{
	return SDK->Memory->Read<bool>(this->address + netvars::m_bSpottedByMask);
}

bool CEntity::IsReloading()
{
	return SDK->Memory->Read<bool>(this->address + netvars::m_bInReload);
}

bool CEntity::IsDefusing()
{
	return SDK->Memory->Read<bool>(this->address + netvars::m_bIsDefusing);
}

float CEntity::GetSpawnTime()
{
	return SDK->Memory->Read<float>(this->address + signatures::m_flSpawnTime);
}
