/*
Multi_Thread.h
project : mutex와 turn을 이용하여 M, A, B, C 순서로 문자열을 출력하는 프로그램의 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// MULTI_THREAD_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef MULTI_THREAD_H

// MULTI_THREAD_H 매크로 정의하기
#define MULTI_THREAD_H

// thread 클래스를 사용하기 위한 헤더파일
#include <thread>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 생성할 스레드 개수 정의하기
#define NUM_THREADS 3

// 스레드에 전달할 데이터를 저장하는 구조체
typedef struct
{
    // 스레드 이름 저장하기
    std::string name;

    // 출력할 문자 저장하기
    char myMark;

    // 콘솔 출력을 보호할 mutex 주소 저장하기
    std::mutex* pMtxConsole;

    // 실행 순서를 제어할 turn 주소 저장하기
    char* pTurn;

} ThreadParam;

// 단순 스레드 함수 선언하기
void simpleThread(ThreadParam* pThrdParam);

#endif