#include "no_recoil.hpp"

no_recoil::no_recoil()
{

}

bool no_recoil::toggle(bool no_recoil_state)
{
	return !no_recoil_state;
}

void no_recoil::nop_recoil_function(HANDLE hProcess)
{
	WriteProcessMemory(hProcess, (void*)(0x3003A313), &nop_function, sizeof(nop_function), nullptr);
}

void no_recoil::original_recoil_function(HANDLE hProcess)
{
	WriteProcessMemory(hProcess, (void*)(0x3003A313), &original_function, sizeof(original_function), nullptr);
}