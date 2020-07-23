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
#include "dotnet_random.hpp"
#include "veritas_hook.hpp"


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
		bool veritas_hook = true;
	} cfg;

	struct state
	{
		bool wall_hack_state = false;
		bool trigger_bot_state = false;
		bool fast_run_state = false;
		bool no_recoil_state = false;
		bool aimbot = false;
		int fps_bypass_state = 0;
		bool veritas_hook_state = false;
	} state;
	
	wall_hack wh;
	trigger_bot tbot;
	fast_run f_run;
	no_recoil n_recoil;
	aimbot aim_b;
	fps_bypass fps_b;
	veritas_hook veri;

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
			switch (state.fps_bypass_state)
			{
			case 0:
				fps_b.set_fps_bypassed(hProcess, 250);
				break;
			case 1:
				fps_b.set_fps_bypassed(hProcess, 333);
				break;
			case 2:
				fps_b.set_fps_bypassed(hProcess, 600);
				break;
			}
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_NUMPAD7) && cfg.veritas_hook)
		{
			state.veritas_hook_state = veri.toggle(state.veritas_hook_state);
			veri.inject_hook(procId, hProcess);
			Sleep(200);
		}

		//update_console(state.wall_hack_state, state.trigger_bot_state, state.fast_run_state, state.no_recoil_state, state.aimbot, state.fps_bypass_state);

		if (state.trigger_bot_state && cfg.trigger_bot)
		{
			if (tbot.on_target_check(hProcess))
			{
				tbot.shoot_gun(50, hProcess);
			}
		}

		while (GetAsyncKeyState(VK_SHIFT) && state.fast_run_state)
		{
			f_run.do_fast_run_macro(6, 230);
		}

		while (GetAsyncKeyState(VK_SPACE) && state.fast_run_state)
		{
			f_run.do_test(50);
		}
		
		if (state.no_recoil_state && cfg.no_recoil)
		{
			n_recoil.nop_recoil_function(hProcess);
		}
		else if (!state.no_recoil_state && cfg.no_recoil) 
		{
			n_recoil.original_recoil_function(hProcess);
		}

		//aim_b.update_values(hProcess);
		//aim_b.print_player_client_no();
		//aim_b.print_client_info(0);
		//aim_b.print_client_info(1);
		//aim_b.print_client_info(3);
		//aim_b.print_client_info(4);
		//aim_b.print_client_info(5);
		//aim_b.print_client_info(6);
		//aim_b.print_client_info(7);
		//aim_b.print_client_info(8);
	}
}
