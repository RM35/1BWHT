#ifndef veriHEADER
#define veriHEADER

#include <windows.h>
#include "proc.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

//Over 40 hours of attempts to hook the correct function. Learned alot. Main tools: Cheat Engine, Snowman Decompiler, ilspy, compiler explorer.
//Hooked function is an error logging function that is called before the main opengl swap buffers therefore hack can turn off before screenshot is loaded
//for image processing.

class veritas_hook
{
public:
	BYTE hook_opcodes[9] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	BYTE loop_opcodes[40] = { 0xC7, 0x05, 0xB2, 0x1D, 0xAE, 0x00, 0x01, 0x00, 0x00, 0x00, 
		0xA1, 0xB2, 0x1D, 0xAE, 0x00, 0x83, 0xF8, 0x01, 0x90, 0x90, 0x90, 0x90, 0x75, 0x02,
		0xEB, 0xF0, 0x55, 0x8B, 0xEC, 0x81, 0xEC, 0x08, 0x05, 0x00, 0x00, 0xE9, 0x90, 0x90, 
		0x90, 0x90 };
	
	//Hardcoded addresses as codmp.exe is assumed to always have 0x400000 base address
	uintptr_t loop_addr = 0xAE1D6F;
	uintptr_t loop_flag_offset = 0x6E1DB2;

	//Hooked function = vstcommon.dll+4220
	uintptr_t hooked_func_offset = 0x4220;

	veritas_hook();
	bool toggle(bool veritas_hook_state);
	std::vector<unsigned char> int_to_bytes(int pint);
	void build_byte_arrays(uintptr_t vstdll_base);
	int inject_hook(DWORD procId, HANDLE hProcess);
	bool turn_off_hacks(HANDLE hProcess);
	void reset_flag(HANDLE hProcess);
};

#endif