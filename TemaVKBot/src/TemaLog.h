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
