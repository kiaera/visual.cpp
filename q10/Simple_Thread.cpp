/*
Simple_Thread.cpp
project : simpleThread 함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 22, 2026
*/

/* Simple_Thread.cpp */
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Multi_Thread.h"

void simpleThread(ThreadParam* pThrdParam)
{
    int round_count = 0;

    while (true)
    {
        // 1. 내 차례가 올 때까지 대기
        while (true) {
            mtx_counter.lock();
            // 공유 상태 체크나 종료 조건 확인 시 뮤텍스 보호
            if (g_turn == pThrdParam->threadId) {
                mtx_counter.unlock();
                break;
            }
            mtx_counter.unlock();
            Sleep(1);
        }

        // 2. 값 계산: 0회차는 초기 고유값 세팅, 1회차부터는 본인 값 + 10
        mtx_counter.lock();
        if (round_count == 0) {
            *(pThrdParam->pCounter) = pThrdParam->incr; // A=3, B=6, C=10 초기화
        }
        else {
            *(pThrdParam->pCounter) += 10; // 이후 회차는 본인 값에 10씩 누적
        }
        int current_counter = *(pThrdParam->pCounter);
        mtx_counter.unlock();

        // 출력하기
        mtx_console.lock();
        std::cout << std::left << std::setw(15) << pThrdParam->threadName
            << "round (" << round_count << ") "
            << "increment " << pThrdParam->incr << ", "
            << "pCounter = " << current_counter << std::endl;
        mtx_console.unlock();

        round_count++;

        // 다음 스레드로 전달 (M(0) -> A(1) -> B(2) -> C(3) -> M(0))
        mtx_counter.lock();
        g_turn = (g_turn + 1) % 4;
        mtx_counter.unlock();

        // 최종 목표인 100에 도달하면 스레드 종료
        if (current_counter >= 91) return;
    }
}