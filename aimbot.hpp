#ifndef aimbotHEADER
#define aimbotHEADER

#include <windows.h>

class aimbot
{
public:

	struct ent_info
	{
		float x, y, z;
		int client_num;
		intptr_t vec3_loc_addr;
	};

	struct entities
	{
		ent_info entity1 = { 0,0,0,0,0x30211B38};
		ent_info entity2 = { 0,0,0,1,0 };
	} ents;

	intptr_t entity_list = 0x30211940;

	aimbot();
	void get_locs();
};

#endif