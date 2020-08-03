#include "utils.hpp"

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