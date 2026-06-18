/*
main.cpp
project : mutex와 turn을 이용하여 M, A, B, C 순서로 문자열을 출력하는 메인 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>

// thread 클래스를 사용하기 위한 헤더파일
#include <thread>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// Sleep 함수를 사용하기 위한 헤더파일
#include <Windows.h>

// ThreadParam 구조체와 simpleThread 함수를 사용하기 위한 헤더파일
#include "Multi_Thread.h"

// 메인 함수
void main()
{
    // 콘솔 출력을 보호할 mutex 객체 선언하기
    std::mutex mtx_console;

    // 실행 순서를 제어할 turn 변수 선언하기
    char turn = 'M';

    // 스레드 파라미터 배열 선언하기
    ThreadParam thrdParams[NUM_THREADS];

    // 스레드 ID 저장 배열 선언하기
    std::thread::id threadIDs[NUM_THREADS];

    // 스레드 객체 배열 선언하기
    std::thread simThrds[NUM_THREADS];

    // 스레드 생성 반복하기
    for (int i = 0; i < NUM_THREADS; i++)
    {
        // 스레드 이름 저장하기
        thrdParams[i].name = std::string("Thread_") + (char)('A' + i);

        // 출력 문자 저장하기
        thrdParams[i].myMark = 'A' + i;

        // mutex 주소 저장하기
        thrdParams[i].pMtxConsole = &mtx_console;

        // turn 주소 저장하기
        thrdParams[i].pTurn = &turn;

        // 스레드 생성하기
        simThrds[i] = std::thread(simpleThread, &thrdParams[i]);

        // 스레드 ID 저장하기
        threadIDs[i] = simThrds[i].get_id();

        // 임계구역 시작하기
        mtx_console.lock();

        // 스레드 생성 메시지 출력하기
        std::cout << "main() : Thread (" << thrdParams[i].name;
        std::cout << ", id: " << threadIDs[i];
        std::cout << ") is successfully created, now !!" << std::endl;

        // 임계구역 끝내기
        mtx_console.unlock();
    }

    // 임계구역 시작하기
    mtx_console.lock();

    // 스레드 종료 대기 메시지 출력하기
    std::cout << "main() : Waiting the threads (";

    // 스레드 ID 출력 반복하기
    for (int i = 0; i < NUM_THREADS; i++)
    {
        std::cout << threadIDs[i] << ", ";
    }

    // 안내 메시지 출력하기
    std::cout << ") to terminate by themselves ..." << std::endl;

    // 메인 스레드 작업 메시지 출력하기
    std::cout << "main() is working as a thread, now ..." << std::endl;

    // 임계구역 끝내기
    mtx_console.unlock();

    // main 스레드에서 M 문자 출력 반복하기
    for (int i = 0; i < 10; i++)
    {
        // 자기 차례가 올 때까지 반복하기
        while (true)
        {
            // 임계구역 시작하기
            mtx_console.lock();

            // main 스레드의 차례인지 확인하기
            if (turn == 'M')
            {
                // mainThread 이름 출력하기
                std::cout << "mainThrdM:: ";

                // M 문자 50개 출력하기
                for (int j = 0; j < 50; j++)
                {
                    std::cout << 'M';
                }

                // 줄바꿈 출력하기
                std::cout << std::endl;

                // 다음 순서로 turn 변경하기
                turn = 'A';

                // 임계구역 끝내기
                mtx_console.unlock();

                break;
            }

            // 임계구역 끝내기
            mtx_console.unlock();

            // 잠시 대기하기
            Sleep(1);
        }
    }

    // 모든 스레드 종료될 때까지 대기하기
    for (int i = 0; i < NUM_THREADS; i++)
    {
        simThrds[i].join();
    }

    // 임계구역 시작하기
    mtx_console.lock();

    // 종료 메시지 출력하기
    std::cout << "main() :: threads (";

    // 스레드 ID 출력 반복하기
    for (int i = 0; i < NUM_THREADS; i++)
    {
        std::cout << threadIDs[i] << ", ";
    }

    // 종료 완료 메시지 출력하기
    std::cout << ") are terminated, now." << std::endl;

    // 임계구역 끝내기
    mtx_console.unlock();
}