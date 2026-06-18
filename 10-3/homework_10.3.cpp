/*
main.cpp
project : GenericCirQ와 multi thread를 이용하여 Event 생성 및 처리 과정을 시뮬레이션하는 메인 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// LARGE_INTEGER 자료형 사용하기 위한 헤더파일
#include <Windows.h>

// thread 클래스를 사용하기 위한 헤더파일
#include <thread>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// srand(), time() 함수를 사용하기 위한 헤더파일
#include <ctime>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// Multi_Thread 헤더파일 포함하기
#include "Multi_Thread.h"

// GenericCirQ template class 사용하기 위한 헤더파일
#include "GenericCirQ.h"

// Event 클래스 사용하기 위한 헤더파일
#include "Event.h"

// 시뮬레이션 상수 사용하기 위한 헤더파일
#include "SimParams.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

/*
GenericCirQ와 multi thread를 이용하여 
Event 생성 및 처리 과정을 시뮬레이션하는 메인 함수
*/
void main()
{
    // 성능 측정용 주파수 저장 변수 선언하기
    LARGE_INTEGER QP_freq;

    // 성능 측정용 주파수 초기화하기
    QueryPerformanceFrequency(&QP_freq);

    // 난수 시드 초기화하기
    srand((unsigned int)time(NULL));

    // main 출력 보호용 mutex 객체 선언하기
    mutex cs_main;

    // monitor 보호용 mutex 객체 선언하기
    mutex cs_thrd_mon;

    // 스레드 종료 플래그 선언하기
    THREAD_FLAG eventThreadFlag = RUN;

    // Event Circular Queue 객체 생성하기
    Generic_CirQ<Event> cirQ_Event("CirQ_Ev", CIRQ_CAPACITY);

    // 스레드 모니터링 구조체 선언하기
    ThreadStatusMonitor thrdMon;

    // 종료 플래그 주소 저장하기
    thrdMon.pFlagThreadTerminate = &eventThreadFlag;

    // 전체 생성 Event 개수 초기화하기
    thrdMon.totalEventGenerated = 0;

    // 전체 처리 Event 개수 초기화하기
    thrdMon.totalEventProcessed = 0;

    // 생성 Event 개수 초기화하기
    thrdMon.numEventGenerated[0] = 0;

    // 처리 Event 개수 초기화하기
    thrdMon.numEventProcessed[0] = 0;

    // Event 배열 초기화 반복하기
    for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
    {
        // 생성 Event 번호 초기화하기
        thrdMon.eventGenerated[ev].Set_Event_No(-1);

        // 생성 Event priority 초기화하기
        thrdMon.eventGenerated[ev].Set_Event_Pri(-1);

        // 처리 Event 번호 초기화하기
        thrdMon.eventProcessed[ev].Set_Event_No(-1);

        // 처리 Event priority 초기화하기
        thrdMon.eventProcessed[ev].Set_Event_Pri(-1);
    }

    // EventProc 스레드 파라미터 선언하기
    ThreadParam_Event paramEvProc;

    // main mutex 주소 저장하기
    paramEvProc.pCS_main = &cs_main;

    // monitor mutex 주소 저장하기
    paramEvProc.pCS_thrd_mon = &cs_thrd_mon;

    // Circular Queue 주소 저장하기
    paramEvProc.pCirQ_Event = &cirQ_Event;

    // 스레드 역할 저장하기
    paramEvProc.role = EVENT_HANDLER;

    // 스레드 주소 저장하기
    paramEvProc.myAddr = 0;

    // 최대 반복 횟수 저장하기
    paramEvProc.maxRound = MAX_ROUND;

    // 목표 Event 개수 저장하기
    paramEvProc.targetEventGen = TOTAL_NUM_EVENTS;

    // 성능 측정 주파수 저장하기
    paramEvProc.QP_freq = QP_freq;

    // 모니터링 구조체 주소 저장하기
    paramEvProc.pThrdMon = &thrdMon;

    // EventProc 스레드 생성하기
    thread thrd_EvProc(EventProc, &paramEvProc);

    // 생성 완료 메시지 출력하기
    cout << "Thread_EventProc is created and activated ..." << endl;

    // EventGen 스레드 파라미터 선언하기
    ThreadParam_Event paramEvGen;

    // main mutex 주소 저장하기
    paramEvGen.pCS_main = &cs_main;

    // monitor mutex 주소 저장하기
    paramEvGen.pCS_thrd_mon = &cs_thrd_mon;

    // Circular Queue 주소 저장하기
    paramEvGen.pCirQ_Event = &cirQ_Event;

    // 스레드 역할 저장하기
    paramEvGen.role = EVENT_GENERATOR;

    // 스레드 주소 저장하기
    paramEvGen.myAddr = 0;

    // 최대 반복 횟수 저장하기
    paramEvGen.maxRound = MAX_ROUND;

    // 목표 Event 개수 저장하기
    paramEvGen.targetEventGen = TOTAL_NUM_EVENTS;

    // 성능 측정 주파수 저장하기
    paramEvGen.QP_freq = QP_freq;

    // 모니터링 구조체 주소 저장하기
    paramEvGen.pThrdMon = &thrdMon;

    // EventGen 스레드 생성하기
    thread thrd_EvGen(EventGen, &paramEvGen);

    // 생성 완료 메시지 출력하기
    cout << "Thread_EventGen is created and activated ..." << endl;

    // 주기적 모니터링 반복하기
    for (int round = 0; round < MAX_ROUND; round++)
    {
        // main mutex 잠그기
        cs_main.lock();

        // 구분선 출력하기
        cout << endl
            << "=========================================="
            << endl;

        // 현재 상태 출력하기
        cout << "Thread monitoring by main() :: ";

        cout << " round("
            << setw(2)
            << round
            << "): current total_event_gen(";

        cout << setw(2)
            << thrdMon.totalEventGenerated
            << "), total_event_proc(";

        cout << setw(2)
            << thrdMon.totalEventProcessed
            << ")"
            << endl;

        // 현재 생성된 Event 개수 저장하기
        int numEventGenerated = thrdMon.numEventGenerated[0];

        // 생성된 Event 출력하기
        cout << "Events generated (current total = "
            << setw(2)
            << numEventGenerated
            << ") :"
            << endl;

        printEvents(cout,
            thrdMon.eventGenerated,
            thrdMon.numEventGenerated[0],
            EVENTS_PER_LINE);

        // 현재 Queue 원소 개수 저장하기
        int num_events_in_CirQ = cirQ_Event.Get_Num_Elements();

        // Queue 상태 출력하기
        cout << "Events currently in CirQ ( total = "
            << num_events_in_CirQ
            << ") :"
            << endl;

        cout << cirQ_Event << endl;

        // 현재 처리된 Event 개수 저장하기
        int numEventProcessed = thrdMon.totalEventProcessed;

        // 처리된 Event 출력하기
        cout << "Events processed (current total = "
            << numEventProcessed
            << ") :"
            << endl;

        printEvents(cout,
            thrdMon.eventProcessed,
            thrdMon.numEventProcessed[0],
            EVENTS_PER_LINE);

        // 모든 Event 처리 완료 여부 확인하기
        if (numEventProcessed >= TOTAL_NUM_EVENTS)
        {
            // 종료 플래그 설정하기
            eventThreadFlag = TERMINATE;

            // mutex 해제하기
            cs_main.unlock();

            break;
        }

        // mutex 해제하기
        cs_main.unlock();

        // 잠시 대기하기
        Sleep(100);
    }

    // EventProc 스레드 종료 대기하기
    thrd_EvProc.join();

    // EventGen 스레드 종료 대기하기
    thrd_EvGen.join();
}