#ifndef no_recoilHEADER
#define no_recoilHEADER

#include <windows.h>

class no_recoil
{
public:

	BYTE nop_function[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
	BYTE original_function[5] = { 0xE8, 0x68, 0x9F, 0xFD, 0xFF };

	no_recoil();
	bool toggle(bool no_recoil_state);
	void nop_recoil_function(HANDLE hProcess);
	void original_recoil_function(HANDLE hProcess);
};

#endif