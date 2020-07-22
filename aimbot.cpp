#include "aimbot.hpp"
#include "utils.hpp"

aimbot::aimbot()
{
	
}

bool aimbot::toggle(bool aimbot_state)
{
	return !aimbot_state;
}

void aimbot::print_client_info(int client_no)
{
	std::cout << " Client: " << std::dec << centities[client_no].client_no
		<< " X Pos: " << std::dec << centities[client_no].cur_coords.x 
		<< " Y Pos: " << std::dec << centities[client_no].cur_coords.y 
		<< " Z Pos: " << std::dec << centities[client_no].cur_coords.z << std::endl;
}

void aimbot::print_player_client_no()
{
	std::cout << "Local Client: " << std::dec << cg_t.ref_angles.x << std::endl;
}

void aimbot::update_values(HANDLE hProcess)
{
	//Read in Centities
	ReadProcessMemory(hProcess, (VOID*)entity_list, &centities, sizeof(centities), nullptr);

	//Read in local player info
	ReadProcessMemory(hProcess, (VOID*)cgt_addr, &cg_t, sizeof(cg_t), nullptr);

	//Read in local player writable angles
	ReadProcessMemory(hProcess, (VOID*)cgt_addr, &cg_t, sizeof(cg_t), nullptr);
}

float aimbot::yaw_to_enemy(int client_no)
{
	float const degrees_ratio = 180 / PI_F;
	float const radian_ratio = PI_F / 180;
	float x_difference = cg_t.ref_coords.x - centities[client_no].coords.x;
	float y_difference = cg_t.ref_coords.y - centities[client_no].coords.y;
	float distance_to_enemy = sqrtf((x_difference * x_difference) + (y_difference * y_difference));
	float global_bearing_to_enemy = 0;

	if (x_difference >= 0 && y_difference >= 0)
	{
		global_bearing_to_enemy = 270 + (degrees_ratio * atan(fabsf(y_difference) / fabsf(x_difference)));
	}
	else if (x_difference >= 0 && y_difference <= 0)
	{
		global_bearing_to_enemy = 270 - (degrees_ratio * atan(fabsf(y_difference) / fabsf(x_difference)));
	}
	else if (x_difference <= 0 && y_difference >= 0)
	{
		global_bearing_to_enemy = 90 - (degrees_ratio * atan(fabsf(y_difference) / fabsf(x_difference)));
	}
	else if (x_difference <= 0 && y_difference <= 0)
	{
		global_bearing_to_enemy = 90 + (degrees_ratio * atan(fabsf(y_difference) / fabsf(x_difference)));
	}

	float corrected_player_bearing = 0;

	if (cg_t.ref_angles.x <= 0 && cg_t.ref_angles.x > -180)
	{
		corrected_player_bearing = -1 * cg_t.ref_angles.x;
	}
	else if (cg_t.ref_angles.x >= 0 && cg_t.ref_angles.x <= 180)
	{
		corrected_player_bearing = 360 - cg_t.ref_angles.x;
	}

	int bearing_to_enemy = 0;

	if (global_bearing_to_enemy >= corrected_player_bearing)
	{
		bearing_to_enemy = global_bearing_to_enemy - corrected_player_bearing;
	}
	else if (global_bearing_to_enemy < corrected_player_bearing)
	{
		bearing_to_enemy = (360 - corrected_player_bearing) + global_bearing_to_enemy;
	}
	
	return bearing_to_enemy;
}

int aimbot::closest_enemy(std::vector<int> enemy_list)
{

}
