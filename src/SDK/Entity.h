#pragma once
#include <Windows.h>
#include "Math.h"

enum Bones
{
	Chest = 6,
	Neck = 7,
	Head = 8,
};

class CEntity
{
public:
	CEntity(DWORD _address);

	Vector3 GetPosition(), GetEyePosition(), GetBonePosition(Bones Bone), GetVelocity();

	DWORD GetBoneMatrix();

	int GetHealth(), GetShotsFired(), GetTeam(), GetObserverMode(), GetCrosshairID();

	bool IsDormant(), IsLocalPlayer(), IsScoped(), IsSpotted(), IsSpottedByMask(),
		IsReloading(), IsDefusing();

	float GetSpawnTime();

private:
	DWORD address;
};
