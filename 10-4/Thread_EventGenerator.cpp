/*
Thread_EventGenerator.cpp
project : EventGen 스레드 함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// Sleep 함수를 사용하기 위한 헤더파일
#include <Windows.h>

// Multi_Thread 헤더파일 포함하기
#include "Multi_Thread.h"

/*
Event 생성 스레드 함수 구현하기
*/
void EventGen(ThreadParam_Event* pParam)
{
    // 스레드 파라미터 주소 저장하기
    ThreadParam_Event* pThrdParam = pParam;

    // Priority Queue 주소 저장하기
    GenericHeapPrioQ_KV<int, Event>* pPrioQ_Event = pThrdParam->pPrioQ_Event;

    // 모니터링 구조체 주소 저장하기
    ThreadStatusMonitor* pThrdMon = pThrdParam->pThrdMon;

    // 최대 반복 횟수 저장하기
    int maxRound = pThrdParam->maxRound;

    // 목표 생성 Event 개수 저장하기
    int targetEventGen = pThrdParam->targetEventGen;

    // 생성된 Event 개수 저장하기
    int ev_gen_count = 0;

    // 라운드 반복하기
    for (int round = 0; round < maxRound; round++)
    {
        // 목표 Event 개수 생성 완료 여부 확인하기
        if (ev_gen_count >= targetEventGen)
        {
            // 종료 플래그 확인하기
            if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
            {
                break;
            }
            else
            {
                Sleep(500);

                continue;
            }
        }

        // Event 번호 생성하기
        int ev_no = ev_gen_count;

        // Event priority를 29부터 0까지 순서대로 생성하기
        int ev_pri = targetEventGen - ev_gen_count - 1;

        // Event 이름 생성하기
        std::string evt_nm = std::string("evt_");

        // 한 자리 Event 번호인 경우 0 붙이기
        if (ev_no < 10)
        {
            evt_nm += "0";
        }

        // Event 번호를 문자열로 추가하기
        evt_nm += std::to_string(ev_no);

        // Event 객체 직접 생성하기
        Event* pEv = new Event(ev_no, ev_pri, evt_nm, pThrdParam->myAddr);

        // Event priority를 key로 하는 Entry 생성하기
        GenericEntry<int, Event> entry(pEv->getEventPri(), *pEv);

        // Priority Queue에 Event 삽입 시도하기
        while (pPrioQ_Event->push(entry) == NULL)
        {
            // main 출력 보호 mutex 잠그기
            pThrdParam->pCS_main->lock();

            // Queue Full 메시지 출력하기
            std::cout << "PrioQ_Event is Full, waiting ..." << std::endl;

            // main 출력 보호 mutex 해제하기
            pThrdParam->pCS_main->unlock();

            // 잠시 대기하기
            Sleep(1000);
        }

        // monitor 보호 mutex 잠그기
        pThrdParam->pCS_thrd_mon->lock();

        // 생성된 Event 저장하기
        pThrdMon->eventGenerated[ev_gen_count] = *pEv;

        // 생성 Event 개수 증가시키기
        pThrdMon->numEventGenerated[0]++;

        // 전체 생성 Event 개수 증가시키기
        pThrdMon->totalEventGenerated++;

        // monitor 보호 mutex 해제하기
        pThrdParam->pCS_thrd_mon->unlock();

        // 생성된 Event 개수 증가시키기
        ev_gen_count++;

        // 동적 메모리 해제하기
        delete pEv;

        // 생성 스레드 잠시 대기하기
        Sleep(100 + rand() % 300);
    }
}