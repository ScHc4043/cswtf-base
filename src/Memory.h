#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class CMemory
{
public:
	DWORD ProcessID = NULL,
		ClientBase = NULL,
		EngineBase = NULL;

	HANDLE ProcessHandle = NULL;

	//Function to write process memory (uses templates to specify what datatype)
	template <class T>
	void Write(DWORD Address, T Value)
	{
		WriteProcessMemory(ProcessHandle, (LPVOID)Address, &Value, sizeof(T), NULL);
	}

	//Function to read process memory (uses templates to specify what datatype)
	template <class T>
	T Read(DWORD Address)
	{
		T Buffer;

		ReadProcessMemory(ProcessHandle, (LPVOID)Address, &Buffer, sizeof(T), NULL);

		return Buffer;
	}

	//How we get access to read and write memory (PROCESS_ALL_ACCESS allows for both r/w permissions)
	bool AttachToProcess(const char* ProcessName)
	{
		//Get process snapshot
		HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		//Check if its null
		if (hProcessSnapshot == INVALID_HANDLE_VALUE)
			return false;

		//PROCESSENTRY32 contains info on the process it is allocated to (for now the first one)
		PROCESSENTRY32 ProcessEntry = PROCESSENTRY32();

		//Allocating dwSize the size of the structure
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		
		//Loop through process list (referencing the address of ProcessEntry so it can set it to the next)
		//Also references hProcessSnapshot (contains the processes) and sets ProcessEntry to the next
		while (Process32Next(hProcessSnapshot, &ProcessEntry))
		{
			//We are checking if current process name in the snapshot is equal to the name we want
			//Strcmp returns 0 if the 2 given texts match up
			if (!strcmp(ProcessName, reinterpret_cast<const char*>(ProcessEntry.szExeFile)))
			{
				//Set this class's process id to the one of the current process
				ProcessID = ProcessEntry.th32ProcessID;

				//Open our handle with all access
				ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);

				//Sanity check to see if hanlde is null
				if (!ProcessHandle)
					return false;

				//Close the handle and return true (so we dont loop through the rest of process list and waste cpu power)
				CloseHandle(hProcessSnapshot);
				return true;
			}
		}

		//Close handle, nothing was found so return false
		CloseHandle(hProcessSnapshot);
		return false;
	}

	//How we get base addresses to the modules we want ('client.dll' and 'engine.dll')
	DWORD GetModuleBase(const char* ModuleName)
	{
		//Get snapshot of the process modules (we have the process id from the attachtoprocess function)
		HANDLE hModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);

		//Check if snapshot is null
		if (hModuleSnapshot == INVALID_HANDLE_VALUE)
			return NULL;

		//MODULEENTRY32 contains info on the module
		MODULEENTRY32 moduleEntry;

		//Allocating dwSize the size of the structure (yes i used the same comment from above :sob:)
		moduleEntry.dwSize = sizeof(MODULEENTRY32);

		//Loop through the module list
		while (Module32Next(hModuleSnapshot, &moduleEntry))
		{
			//Check if the current module name is equal; to the one we want
			if (!strcmp(ModuleName, reinterpret_cast<const char*>(moduleEntry.szModule)))
			{
				//Close the handle and return the base address of that module
				CloseHandle(hModuleSnapshot);
				return reinterpret_cast<DWORD>(moduleEntry.modBaseAddr);
			}
		}

		//Close handle and return null (we didnt find that module)
		CloseHandle(hModuleSnapshot);
		return NULL;
	}
};
