#include "aimbot.hpp"
#include "utils.hpp"

aimbot::aimbot()
{
	
}

bool aimbot::toggle(bool aimbot_state)
{
	return !aimbot_state;
}

void aimbot::update_values(HANDLE hProcess)
{
	ReadProcessMemory(hProcess, (VOID*)entity_list, &centities, sizeof(centities), nullptr);

	system("cls");
	for (int i = 0; i < 16; i++)
	{
		std::cout << "Value " << std::dec << centities[i].cur_wep << std::endl;
	}
}

