/*
simple_threads_MABC.cpp
project :
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

/*
multi thread를 이용하여 A, B, C, M 문자를
병렬 출력하는 메인 함수
*/
void main()
{
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

        // 스레드 생성하기
        simThrds[i] = std::thread(simple_Thread, &thrdParams[i]);

        // 스레드 ID 저장하기
        threadIDs[i] = simThrds[i].get_id();

        // 스레드 생성 메시지 출력하기
        std::cout << "main() : Thread (" << thrdParams[i].name;

        std::cout << ", id: " << threadIDs[i];

        std::cout << ") is successfully created, now !!" << std::endl;
    }

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

    // main 스레드에서 M 문자 출력 반복하기
    for (int i = 0; i < 10; i++)
    {
        // mainThread 이름 출력하기
        std::cout << "mainThrd : ";

        // M 문자 50개 출력하기
        for (int j = 0; j < 50; j++)
        {
            std::cout << 'M';
        }

        // 줄바꿈 출력하기
        std::cout << std::endl;

        // 잠시 대기하기
        Sleep(10);
    }

    // 모든 스레드 종료될 때까지 대기하기
    for (int i = 0; i < NUM_THREADS; i++)
    {
        simThrds[i].join();
    }

    // 종료 메시지 출력하기
    std::cout << "main() :: threads (";

    // 스레드 ID 출력 반복하기
    for (int i = 0; i < NUM_THREADS; i++)
    {
        std::cout << threadIDs[i] << ", ";
    }

    // 종료 완료 메시지 출력하기
    std::cout << ") are terminated, now." << std::endl;
}