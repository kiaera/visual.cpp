/*
Simple_Thread.cpp
project : simpleThread 함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// Sleep 함수를 사용하기 위한 헤더파일
#include <Windows.h>

// Multi_Thread 헤더파일 포함하기
#include "Multi_Thread.h"

// 단순 스레드 함수 구현하기
void simple_Thread(ThreadParam* pThrdParam)
{
    // 스레드 이름 저장하기
    std::string threadName = pThrdParam->name;

    // 출력할 문자 저장하기
    char myMark = pThrdParam->myMark;

    // 10줄 출력 반복하기
    for (int i = 0; i < 10; i++)
    {
        // 스레드 이름 출력하기
        std::cout << threadName << " : ";

        // 문자 50개 출력하기
        for (int j = 0; j < 50; j++)
        {
            std::cout << myMark;
        }

        // 줄바꿈 출력하기
        std::cout << std::endl;

        // 잠시 대기하기
        Sleep(10);
    }
}