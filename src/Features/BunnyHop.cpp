#include "Features.h"
#include "../SDK/SDK.h"

#include <iostream>

void Features::BunnyHop()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		SDK->Client->Jump();
	}
}
