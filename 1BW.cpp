#include <iostream>
#include <Windows.h>
#include "proc.hpp"

int main()
{
	//Get ProcId of process
	DWORD procId = GetProcId(L"CoDMP.exe");
	std::cout << "Process ID: " << procId << std::endl;

	//Get Base address
	uintptr_t moduleBase = GetmoduleBaseAddress(procId, L"cgame_mp_x86.dll");

	//get process handle
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	bool noodle = false;
	bool straight_noodle = false;
	int straight_value = 0;
	INPUT straight;

	straight.type = INPUT_MOUSE;
	straight.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN);

	for (;; Sleep(10))
	{
		if (GetAsyncKeyState(VK_XBUTTON1))
		{
			if (noodle == FALSE)
			{
				WriteProcessMemory(hProcess, (void*)(0x300296B7), (PBYTE)"\x88", 2, 0);
				noodle = TRUE;
			}
			else
			{
				WriteProcessMemory(hProcess, (void*)(0x300296B7), (PBYTE)"\x80", 2, 0);
				noodle = FALSE;
			}
			std::cout << "1BW on? : " << noodle << std::endl;
		}
		if (GetAsyncKeyState(VK_XBUTTON2))
		{
			if (straight_noodle == FALSE)
			{
				straight_noodle = TRUE;
			}
			else
			{
				straight_noodle = FALSE;
			}
			std::cout << "straight on? : " << straight_noodle << std::endl;
		}
		
		if (straight_noodle)
		{
			ReadProcessMemory(hProcess, (int*)0x301E6038, &straight_value, sizeof(straight_value), nullptr);

			if (straight_value != 0)
			{
				straight.type = INPUT_MOUSE;
				straight.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN);
				SendInput(1, &straight, sizeof(INPUT));
				ZeroMemory(&straight, sizeof(straight));
				straight.type = INPUT_MOUSE;
				straight.mi.dwFlags = (MOUSEEVENTF_LEFTUP);
				SendInput(1, &straight, sizeof(INPUT));
				Sleep(50);
			}
		}
	}
}
