/*
Multi_Thread.h
project : EventGen, EventProc 스레드에 필요한 구조체와 함수를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// MULTI_THREAD_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef MULTI_THREAD_H

// MULTI_THREAD_H 매크로 정의하기
#define MULTI_THREAD_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>

// LARGE_INTEGER 자료형 사용하기 위한 헤더파일
#include <Windows.h>

// thread 클래스를 사용하기 위한 헤더파일
#include <thread>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// process 관련 함수를 사용하기 위한 헤더파일
#include <process.h>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// Heap Priority Queue 사용하기 위한 헤더파일
#include "GenericHeapPrioQ_KV.h"

// Event 클래스 사용하기 위한 헤더파일
#include "Event.h"

// 시뮬레이션 상수 사용하기 위한 헤더파일
#include "SimParams.h"

// Generator 개수 정의하기
#define NUM_GEN 1

// Handler 개수 정의하기
#define NUM_HND 1

// 스레드 역할 종류 정의하기
enum ROLE
{
    EVENT_GENERATOR,
    EVENT_HANDLER
};

// 스레드 상태 종류 정의하기
enum THREAD_FLAG
{
    INITIALIZE,
    RUN,
    TERMINATE
};

// 스레드 모니터링 구조체 선언하기
typedef struct
{
    // 생성된 Event 개수 저장하기
    int numEventGenerated[NUM_GEN];

    // 처리된 Event 개수 저장하기
    int numEventProcessed[NUM_HND];

    // 전체 생성 Event 개수 저장하기
    int totalEventGenerated;

    // 전체 처리 Event 개수 저장하기
    int totalEventProcessed;

    // 생성된 Event 배열 저장하기
    Event eventGenerated[TOTAL_NUM_EVENTS];

    // 처리된 Event 배열 저장하기
    Event eventProcessed[TOTAL_NUM_EVENTS];

    // 스레드 종료 플래그 주소 저장하기
    THREAD_FLAG* pFlagThreadTerminate;

} ThreadStatusMonitor;

// Event 스레드 파라미터 구조체 선언하기
typedef struct
{
    // main 출력 보호용 mutex 주소 저장하기
    std::mutex* pCS_main;

    // monitor 보호용 mutex 주소 저장하기
    std::mutex* pCS_thrd_mon;

    // Priority Queue 주소 저장하기
    GenericHeapPrioQ_KV<int, Event>* pPrioQ_Event;

    // 파일 출력 객체 저장하기
    FILE* fout;

    // 스레드 역할 저장하기
    ROLE role;

    // 스레드 주소 저장하기
    int myAddr;

    // 최대 반복 횟수 저장하기
    int maxRound;

    // 목표 생성 Event 개수 저장하기
    int targetEventGen;

    // 성능 측정용 주파수 저장하기
    LARGE_INTEGER QP_freq;

    // 모니터링 구조체 주소 저장하기
    ThreadStatusMonitor* pThrdMon;

} ThreadParam_Event;

// Event 처리 스레드 함수 선언하기
void EventProc(ThreadParam_Event* pParam);

// Event 생성 스레드 함수 선언하기
void EventGen(ThreadParam_Event* pParam);

#endif