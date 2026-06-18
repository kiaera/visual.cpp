/*
Thread_EventGenerator.cpp
project : EventGen 스레드 함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// Sleep 함수를 사용하기 위한 헤더파일
#include <Windows.h>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// Multi_Thread 헤더파일 포함하기
#include "Multi_Thread.h"

// GenericCirQ template class 사용하기 위한 헤더파일
#include "GenericCirQ.h"

// Event 클래스 사용하기 위한 헤더파일
#include "Event.h"

// 시뮬레이션 상수 사용하기 위한 헤더파일
#include "SimParams.h"

/*
Event 생성 스레드 함수 구현하기
*/
void EventGen(ThreadParam_Event* pParam)
{
    // 스레드 파라미터 주소 저장하기
    ThreadParam_Event* pThrdParam = pParam;

    // Circular Queue 주소 저장하기
    Generic_CirQ<Event>* pCirQ_Event = pThrdParam->pCirQ_Event;

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

        // Event priority를 49부터 0까지 역순으로 생성하기
        int ev_priority = targetEventGen - ev_gen_count - 1;

        // Event 이름 생성하기
        std::string evt_name = std::string("evt_") + std::to_string(ev_no);

        // Event 생성자 주소 저장하기
        int ev_gen_addr = pThrdParam->myAddr;

        // 새로운 Event 직접 생성하기
        Event* pEv = new Event(ev_no, ev_priority, evt_name, ev_gen_addr);

        // Queue에 Event 삽입 시도하기
        while (pCirQ_Event->enqueue(*pEv) == NULL)
        {
            // main 출력 보호하기
            pThrdParam->pCS_main->lock();

            // Queue Full 메시지 출력하기
            std::cout << "CirQ_Event is Full, waiting ..." << std::endl;

            // mutex 해제하기
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

        // 잠시 대기하기
        Sleep(100 + rand() % 300);
    }
}