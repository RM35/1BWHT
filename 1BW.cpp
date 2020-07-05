#include <iostream>
#include <Windows.h>
#include "proc.hpp"
#include "wall_hack.hpp"
#include "trigger_bot.hpp"

int main()
{
	DWORD procId = GetProcId(L"CoDMP.exe");
	uintptr_t moduleBase = GetmoduleBaseAddress(procId, L"cgame_mp_x86.dll");
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	bool wall_hack_state = false;
	wall_hack wh;

	bool trigger_bot_state = false;
	trigger_bot tbot;

	//Main Loop
	for (;; Sleep(10))
	{
		if (GetAsyncKeyState(VK_XBUTTON1))
		{
			wall_hack_state = wh.toggle(wall_hack_state, hProcess);
			std::cout << "Wall hack toggled to state: " << wall_hack_state << std::endl;
			Sleep(200);
		}
		if (GetAsyncKeyState(VK_XBUTTON2))
		{
			trigger_bot_state = tbot.toggle(trigger_bot_state);
			std::cout << "Trigger Bot toggled to state: " << trigger_bot_state << std::endl;
			Sleep(200);
		}
		if (trigger_bot_state)
		{
			if (tbot.on_target_check(hProcess))
			{
				tbot.shoot_gun(50);
				std::cout << "Trigger bot has shot at target" << std::endl;
			}
		}
	}
}
