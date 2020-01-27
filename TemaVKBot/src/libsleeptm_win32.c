/****************************************************************
* Vertver, 2019. All rights no reserved.
* libsleeptm - simple library to manipulate with time
* License: Unlicense
* ***************************************************************
* Module Name : WinAPI library impl.
*****************************************************************/
#include "libsleeptm.h"

#ifdef WINDOWS_PLATFORM
PNTDELAYEXECUTION pNtDelayExecution = NULL;
char HighQualityTimer = -1;

char
slInitialize(
	char bHQTimer
)
{
	HMODULE hModule = NULL;

	if (pNtDelayExecution) return -1;		// we are already initialized
	hModule = GetModuleHandleA("ntdll");
	if (!hModule || hModule == INVALID_HANDLE_VALUE) return -1;
	pNtDelayExecution = GetProcAddress(hModule, "NtDelayExecution");
	if (!pNtDelayExecution) return -1;

	/*
		Try to initialize high quality timer in application
	*/
	if (bHQTimer)
	{
		if (timeBeginPeriod(1) != TIMERR_NOERROR)
		{
			return -1;
		}
		else
		{
			HighQualityTimer = 1;
		}
	}

	return 0;
}

char
slUnitialize()
{
	if (HighQualityTimer != -1)
	{
		if (timeEndPeriod((UINT)HighQualityTimer) != TIMERR_NOERROR)
		{
			return -1;
		}
	}

	return 0;
}

char
slMicroSleep(
	long long TimeToSleep
)
{
	LARGE_INTEGER StructSleepTime = { 0 };
	StructSleepTime.QuadPart = -(TimeToSleep * 10);		// convert microseconds to 100 nanoseconds periods

	if (!pNtDelayExecution) return -1;
	if (pNtDelayExecution(FALSE, &StructSleepTime) != 0) return -1;

	return 0;
}

char
slMilliSleep(
	unsigned long TimeToSleep
)
{
	if (TimeToSleep >= 0xFFFFFFFE) return -1;
	Sleep(TimeToSleep);
	return 0;
}

char
slSecondSleep(
	unsigned long TimeToSleep
)
{
	DWORD dwSleepMilliseconds = TimeToSleep * 1000;
	if (dwSleepMilliseconds >= 0xFFFFFFFE) return -1;	// ignore integer overflow

	Sleep(dwSleepMilliseconds);
	return 0;
}

char
slGetSystemTime32(
	unsigned long* MillisecondsTime
)
{
	if (!MillisecondsTime) return -1;

	if (HighQualityTimer != -1)
	{
		*MillisecondsTime = timeGetTime();

	}
	else
	{
		*MillisecondsTime = GetTickCount();
	}

	return 0;
}

char
slGetSystemTime64(
	unsigned long long* MillisecondsTime
)
{
	if (!MillisecondsTime) return -1;

	*MillisecondsTime = GetTickCount64();
	return 0;
}
#endif
