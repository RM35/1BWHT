#ifndef PROCHEADER
#define PROCHEADER

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcId(const wchar_t* procName);

uintptr_t GetmoduleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int>);

#endif