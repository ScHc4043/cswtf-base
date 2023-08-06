#pragma once
#include <vector>
#include "Entity.h"

class CClient
{
public:
	CClient();

	DWORD GetState();

	void Attack(int SleepMS = 35), Jump(int SleepMS = 35);

	Vector3 GetViewAngles();
	void SetViewAngles(Vector3 Angles);

	CEntity GetLocalPlayer();
	std::vector<CEntity> GetEntityList(bool RemoveDead = false);
private:
	DWORD address;
};