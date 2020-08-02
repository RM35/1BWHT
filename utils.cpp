#include "utils.hpp"

void update_console(bool wh, bool tb, bool fr, bool nr, bool ab, int fps)
{
	std::cout << "Wall Hack (NUM1) " << wh << std::endl
		<< "Trigger Bot (NUM2): " << tb << std::endl
		<< "Fast Run (NUM3) (Activate: LeftShift): " << fr << std::endl
		<< "No Recoil (NUM4): " << nr << std::endl
		<< "Aimbot: Not Implemented yet" << ab << std::endl
		<< "FPS Bypass (0 = 250, 1 = 333, 2 = 500): " << std::dec << fps << std::endl;
}

void print_addr(intptr_t value)
{
	std::cout << "addr: 0x" << std::hex << value << std::endl;
}

float vec3_dot(const Vector3 v1, const Vector3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.y * v2.y;
}

void vec3_sub(const Vector3 veca, const Vector3 vecb, Vector3 out)
{
    out.x = veca.x - vecb.x;
    out.y = veca.y - vecb.y;
    out.z = veca.z - vecb.z;
}

void vec3_add(const Vector3 veca, const Vector3 vecb, Vector3 out)
{
    out.x = veca.x + vecb.x;
    out.y = veca.y + vecb.y;
    out.z = veca.z + vecb.z;
}

void vec3_copy(const Vector3 in, Vector3 out)
{
    out.x = in.x;
    out.y = in.y;
    out.z = in.z;
}

float vec3_distance(const Vector3 veca, const Vector3 vecb)
{
    return (sqrt(pow((veca.x - vecb.x), 2) + pow((veca.y - vecb.y), 2) + pow((veca.z - vecb.z), 2)));
}