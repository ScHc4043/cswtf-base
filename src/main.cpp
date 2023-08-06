// IOStream needed for input and output
#include <iostream>

//Thread to sleep our thread and chrono to specify the timeframe of the sleep
#include <thread>
#include <chrono>

//Including our SDK and Features
#include "SDK/SDK.h"
#include "Features/Features.h"

int main()
{
	//Set text color to red
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	std::cout << "\n  [+] Welcome To 'cswtf-base'.\n";

	//If it can attach to process 'csgo.exe' then we can proceed
	if (SDK->Memory->AttachToProcess("csgo.exe"))
	{
		//Print Process ID
		std::cout << "\n  [+] Process ID: " << SDK->Memory->ProcessID;

		//Get base addresses for 'client.dll' and 'engine.dll'
		SDK->Memory->ClientBase = SDK->Memory->GetModuleBase("client.dll");
		SDK->Memory->EngineBase = SDK->Memory->GetModuleBase("engine.dll");

		//Printing these base addresses
		std::cout << "\n  [+] 'client.dll' Base Address: 0x" << SDK->Memory->ClientBase << ".";
		std::cout << "\n  [+] 'engine.dll' Base Address: 0x" << SDK->Memory->EngineBase << ".\n";

		//Initialising Client in SDK
		SDK->Client = new CClient();

		//Our game loop
		while (true)
		{
			//Sleeping the thread for 1ms so that we don't use too much cpu power without need to
			std::this_thread::sleep_for(std::chrono::milliseconds(1));			

			//Sanity check to see if we're in game (state 6 = in game)
			if (SDK->Client->GetState() != 6) continue;

			//Call our module functions
			Features::BunnyHop();
		}
	}
	else
	{
		//Catching the error of not being able to attach with a message
		std::cout << "\n  [!] Could Not Attach To 'csgo.exe'.\n";
	}

	//Program End
	return 0;
}
