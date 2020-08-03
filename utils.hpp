#ifndef utilsHEADER
#define utilsHEADER

#include <iostream>
#include <math.h>

struct Vector3
{
	float x, y, z;
};

void print_addr(intptr_t value);
float vec3_dot(const Vector3 v1, const Vector3 v2);
void vec3_sub(const Vector3 veca, const Vector3 vecb, Vector3 out);
void vec3_add(const Vector3 veca, const Vector3 vecb, Vector3 out);
void vec3_copy(const Vector3 in, Vector3 out);
float vec3_distance(const Vector3 veca, const Vector3 vecb);

#endif