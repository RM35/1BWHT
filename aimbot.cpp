#include "aimbot.hpp"
#include "utils.hpp"

aimbot::aimbot()
{
	
}

void aimbot::get_locs(int players)
{
	intptr_t client_0_coords = entity_list + 0x1F8;

	coord_ad.insert(coord_ad.end(), client_0_coords);
	print_addr(coord_ad[0]);

	for (int i = 1; i <= (players - 1); i++)
	{
		coord_ad.insert(coord_ad.end(), client_0_coords + (i + 1) * 522);
		print_addr(coord_ad[i]);
	}
}