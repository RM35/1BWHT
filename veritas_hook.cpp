#include "veritas_hook.hpp"

veritas_hook::veritas_hook()
{

}

bool veritas_hook::toggle(bool veritas_hook_state)
{
	return !veritas_hook_state;
}

void veritas_hook::build_byte_arrays(uintptr_t vstdll_base)
{
	uintptr_t make_ss_addr = vstdll_base + 0x3340;
	uintptr_t hook_loop_addr = codmp_base + hook_loop_offset;
	intptr_t rel_offset_to_loop = 0xFFFFFFFF - make_ss_addr - hook_loop_addr + 0x4;
	intptr_t rel_offset_to_hook = make_ss_addr - hook_loop_addr - 0x41;


}

int veritas_hook::inject_hook(DWORD procId, HANDLE hProcess)
{
	uintptr_t vstdll_base = GetmoduleBaseAddress(procId, L"vstdll.dll");
	if (!vstdll_base == 0)
	{
		std::cout << "Veritas module detected successfully at: " << std::hex << vstdll_base << std::endl;
		BYTE read_bytes[3] = { 0x90, 0x90, 0x90 };
		BYTE ss_func_bytes[3] = { 0x89, 0x45, 0xFC };
		if (!ReadProcessMemory(hProcess, (BYTE*)vstdll_base + 0x3350, &read_bytes, sizeof(read_bytes), nullptr) == 0)
		{
			if (read_bytes[0] == ss_func_bytes[0] && read_bytes[2] == ss_func_bytes[2])
			{
				std::cout << "Veritas screenshot function located successfull" << std::endl;
				build_byte_arrays(vstdll_base);
			}
		}
	}
	return 0;
	//WriteProcessMemory(hProcess, (void*)(0x3003A313), &nop_function, sizeof(nop_function), nullptr);
}
