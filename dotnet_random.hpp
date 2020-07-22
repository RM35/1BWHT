#ifndef dotnet_randomHEADER
#define dotnet_randomHEADER

#include <math.h>
#include <Windows.h>

class dotnet_random
{
public:
	int inext = 0;
	int inextp = 21; 
	int SeedArray[56];

	void refresh_seed();
	int InternalSample();
	double Sample();
	int next();
};
#endif