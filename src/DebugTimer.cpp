/*****************************************************************
* Копирайт (C) Антон Ковалев (vertver), 2020. Все права защищены.
* TemaVKBot - Бот, который дополнит ваши беседы бесполезным трепом
* GPLv3 лицензия
******************************************************************
* Данный бот создан как просто шутка, и не стремится оскорбить
* кого-либо (как самого Артемия Лебедева, так и его студию
* дизайна). Код бота распространяется под свободной лицензией
* GPLv3 для того, чтобы при создание порта на другие платформы
* от других людей код также был бы открыт и прозрачен для
* программиста.
******************************************************************
* Автору бота не требуется никаких пожертвований, он сам себя
* сможет обеспечить. Но чем вы точно сможете помочь автору
* проекта - так это pull request'ами и issue на гитхабе. Так
* вы и людям поможете избавиться от багов и говнокода, так и
* автору "спасибо" таким образом скажите.
*****************************************************************/
#include "TemaLog.h"
#include "math.h"

CDebugTimer g_timer;
CDebugLog g_log;

CDebugTimer::CDebugTimer()
{
	slInitialize(1);		// Винда по дефолту ставить HQ таймер, так что в единице смысла особого нету
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
		TODO: запись лога в файл
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
