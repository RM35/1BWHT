#include "trigger_bot.hpp"

trigger_bot::trigger_bot()
{
	mouse_input.type = INPUT_MOUSE;
}

bool trigger_bot::toggle(bool trigger_bot_state)
{
	if (trigger_bot_state == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool trigger_bot::on_target_check(HANDLE hProcess)
{
	int on_target_value = 0;

	ReadProcessMemory(hProcess, (int*)0x301E6038, &on_target_value, sizeof(on_target_value), nullptr);

	if (on_target_value == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void trigger_bot::shoot_gun(int delay, HANDLE hProcess)
{
	float ads = 1;

	mouse_input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN);

	WriteProcessMemory(hProcess, (float*)(0x301F87D4), &ads, sizeof(ads), nullptr);

	SendInput(1, &mouse_input, sizeof(INPUT));
	ZeroMemory(&mouse_input, sizeof(mouse_input));
	mouse_input.mi.dwFlags = (MOUSEEVENTF_LEFTUP);
	SendInput(1, &mouse_input, sizeof(INPUT));
	Sleep(delay);
}