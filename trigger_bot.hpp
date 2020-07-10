#ifndef tbHEADER
#define tbHEADER

#include <windows.h>

class trigger_bot
{
public:
	INPUT mouse_input;

	trigger_bot();
	bool toggle(bool trigger_bot_state);
	bool on_target_check(HANDLE hProcess);
	void shoot_gun(int delay, HANDLE);
};

#endif