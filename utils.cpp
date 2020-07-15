#include "utils.hpp"

void update_console(bool wh, bool tb, bool fr, bool nr, bool ab, int fps)
{
	system("cls");

	std::cout << "Wall Hack (NUM1) " << wh << std::endl
		<< "Trigger Bot (NUM2): " << tb << std::endl
		<< "Fast Run (NUM3) (Activate: LeftShift): " << fr << std::endl
		<< "No Recoil (NUM4): " << nr << std::endl
		<< "Aimbot: " << ab << std::endl
		<< "UNSTABLE & NEEDS THREADING FPS Bypass (0 = off, 1 = 333, 2 = 500): " << std::dec << fps << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl
		<< "=============================================" << nr << std::endl;
}

void print_addr(intptr_t value)
{
	std::cout << "addr: 0x" << std::hex << value << std::endl;
}