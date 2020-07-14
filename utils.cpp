#include "utils.hpp"

void update_console(bool wh, bool tb, bool fr, bool nr)
{
	system("cls");

	std::cout << "Wall Hack (NUM1) " << wh << std::endl
		<< "Trigger Bot (NUM2): " << tb << std::endl
		<< "Fast Run (NUM3) (Activate: LeftShift): " << fr << std::endl
		<< "No Recoil (NUM4): " << nr << std::endl;
}

void print_addr(intptr_t value)
{
	std::cout << "print value:" << std::hex << value << std::endl;
}