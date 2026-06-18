/*
Multi_Thread.h
project : mutex와 turn을 이용하여 M, A, B, C 순서로 숫자를 출력하는 프로그램의 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 22, 2026
*/

#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H

#include <iostream>
#include <mutex>
#include <string>

#define NUM_THREADS 3

// 전역 동기화 변수 및 뮤텍스
extern std::mutex mtx_counter;
extern std::mutex mtx_console;
extern int g_turn; // 0: MainM, 1: Thread_A, 2: Thread_B, 3: Thread_C

typedef struct
{
    std::string threadName;
    int threadId;           // 1: A, 2: B, 3: C
    int* pCounter;          // 각 스레드의 독립된 카운터 변수 주소
    int incr;               // 증가값 (3, 6, 10)
} ThreadParam;

void simpleThread(ThreadParam* pThrdParam);

#endif


