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
#include "TemaVKBot.h"
#include "libsleeptm.h"

class CDebugTimer
{
private:
	u64 TimerFirstStamp = 0;

public:
	CDebugTimer();
	~CDebugTimer();

	u64 GetStartupTicks();
	u64 Ticks();
};

#define ENABLE_DEBUG_TIMER \
	extern CDebugTimer g_timer 

#define BEGIN_STAMP() \
	u64 temp_tick_count = g_timer.Ticks();

#define END_STAMP() \
	(g_timer.Ticks() - temp_tick_count)

#ifdef OS_WINDOWS
#define PRINT_DEBUGGER(x) \
	if (IsDebuggerPresent()) {
		OutputDebugStringW();
	}
#endif

class CDebugLog
{
private:

public:
	CDebugLog();
	~CDebugLog();

	void Update();
	void PrintToLog(const char* pStringToPrint);
};
