#ifndef whHEADER
#define whHEADER

#include <windows.h>
#include "proc.hpp"

class wall_hack
{
public:
	bool toggle(bool wall_hack_state, HANDLE hProcess);
};

#endif