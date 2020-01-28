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
#include <process.h>

struct ThreadProcWorker
{

}

void 
ThreadWorkerFuncProc(

)
{
}

CSimpleEvent::CSimpleEvent()
{
#ifdef OS_WINDOWS
	hEvent = (void*)CreateEventEx(nullptr, nullptr, 0, 0);
#else 
	/*
		TODO:
	*/
#endif
}

CSimpleEvent::~CSimpleEvent()
{
#ifdef OS_WINDOWS
	if (!IsInvalidHandle(hEvent)) CloseHandle((HANDLE)hEvent);
#else 
	/*
		TODO:
	*/
#endif
}

void
CSimpleEvent::Raise()
{
#ifdef OS_WINDOWS
	SetEvent((HANDLE)hEvent);
#else 
	/*
		TODO:
	*/
#endif
}

void
CSimpleEvent::Reset()
{
#ifdef OS_WINDOWS
	ResetEvent((HANDLE)hEvent);
#else 
	/*
		TODO:
	*/
#endif
}

void
CSimpleEvent::Wait()
{
#ifdef OS_WINDOWS
	WaitForSingleObject((HANDLE)hEvent, INFINITE);
#else 
	/*
		TODO:
	*/
#endif
}

bool
CSimpleEvent::Wait(
	i32 TimeToWait
)
{
#ifdef OS_WINDOWS
	return WaitForSingleObject((HANDLE)hEvent, (DWORD)TimeToWait) == WAIT_OBJECT_0;
#else 
	/*
		TODO:
	*/
#endif
}

bool
CSimpleEvent::IsRaised()
{
#ifdef OS_WINDOWS
	return WaitForSingleObject((HANDLE)hEvent, 0) == WAIT_OBJECT_0;
#else 
	/*
		TODO:
	*/
#endif
}

CWorkerSpawner::CWorkerSpawner()
{

}

CWorkerSpawner::~CWorkerSpawner()
{

}

void*
CWorkerSpawner::SpawnThread(
	WORKERPROC* pWorkerFunc,
	void* pArg
)
{
#ifdef OS_WINDOWS
	/*
		В винде используем эту функцию, потому что при использование CreateThread 
		CRT неправильно очищается.
	*/
	void* threadHandle = _beginthread((_beginthread_proc_type)pWorkerFunc, 0, pArg);
	return IsInvalidHandle(threadHandle) ? nullptr : threadHandle;
#else 
	/*
		TODO:
	*/
#endif
}

bool 
CWorkerSpawner::DestroyThread(
	size_t ThreadId
)
{

	WorkersList* pPreviosTemp = nullptr;
	WorkersList* pNextTemp = nullptr;
	WorkersList* pCurrentTemp = pFirstWorker;

	while (pCurrentTemp) {
		if (pCurrentTemp->pWorkerStruct->WorkerThreadId == ThreadId) {
#ifdef OS_WINDOWS
			/* Убеждаемся, что эвент нормальный и идем дальше. */
			if (!IsInvalidHandle(pCurrentTemp->pWorkerStruct->EventEndHandle)) {
				if (!SetEvent((HANDLE)pCurrentTemp->pWorkerStruct->EventEndHandle)) return false;
			}

			/* 
				Обычно 50-100 миллисекунд хватает для уничтожения контекста, но если 
				не хватает - не стесняемся удалять поток по-жесткому.
			*/
			if (WaitForSingleObject((HANDLE)pCurrentTemp->pWorkerStruct->ThreadHandle, 100) == WAIT_TIMEOUT) {
				::TerminateThread((HANDLE)pCurrentTemp->pWorkerStruct->ThreadHandle, 0xFFFFFEE);
			}
#else

#endif
			return true;
		}
	}

	return false;

}

bool 
CWorkerSpawner::AddWorker(
	WORKERPROC* pWorkerFunc, 
	void* pArg,
	i32& WorkerId
)
{
	WorkerThreadStruct* pWorkerStruct = nullptr;
	WorkersList* pWorker = nullptr;

	pWorker = malloc(sizeof(WorkersList));
	if (!pWorker) return false;		// Серьезно, если у вас здесь повалилось - у вас явно ведро и скоро должен быть kernel panic.

	pWorker->pWorkerStruct = malloc(sizeof(WorkerThreadStruct));
	if (!pWorker->pWorkerStruct) return false;		// Вот правда, на тех же старых Orange Pi здесь падало иногда когда свапа не хватало.

	void* ThreadHandleTemp = SpawnThread(pWorkerFunc, pArg);
	if (!ThreadHandleTemp) return false;

	/* Мне нравится этот код. */
	WorkersList** ppWorker = &pFirstWorker;
	while (*ppWorker) {
		ppWorker = &((*ppWorker)->pNext);
	}

	*ppWorker = pWorker;
	return true;
}

bool
CWorkerSpawner::DeleteWorker(
	i32 WorkerId
)
{

}

void
CWorkerSpawner::GetWorkerName(
	i32 WorkerId, 
	string64& name
)
{

}

void
CWorkerSpawner::GetWorkerDescription(
	i32 WorkerId,
	string64& description
)
{

}
