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
		� ����� ���������� ��� �������, ������ ��� ��� ������������� CreateThread 
		CRT ����������� ���������.
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
			/* ����������, ��� ����� ���������� � ���� ������. */
			if (!IsInvalidHandle(pCurrentTemp->pWorkerStruct->EventEndHandle)) {
				if (!SetEvent((HANDLE)pCurrentTemp->pWorkerStruct->EventEndHandle)) return false;
			}

			/* 
				������ 50-100 ����������� ������� ��� ����������� ���������, �� ���� 
				�� ������� - �� ���������� ������� ����� ��-��������.
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
	if (!pWorker) return false;		// ��������, ���� � ��� ����� ���������� - � ��� ���� ����� � ����� ������ ���� kernel panic.

	pWorker->pWorkerStruct = malloc(sizeof(WorkerThreadStruct));
	if (!pWorker->pWorkerStruct) return false;		// ��� ������, �� ��� �� ������ Orange Pi ����� ������ ������ ����� ����� �� �������.

	void* ThreadHandleTemp = SpawnThread(pWorkerFunc, pArg);
	if (!ThreadHandleTemp) return false;

	/* ��� �������� ���� ���. */
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
