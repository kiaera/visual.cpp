
/*
simple_threads_MABC.cpp
project : mutex와 turn을 이용하여 M, A, B, C 순서로 숫자를 출력하는 메인 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 22, 2026
*/

#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <Windows.h>
#include "Multi_Thread.h"

std::mutex mtx_counter;
std::mutex mtx_console;
int g_turn = 0; // 메인 스레드M(0)부터 순환 시작


/*
mutex와 turn을 이용하여 M, A, B, C 순서로 숫자를 출력하는 메인 함수
*/
void main()
{
    // 각 스레드가 자신만의 독립된 값을 유지할 수 있도록 개별 카운터 변수 선언
    int main_counter = 0;
    int thrd_counters[NUM_THREADS] = { 0, 0, 0 };
    int main_round = 0;

    std::thread simThrds[NUM_THREADS];
    ThreadParam params[NUM_THREADS];
    std::string names[NUM_THREADS] = { "Thread_A", "Thread_B", "Thread_C" };
    int increments[NUM_THREADS] = { 3, 6, 10 };

    // 자식 스레드 생성 및 매개변수 설정
    for (int i = 0; i < NUM_THREADS; i++) {
        params[i].threadName = names[i];
        params[i].threadId = i + 1; 
        params[i].pCounter = &thrd_counters[i]; 
        params[i].incr = increments[i];

        simThrds[i] = std::thread(simpleThread, &params[i]);
    }

    // M -> A -> B -> C 전체 순환 루프 시작
    while (true)
    {
        // 1. 메인 스레드 차례가 올 때까지 대기
        while (true) {
            mtx_counter.lock();
            if (g_turn == 0) {
                mtx_counter.unlock();
                break;
            }
            mtx_counter.unlock();
            Sleep(1);
        }

        // 2. 메인 스레드 계산: 0회차는 1, 1회차부터는 본인 이전 값 + 10
        mtx_counter.lock();
        if (main_round == 0) {
            main_counter = 1;
        }
        else {
            main_counter += 10;
        }
        int current_counter = main_counter;
        mtx_counter.unlock();

        // 3. 출력
        mtx_console.lock();
        std::cout << std::left << std::setw(15) << "mainThreadM"
            << "round (" << main_round << ") "
            << "increment 1, "
            << "counter = " << current_counter << std::endl;
        mtx_console.unlock();

        main_round++;

        // 4. 차례를 Thread_A(1)에게 넘김
        mtx_counter.lock();
        g_turn = 1;
        mtx_counter.unlock();

        // 만약 C 스레드까지 돌아서 최종 100에 도달했다면 메인 루프 탈출
        mtx_counter.lock();
        if (thrd_counters[2] >= 90) {
            mtx_counter.unlock();
            break;
        }
        mtx_counter.unlock();
    }

    // 모든 자식 스레드가 안전하게 퇴근할 때까지 조인
    for (int i = 0; i < NUM_THREADS; i++) {
        if (simThrds[i].joinable()) {
            simThrds[i].join();
        }
    }

}
