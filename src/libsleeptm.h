/****************************************************************
* Vertver, 2019. All rights no reserved.
* libsleeptm - simple library to manipulate with time
* License: Unlicense
* ***************************************************************
* Module Name : Base library header.
*****************************************************************/
#pragma once

#define SLEEPTM_VERSION 0.1f

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS_PLATFORM
#include <windows.h>
typedef NTSTATUS (__stdcall* PNTDELAYEXECUTION)(BOOL, const LARGE_INTEGER*);
#else
#include <unistd.h>		// usleep and sleep defenetion
#include <sys/time.h>
#define POSIX_PLATFORM
#endif

#ifndef NULL
#define NULL 0
#endif

/*
	slInitialize - Initialize library instance in application. 
	This function should be called only once at startup.

	On failed return -1, success - 0
*/
char
slInitialize(
	char bHQTimer		// set this argument by 'false' if you initialize "timeBeginPeriod" on application startup
);

/*
	slUnitialize - Unitialize library instance in application.
	This function should be called only once at destroy.

	On failed return -1, success - 0
*/
char
slUnitialize();

/*
	slMicroSleep - Suspend current thread until the time-out interval in microseconds elapses.

	On failed return -1, success - 0
*/
char
slMicroSleep(
	long long TimeToSleep
);

/*
	slMilliSleep - Suspend current thread until the time-out interval in milliseconds elapses.

	On failed return -1, success - 0
*/
char
slMilliSleep(
	unsigned long TimeToSleep
);

/*
	slSecondsSleep - Suspend current thread until the time-out interval in seconds elapses.

	On failed return -1, success - 0
*/
char 
slSecondSleep(
	unsigned long TimeToSleep
);

/*
	slGetSystemTime32 - Get time from system startup in 32-bit integers

	On failed return -1, success - 0
*/
char
slGetSystemTime32(
	unsigned long* MillisecondsTime
);

/*
	slGetSystemTime64 - Get time from system startup in 64-bit integers

	On failed return -1, success - 0
*/
char
slGetSystemTime64(
	unsigned long long* MillisecondsTime
);
