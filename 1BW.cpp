#include <iostream>
#include <Windows.h>
#include "proc.hpp"
#include "wall_hack.hpp"
#include "trigger_bot.hpp"
#include "fast_run.hpp"
#include "no_recoil.hpp"
#include "utils.hpp"

int main()
{
	DWORD procId = GetProcId(L"CoDMP.exe");
	uintptr_t moduleBase = GetmoduleBaseAddress(procId, L"cgame_mp_x86.dll");
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	struct config
	{
		bool wall_hack = true;
		bool trigger_bot = true;
		bool fast_run = true;
		bool no_recoil = true;
	} cfg;

	struct state
	{
		bool wall_hack_state = false;
		bool trigger_bot_state = false;
		bool fast_run_state = false;
		bool no_recoil_state = false;
	} state;
	
	wall_hack wh;
	trigger_bot tbot;
	fast_run f_run;
	no_recoil n_recoil;

	for (;; Sleep(1))
	{

		if (GetAsyncKeyState(VK_NUMPAD1) && cfg.wall_hack)
		{
			state.wall_hack_state = wh.toggle(state.wall_hack_state, hProcess);
			update_console(state.wall_hack_state, state.trigger_bot_state, state.fast_run_state, state.no_recoil_state);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) && cfg.trigger_bot)
		{
			state.trigger_bot_state = tbot.toggle(state.trigger_bot_state);
			update_console(state.wall_hack_state, state.trigger_bot_state, state.fast_run_state, state.no_recoil_state);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD3) && cfg.fast_run)
		{
			state.fast_run_state = f_run.toggle(state.fast_run_state);
			update_console(state.wall_hack_state, state.trigger_bot_state, state.fast_run_state, state.no_recoil_state);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD4) && cfg.no_recoil)
		{
			state.no_recoil_state = n_recoil.toggle(state.no_recoil_state);
			update_console(state.wall_hack_state, state.trigger_bot_state, state.fast_run_state, state.no_recoil_state);
			Sleep(200);
		}

		if (state.trigger_bot_state && cfg.trigger_bot)
		{
			if (tbot.on_target_check(hProcess))
			{
				tbot.shoot_gun(1500, hProcess);
				//std::cout << "Trigger bot has shot at target" << std::endl;
			}
		}

		while (GetAsyncKeyState(VK_SHIFT) && state.fast_run_state)
		{
			f_run.do_fast_run_macro(20);
		}
	}
}
