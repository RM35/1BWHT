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

void veritas_hook::build_byte_arrays(uintptr_t func_to_hook_addr)
{
	intptr_t rel_offset_to_loop = 0xFFFFFFFF - (func_to_hook_addr - loop_addr + 0x4);
	std::vector<BYTE> rel_to_loop_bytes = int_to_bytes((int)rel_offset_to_loop);
	hook_opcodes[1] = rel_to_loop_bytes[3];
	hook_opcodes[2] = rel_to_loop_bytes[2];
	hook_opcodes[3] = rel_to_loop_bytes[1];
	hook_opcodes[4] = rel_to_loop_bytes[0];

	uintptr_t rel_offset_to_hook = (func_to_hook_addr + 0x10) - (loop_addr + 0x32);
	std::vector<BYTE> rel_to_hook_bytes = int_to_bytes((int)rel_offset_to_hook);
	loop_opcodes[36] = rel_to_hook_bytes[3];
	loop_opcodes[37] = rel_to_hook_bytes[2];
	loop_opcodes[38] = rel_to_hook_bytes[1];
	loop_opcodes[39] = rel_to_hook_bytes[0];

	std::cout << "Opcode arrays have been built and ready for injection" << std::endl;
 }

int veritas_hook::inject_hook(DWORD procId, HANDLE hProcess)
{
	std::cout << "Trying to get vstcommon.dll address " << std::endl;
	uintptr_t vstcommon_base = GetmoduleBaseAddress(procId, L"vstcommon.dll");
	if (!vstcommon_base == 0)
	{
		uintptr_t error_log_addr = vstcommon_base + hooked_func_offset;
		std::cout << "Veritas (vstcommon) module detected successfully at: " << std::hex << vstcommon_base << std::endl;
		std::cout << "Error log addr " << std::hex << error_log_addr << std::endl;
		std::cout << "Error log byte check " << std::hex << error_log_addr + 0x0E << std::endl;
		BYTE read_bytes[3] = { 0x90, 0x90, 0x90 };
		BYTE ss_func_bytes[3] = { 0x33, 0xC5, 0x89 };
		if (!ReadProcessMemory(hProcess, (BYTE*)(error_log_addr + 0x0E) , &read_bytes, sizeof(read_bytes), nullptr) == 0)
		{
			if (read_bytes[0] == ss_func_bytes[0] && read_bytes[2] == ss_func_bytes[2])
			{
				std::cout << "Veritas error log function located successfull" << std::endl;
				build_byte_arrays(error_log_addr);
				WriteProcessMemory(hProcess, (void*)(loop_addr), &loop_opcodes, sizeof(loop_opcodes), nullptr);
				std::cout << "Hook loop has been written to codmp.exe" << std::endl;
				WriteProcessMemory(hProcess, (void*)(error_log_addr), &hook_opcodes, sizeof(hook_opcodes), nullptr);
				std::cout << "Hook has been written to vstcommon.dll" << std::endl;
			}
			else
			{
				for (int i = 0; i < 3; ++i)
				{
					std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)(unsigned char)read_bytes[i] << " ";
				}
				for (int i = 0; i < 3; ++i)
				{
					std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)(unsigned char)ss_func_bytes[i] << " ";
				}

				std::cout << "Bytes do not match for error function" << std::endl;
			}
		}
		else
		{
			std::cout << "Could not read memory to validate error logging function:" << std::endl;
			std::cout << "Error Code: " << GetLastError() << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to find vstcommon.dll module" << std::endl;
		std::cout << "Error Code: " << GetLastError() << std::endl;
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