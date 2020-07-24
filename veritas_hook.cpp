#include "veritas_hook.hpp"

veritas_hook::veritas_hook()
{

}

bool veritas_hook::toggle(bool veritas_hook_state)
{
	return !veritas_hook_state;
}

std::vector<BYTE> veritas_hook::int_to_bytes(int pint)
{
	std::vector<BYTE> arrayOfByte(4);
	for (int i = 0; i < 4; i++)
		arrayOfByte[3 - i] = (pint >> (i * 8));
	return arrayOfByte;
}

void veritas_hook::build_byte_arrays(uintptr_t make_ss_addr)
{
	intptr_t rel_offset_to_loop = 0xFFFFFFFF - (make_ss_addr - hook_loop_addr + 0x4);
	std::vector<BYTE> rel_to_loop_bytes = int_to_bytes((int)rel_offset_to_loop);
	hook_opcodes[1] = rel_to_loop_bytes[3];
	hook_opcodes[2] = rel_to_loop_bytes[2];
	hook_opcodes[3] = rel_to_loop_bytes[1];
	hook_opcodes[4] = rel_to_loop_bytes[0];

	uintptr_t rel_offset_to_hook = (make_ss_addr + 0x9) - (hook_loop_addr + 0x28);
	std::vector<BYTE> rel_to_hook_bytes = int_to_bytes((int)rel_offset_to_hook);
	loop_opcodes[36] = rel_to_hook_bytes[3];
	loop_opcodes[37] = rel_to_hook_bytes[2];
	loop_opcodes[38] = rel_to_hook_bytes[1];
	loop_opcodes[39] = rel_to_hook_bytes[0];

	std::cout << "Opcode arrays have been built and ready for injection" << std::endl;
 }

int veritas_hook::inject_hook(DWORD procId, HANDLE hProcess)
{
	uintptr_t vstdll_base = GetmoduleBaseAddress(procId, L"vstdll.dll");
	std::cout << "Trying to get vstdll.dll address " << std::endl;
	if (!vstdll_base == 0)
	{
		uintptr_t make_ss_addr = vstdll_base + 0x3340;
		std::cout << "Veritas module detected successfully at: " << std::hex << vstdll_base << std::endl;
		BYTE read_bytes[3] = { 0x90, 0x90, 0x90 };
		BYTE ss_func_bytes[3] = { 0x89, 0x45, 0xFC };
		if (!ReadProcessMemory(hProcess, (BYTE*)vstdll_base + 0x3350, &read_bytes, sizeof(read_bytes), nullptr) == 0)
		{
			if (read_bytes[0] == ss_func_bytes[0] && read_bytes[2] == ss_func_bytes[2])
			{
				std::cout << "Veritas screenshot function located successfull" << std::endl;
				build_byte_arrays(make_ss_addr);
				WriteProcessMemory(hProcess, (void*)(hook_loop_addr), &loop_opcodes, sizeof(loop_opcodes), nullptr);
				std::cout << "Hook loop has been written to codmp.exe" << std::endl;
				WriteProcessMemory(hProcess, (void*)(make_ss_addr), &hook_opcodes, sizeof(hook_opcodes), nullptr);
				std::cout << "Hook has been written to vstdll.dll" << std::endl;
			}
		}
	}
	return 0;
}

bool veritas_hook::turn_off_hacks(HANDLE hProcess)
{
	int inject_loop_flag = 0;
	ReadProcessMemory(hProcess, (int*)0xAE1DB2, &inject_loop_flag, sizeof(inject_loop_flag), nullptr);
	if (inject_loop_flag == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void veritas_hook::reset_flag(HANDLE hProcess)
{
	int inject_loop_flag = 0;
	WriteProcessMemory(hProcess, (int*)0xAE1DB2, &inject_loop_flag, sizeof(inject_loop_flag), nullptr);
}