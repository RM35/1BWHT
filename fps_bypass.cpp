#include "fps_bypass.hpp"
#include <iostream>

fps_bypass::fps_bypass()
{

}

int fps_bypass::change_state(int fps_bypass_state)
{
	switch (fps_bypass_state)
	{
		case 2: return 0;
		case 0: return 1;
		case 1: return 2;
	}
	
}

void fps_bypass::set_frame_delay(HANDLE hProcess, int frame_delay_ms)
{
	WriteProcessMemory(hProcess, (void*)(0x0249BC88), &frame_delay_ms, 4, nullptr);	
}