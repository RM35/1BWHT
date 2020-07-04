#include "wall_hack.hpp"

bool wall_hack::toggle(bool wall_hack_state, HANDLE hProcess)
{
	if (wall_hack_state == false)
	{
		WriteProcessMemory(hProcess, (void*)(0x300296B7), (PBYTE)"\x88", 2, 0);
		return true;
	}
	else
	{
		WriteProcessMemory(hProcess, (void*)(0x300296B7), (PBYTE)"\x80", 2, 0);
		return false;
	}
}