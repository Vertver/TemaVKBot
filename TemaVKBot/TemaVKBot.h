﻿/*****************************************************************
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
#define OS_WINDOW
#endif

#ifdef OS_WINDOW
#include <Windows.h>

#define MAX_PATH 260
typedef wchar_t utf16;
typedef utf8 stringPath[MAX_PATH];
typedef utf8 stringName[MAX_PATH];
typedef utf16 wstringPath[MAX_PATH];
#else
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

enum ModuleType : i32
{
	eNoneType,
	eTemaBotType
};

struct TemaAuthStruct
{
	const char* pVkBotKeyString = nullptr;
	const char* pLoginString = nullptr;
	const char* pPasswordString = nullptr;
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
