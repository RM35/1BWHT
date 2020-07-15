#include <iostream>
#include <thread>
#include <Windows.h>
#include "proc.hpp"
#include "wall_hack.hpp"
#include "trigger_bot.hpp"
#include "fast_run.hpp"
#include "no_recoil.hpp"
#include "aimbot.hpp"
#include "utils.hpp"
#include "fps_bypass.hpp"


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
		bool aimbot = true;
		bool fps_bypass = true;
	} cfg;

	struct state
	{
		bool wall_hack_state = false;
		bool trigger_bot_state = false;
		bool fast_run_state = false;
		bool no_recoil_state = false;
		bool aimbot = false;
		int fps_bypass_state = 0;
	} state;
	
	wall_hack wh;
	trigger_bot tbot;
	fast_run f_run;
	no_recoil n_recoil;
	aimbot aim_b;
	fps_bypass fps_b;

	for (;; Sleep(1))
	{
		//Toggles
		if (GetAsyncKeyState(VK_NUMPAD1) && cfg.wall_hack)
		{
			state.wall_hack_state = wh.toggle(state.wall_hack_state, hProcess);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) && cfg.trigger_bot)
		{
			state.trigger_bot_state = tbot.toggle(state.trigger_bot_state);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD3) && cfg.fast_run)
		{
			state.fast_run_state = f_run.toggle(state.fast_run_state);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD4) && cfg.no_recoil)
		{
			state.no_recoil_state = n_recoil.toggle(state.no_recoil_state);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD5) && cfg.aimbot)
		{
			state.aimbot = aim_b.toggle(state.aimbot);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD6) && cfg.fps_bypass)
		{
			state.fps_bypass_state = fps_b.change_state(state.fps_bypass_state);
			std::cout << "fps changed" << std::endl;
			Sleep(200);
		}

		update_console(state.wall_hack_state, state.trigger_bot_state, state.fast_run_state, state.no_recoil_state, state.aimbot, state.fps_bypass_state);

		if (state.trigger_bot_state && cfg.trigger_bot)
		{
			if (tbot.on_target_check(hProcess))
			{
				tbot.shoot_gun(50, hProcess);
			}
		}

		while (GetAsyncKeyState(VK_SHIFT) && state.fast_run_state)
		{
			f_run.do_fast_run_macro(50, 230);
		}

		if (state.no_recoil_state && cfg.no_recoil)
		{
			n_recoil.nop_recoil_function(hProcess);
		}
		else if (!state.no_recoil_state && cfg.no_recoil) 
		{
			n_recoil.original_recoil_function(hProcess);
		}

		if (!state.fps_bypass_state == 0) //checks again inside the func. Unessessary but leaving it in
		{
			int frame_delay_ms = 4;

			switch (state.fps_bypass_state)
			{
			case 1:
				frame_delay_ms = 3;
				break;
			case 2:
				frame_delay_ms = 2;
				break;
			}
			fps_b.set_frame_delay(hProcess, frame_delay_ms);
		}
	}
}
