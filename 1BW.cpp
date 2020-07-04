#include <iostream>
#include <Windows.h>
#include "proc.hpp"
#include "wall_hack.hpp"

int main()
{
	DWORD procId = GetProcId(L"CoDMP.exe");
	uintptr_t moduleBase = GetmoduleBaseAddress(procId, L"cgame_mp_x86.dll");
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	bool wall_hack_state = false;
	wall_hack wh;
	bool trigger_bot_state = false;
	int straight_value = 0;
	INPUT straight;

	straight.type = INPUT_MOUSE;
	straight.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN);

	for (;; Sleep(10))
	{
		if (GetAsyncKeyState(VK_XBUTTON1))
		{
			wall_hack_state = wh.toggle(wall_hack_state, hProcess);
		}
		if (GetAsyncKeyState(VK_XBUTTON2))
		{
			if (trigger_bot_state == false)
			{
				trigger_bot_state = true;
			}
			else
			{
				trigger_bot_state = false;
			}
			std::cout << "straight on? : " << trigger_bot_state << std::endl;
		}
		
		if (trigger_bot_state)
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
