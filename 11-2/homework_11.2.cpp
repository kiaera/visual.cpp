/*
main.cpp
project : DLL_Queue template class를 이용하여 문자열 FIFO Queue의 enqueue와 dequeue 기능을 시험하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// DLL template class를 사용하기 위한 헤더파일
#include "DLL.h"

// DLL_Queue template class를 사용하기 위한 헤더파일
#include "DLL_Queue.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 문자열 데이터 개수 정의하기
#define NUM_DATA 10

/*
DLL_Queue template class를 이용하여 
문자열 FIFO Queue의 enqueue와 dequeue 기능을 시험하는 메인 함수
*/
int main()
{
    // string형 DLL Queue 객체 생성하기
    DLL_Queue<string> DLL_Queue_Str("DLL_Queue_String");

    // Queue에 삽입할 문자열 배열 선언하기
    string strArray[NUM_DATA] = {
        "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine", "ten"
    };

    // deQueue된 원소 주소를 저장할 포인터 선언하기
    string* pE;

    // 초기 상태 출력하기
    cout << "Initial status (before enQueues :: " << DLL_Queue_Str << endl;

    // enqueue와 dequeue 과정을 3번 반복하기
    for (int round = 0; round < 3; round++)
    {
        // DLL 기반 FIFO Queue의 enqueue 기능 시험하기
        for (int i = 0; i < NUM_DATA; i++)
        {
            DLL_Queue_Str.enQueue(&strArray[i]);
            cout << "After enQueue(" << setw(6) << strArray[i] << ") : ";
            cout << DLL_Queue_Str;
        }

        // DLL 기반 FIFO Queue의 dequeue 기능 시험하기
        for (int i = 0; i < NUM_DATA; i++)
        {
            pE = DLL_Queue_Str.deQueue();
            cout << "After deQueue(" << setw(6) << *pE << ") : ";
            cout << DLL_Queue_Str;
        }

        cout << endl;
    }

    return 0;
}