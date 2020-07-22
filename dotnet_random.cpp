#include "dotnet_random.hpp"

void dotnet_random::refresh_seed()
{
	int num = 161803398 - fabs(GetTickCount());
	SeedArray[55] = num;
	int num2 = 1;
	for (int i = 1; i < 55; i++)
	{
		int num3 = 21 * i % 55;
		SeedArray[num3] = num2;
		num2 = num - num2;
		if (num2 < 0)
		{
			num2 += 2147483647;
		}
		num = SeedArray[num3];
	}
	for (int j = 1; j < 5; j++)
	{
		for (int k = 1; k < 56; k++)
		{
			SeedArray[k] -= SeedArray[1 + (k + 30) % 55];
			if (SeedArray[k] < 0)
			{
				SeedArray[k] += 2147483647;
			}
		}
	}
	inext = 0;
	inextp = 21;
}

int dotnet_random::InternalSample() 
{
	int num = inext;
	int num2 = inextp;
	if (++num >= 56)
	{
		num = 1;
	}
	if (++num2 >= 56)
	{
		num2 = 1;
	}
	int num3 = SeedArray[num] - SeedArray[num2];
	if (num3 < 0)
	{
		num3 += 2147483647;
	}
	SeedArray[num] = num3;
	inext = num;
	inextp = num2;
	return num3;
}

double dotnet_random::Sample()
{
	return InternalSample() * 4.6566128752457969E-10;
}


int dotnet_random::next()
{
	{
		int num = 50000;
		return (Sample() * num) + 25000;
	}
}