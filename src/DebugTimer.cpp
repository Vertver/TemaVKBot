/*****************************************************************
* �������� (C) ����� ������� (vertver), 2020. ��� ����� ��������.
* TemaVKBot - ���, ������� �������� ���� ������ ����������� ������
* GPLv3 ��������
******************************************************************
* ������ ��� ������ ��� ������ �����, � �� ��������� ���������
* ����-���� (��� ������ ������� ��������, ��� � ��� ������
* �������). ��� ���� ���������������� ��� ��������� ���������
* GPLv3 ��� ����, ����� ��� �������� ����� �� ������ ���������
* �� ������ ����� ��� ����� ��� �� ������ � ��������� ���
* ������������.
******************************************************************
* ������ ���� �� ��������� ������� �������������, �� ��� ����
* ������ ����������. �� ��� �� ����� ������� ������ ������
* ������� - ��� ��� pull request'��� � issue �� �������. ���
* �� � ����� �������� ���������� �� ����� � ���������, ��� �
* ������ "�������" ����� ������� �������.
*****************************************************************/
#include "TemaLog.h"
#include "math.h"

CDebugTimer g_timer;
CDebugLog g_log;

CDebugTimer::CDebugTimer()
{
	slInitialize(1);		// ����� �� ������� ������� HQ ������, ��� ��� � ������� ������ ������� ����
	slGetSystemTime64(&TimerFirstStamp);
}

CDebugTimer::~CDebugTimer()
{
	slUnitialize();
}

u64
CDebugTimer::GetStartupTicks()
{
	return TimerFirstStamp;
}

CDebugTimer* 
CDebugTimer::Instance()
{
	return &g_timer;
}

u64 
CDebugTimer::Ticks()
{
	u64 tick = 0;
	slGetSystemTime64(&tick);
	return tick;
}

CDebugLog::CDebugLog()
{
	for (char*& stringBuf : pStringBuffers) {
		stringBuf  = (char*)malloc(DEBUG_LOG_BUFFER_LENGTH);
	}
}

CDebugLog::~CDebugLog()
{
	for (char*& stringBuf : pStringBuffers) {
		if (stringBuf) free(stringBuf);
	}
}

void CDebugLog::Update()
{
	/*
		TODO: ������ ���� � ����
	*/
}

void CDebugLog::PrintToLog(const char* pStringToPrint)
{
	i32 totalTicks = GetTimeFromBegin();
	i32 hours = totalTicks / 3600000;
	i32 minutes = (totalTicks - (hours * 3600000)) / 60000;
	i32 seconds = (totalTicks - (minutes * 60000)) / 1000;
	i32 millis = totalTicks - (seconds * 1000);

	memset(pStringBuffers[0], 0, DEBUG_LOG_BUFFER_LENGTH);
	snprintf(pStringBuffers[0], DEBUG_LOG_BUFFER_LENGTH, "[%02d:%02d:%02d.%03d] - %s", hours, minutes, seconds, millis, pStringToPrint);
	PRINT_DEBUGGER(pStringBuffers[0]);
}

void CDebugLog::PrintToLog(const char* line, const char* file, const char* pStringToPrint)
{
	memset(pStringBuffers[1], 0, DEBUG_LOG_BUFFER_LENGTH);
	snprintf(pStringBuffers[1], DEBUG_LOG_BUFFER_LENGTH, "[L: %s, F: %s]: %s", line, file, pStringToPrint);
	PrintToLog(pStringBuffers[1]);
}
