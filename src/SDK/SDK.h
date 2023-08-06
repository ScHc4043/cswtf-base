#pragma once
#include "../Memory.h"
#include "Client.h"
#include <mutex>

class CSDK
{
public:
	CMemory* Memory = new CMemory();

	//Set to nullptr so we can initialise it once we're ready
	CClient* Client = nullptr;

	CMath* Math = new CMath();
};

inline auto SDK = std::make_unique<CSDK>();
