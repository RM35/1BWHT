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
	/*the function to calc frame delay from fps cap (com_maxfps) will be rerouted to a code cave area of the exe. This new fps is set, then the original
	function points to this new fps instead of the com_maxfps value which is checked by anticheat*/

	//write our custom undetected fps (int) value to the code cave address 0x302B9690
	(WriteProcessMemory(hProcess, (void*)(0x302B9690), &fps, sizeof(fps), nullptr);
	
	//alter the opcode for mov eax,[pointer to com_maxfps] tp mov eax,[pointer to custom fps]
	WriteProcessMemory(hProcess, (void*)(0x43A4CF), &fps_bypass_opcodes, sizeof(fps_bypass_opcodes), nullptr);
}


