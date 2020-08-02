#include "fast_run.hpp"

fast_run::fast_run() 
{
	kb_input.type = INPUT_KEYBOARD;
}

bool fast_run::toggle(bool fast_run_state)
{
	return !fast_run_state;
}

void fast_run::do_fast_run_macro(int delay, float speed_cap)
{
	kb_input.ki.time = 0;
	kb_input.ki.wVk = 0;
	kb_input.ki.dwExtraInfo = 0;
	kb_input.ki.dwFlags = KEYEVENTF_SCANCODE;
	kb_input.ki.wScan = 0x1E;
	SendInput(1, &kb_input, sizeof(INPUT));
	kb_input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	Sleep(delay);
	SendInput(1, &kb_input, sizeof(INPUT));
	kb_input.ki.dwFlags = KEYEVENTF_SCANCODE;
	kb_input.ki.wScan = 0x20;
	SendInput(1, &kb_input, sizeof(INPUT));
	kb_input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	Sleep(delay);
	SendInput(1, &kb_input, sizeof(INPUT));
}
