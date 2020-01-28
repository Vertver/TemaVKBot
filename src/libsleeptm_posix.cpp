/****************************************************************
* Vertver, 2019. All rights no reserved.
* libsleeptm - simple library to manipulate with time
* License: Unlicense
* ***************************************************************
* Module Name : POSIX library impl.
*****************************************************************/
#include "libsleeptm.h"

#ifdef POSIX_PLATFORM
char
slInitialize(
	char bHQTimer
)
{
	return 0;
}

char
slUnitialize()
{
	return 0;
}

char
slMicroSleep(
	long long TimeToSleep
)
{
	return usleep((useconds_t)TimeToSleep);
}

char
slMilliSleep(
	unsigned long TimeToSleep
)
{
	sleep((unsigned int)TimeToSleep);
	return 0;
}

char
slSecondSleep(
	unsigned long TimeToSleep
)
{
	sleep((unsigned int)(TimeToSleep * 1000));
	return 0;
}

char
slGetSystemTime32(
	unsigned long* MillisecondsTime
)
{
	unsigned long long LongValue = 0;

	if (slGetSystemTime64(&LongValue) == -1) return -1;
	*MillisecondsTime = (unsigned long)LongValue;
}

char
slGetSystemTime64(
	unsigned long long* MillisecondsTime
) 
{
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) return -1;

	*MillisecondsTime = (uint64_t)(ts.tv_nsec / 1000000) + ((uint64_t)ts.tv_sec * 1000ull);
	return 0;
}

#endif