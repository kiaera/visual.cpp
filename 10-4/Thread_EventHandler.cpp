/*
Thread_EventHandler.cpp
project : EventProc 스레드 함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// Sleep 함수를 사용하기 위한 헤더파일
#include <Windows.h>

// Multi_Thread 헤더파일 포함하기
#include "Multi_Thread.h"

/*
Event 처리 스레드 함수 구현하기
*/
void EventProc(ThreadParam_Event* pParam)
{
    // 스레드 파라미터 주소 저장하기
    ThreadParam_Event* pThrdParam = pParam;

    // Priority Queue 주소 저장하기
    GenericHeapPrioQ_KV<int, Event>* pPrioQ_Event = pThrdParam->pPrioQ_Event;

    // 모니터링 구조체 주소 저장하기
    ThreadStatusMonitor* pThrdMon = pThrdParam->pThrdMon;

    // 최대 반복 횟수 저장하기
    int maxRound = pThrdParam->maxRound;

    // 처리된 Event 개수 저장하기
    int ev_proc_count = 0;

    // 라운드 반복하기
    for (int round = 0; round < maxRound; round++)
    {
        // 종료 플래그 확인하기
        if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
        {
            break;
        }

        // Priority Queue가 비어있지 않은 경우 처리하기
        if (!pPrioQ_Event->isEmpty())
        {
            // Priority Queue에서 최고 우선순위 Entry 추출하기
            GenericEntry<int, Event>* pEntry = pPrioQ_Event->pop();

            // Entry 추출 성공 여부 확인하기
            if (pEntry != NULL)
            {
                // Entry에서 Event 꺼내기
                Event event = pEntry->getValue();

                // monitor 보호 mutex 잠그기
                pThrdParam->pCS_thrd_mon->lock();

                // 처리된 Event 저장하기
                pThrdMon->eventProcessed[ev_proc_count] = event;

                // 처리된 Event 개수 증가시키기
                pThrdMon->numEventProcessed[0]++;

                // 전체 처리 Event 개수 증가시키기
                pThrdMon->totalEventProcessed++;

                // monitor 보호 mutex 해제하기
                pThrdParam->pCS_thrd_mon->unlock();

                // 처리된 Event 개수 증가시키기
                ev_proc_count++;

                // 동적 메모리 해제하기
                delete pEntry;
            }
        }

        // 처리 스레드 잠시 대기하기
        Sleep(300 + rand() % 100);
    }
}