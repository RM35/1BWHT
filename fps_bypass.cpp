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

void fps_bypass::set_fps_bypassed(HANDLE hProcess, int fps)
{
	if (WriteProcessMemory(hProcess, (void*)(0x00AE1D6C), &fps, sizeof(fps), nullptr) == 0)
	{
		std::cout << "Windows " << GetLastError() << std::endl;
	}

	WriteProcessMemory(hProcess, (void*)(0x0043A4CF), &fps_bypass_opcodes, sizeof(fps_bypass_opcodes), nullptr);
} 
