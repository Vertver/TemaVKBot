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
#pragma once
#include <iostream>

typedef signed char i8;
typedef unsigned char u8;
typedef signed short i16;
typedef unsigned short u16;
typedef signed int i32;
typedef unsigned int u32;
typedef signed long long i64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef u64 uint64;
typedef i8 int8;
typedef i16 int16;
typedef i64 int64;
typedef f32 r32;
typedef f64 r64;
typedef i32 b32;
typedef f64 real64;

typedef char utf8;
typedef utf8* PStr;
typedef utf8 const* PConstStr;

#if defined (_WIN32) || defined(_WIN64)
#define OS_WINDOWS
#endif

#ifdef OS_WINDOWS
#include <Windows.h>

#define IsInvalidHandle(x) (x == 0 || x == INVALID_HANDLE_VALUE)
#define MAX_PATH 260

typedef wchar_t utf16;
typedef utf8 stringPath[MAX_PATH];
typedef utf8 stringName[MAX_PATH];
typedef utf16 wstringPath[MAX_PATH];
#else
#include <pthread.h>
#define PATH_MAX 4096 
#define NAME_MAX 256 
typedef u16 utf16;
typedef utf8 stringPath[PATH_MAX];
typedef utf8 stringName[NAME_MAX];
#endif

typedef utf16* PWStr;
typedef utf16 const* PConstWStr;

typedef utf8 string8[16];
typedef utf8 string16[16];
typedef utf8 string32[32];
typedef utf8 string64[64];
typedef utf8 string128[128];
typedef utf8 string256[256];
typedef utf8 string512[512];
typedef utf8 string1k[1024];
typedef utf8 string2k[2048];
typedef utf8 string4k[4096];
typedef utf8 string8k[8192];
typedef utf8 string16k[16384];
typedef utf8 string32k[32768];
typedef utf8 string64k[65536];

typedef utf16 wstring8[8];
typedef utf16 wstring16[16];
typedef utf16 wstring32[32];
typedef utf16 wstring64[64];
typedef utf16 wstring128[128];
typedef utf16 wstring256[256];
typedef utf16 wstring512[512];
typedef utf16 wstring1k[1024];
typedef utf16 wstring2k[2048];
typedef utf16 wstring4k[4096];
typedef utf16 wstring8k[8192];
typedef utf16 wstring16k[16384];
typedef utf16 wstring32k[32768];
typedef utf16 wstring64k[65536];

#ifdef OS_WINDOWS
inline
int
ConvertToUTF16(
	const char* pUTF8String,
	wstring4k& stringConverted		// 8кбайт более чем достаточно, да
)
{
	return MultiByteToWideChar(CP_UTF8, 0, pUTF8String, -1, stringConverted, ARRAYSIZE(stringConverted));
}
#endif

enum ModuleType : i32
{
	eNoneType,				// Для пустых интерфейсов бота
	eTemaBotType			// Базовый класс для бизнес логики бота  
};

struct TemaAuthStruct
{
	const char* pSessionString = nullptr;			// Название сессии, для упрощения ориентации в коде
	const char* pVkBotKeyString = nullptr;			// Ключ для использование VK API, прости его господи
	const char* pLoginString = nullptr;				// Логин для бота (а вы думали, можно как анонимус сидеть? Хер там!)
	const char* pPasswordString = nullptr;			// Пароль для бота (сейм что и логин по значению)
};

class ITemaInterface
{
protected:
	TemaAuthStruct localAuthData = {};

public:
	virtual i32 Initialize(TemaAuthStruct* temaAuth) = 0;		// Инициализация в системе, авторизация бота в сети (если это базовый класс бота), 
	virtual i32 Destroy() = 0;									// Уничтожение стейта, деавторизация

	virtual i32 Update() = 0;									// Функция апдейта, которая происходит в цикле главного потока

	virtual void GetModuleName(string256& szModuleName) = 0;
	virtual void GetModuleType(ModuleType& type) = 0;
};

class CSimpleEvent
{
private:
	void* hEvent = nullptr;

public:
	CSimpleEvent();
	~CSimpleEvent();

	void Raise();
	void Reset();
	void Wait();
	bool Wait(i32 TimeToWait);
	bool IsRaised();
};

typedef i32(WORKERPROC)(void* pInstance);

struct WorkerThreadStruct
{
	u32 WorkerThreadId = (u32)-2;		// Стандартное значение для функции GetCurrentThreadId()
	size_t WorkerIndex = 0;
	void* ThreadHandle = nullptr;
	void* EventEndHandle = nullptr;
	WORKERPROC* pWorkerFunc = nullptr;
	string64 WorkerNameString = {};
	string256 WorkerDescriptionString = {};
};

struct WorkersList
{
	WorkersList* pPrevious = nullptr;
	WorkersList* pNext = nullptr;
	void* pContext = nullptr;
	WorkerThreadStruct* pWorkerStruct = nullptr;
};

struct WorkerArg
{
	void* EventEndHandle = nullptr;
	void* ThreadHandle = nullptr;
};

class CWorkerSpawner
{
private:
	WorkersList* pFirstWorker = nullptr;

	void* SpawnThread(WORKERPROC* pWorkerFunc, void* pArg);
	bool DestroyThread(size_t ThreadId);

public:
	CWorkerSpawner();
	~CWorkerSpawner();

	bool AddWorker(WORKERPROC* pWorkerFunc, void* pArg, i32& WorkerId);
	bool DeleteWorker(i32 WorkerId);

	void GetWorkerName(i32 WorkerId, string64& name);
	void GetWorkerDescription(i32 WorkerId, string64& description);
};
