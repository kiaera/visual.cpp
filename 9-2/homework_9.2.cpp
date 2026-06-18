/*
main_GenericCirQ.cpp
project : GenericCirQ template class를 이용하여 환형 큐의 enqueue, dequeue 기능을 시험하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// GenericCirQ template class를 사용하기 위한 헤더파일
#include "GenericCirQ.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 한 번에 enqueue/dequeue 할 원소 개수 정의하기
#define NUM_ELEMENTS_PER_ROUND 7

// 환형 큐의 최대 크기 정의하기
#define QUEUE_CAPACITY 10

/*
GenericCirQ template class의 enqueue, dequeue 기능 시험하기
int형 데이터를 환형 큐에 삽입하고 제거하면서 상태 출력하기
*/
int main()
{
    // int형 환형 큐 객체 생성하기
    GenericCirQ<int> genericIntCirQ("GenericIntCirQ", QUEUE_CAPACITY);

    // 삽입할 데이터 저장 변수 선언하기
    int data = 0;

    // dequeue된 데이터 주소 저장 포인터 선언하기
    int* pE;

    // enqueue/dequeue 과정 4번 반복하기
    for (int j = 0; j < 4; j++)
    {
        // 환형 큐에 데이터 삽입하기
        for (int i = 0; i < NUM_ELEMENTS_PER_ROUND; i++)
        {
            // enqueue 수행 전 출력하기
            cout << "EnCirQ (" << setw(3) << data << ") => ";

            // 데이터 삽입하기
            genericIntCirQ.enqueue(data);

            // 현재 환형 큐 상태 출력하기
            cout << genericIntCirQ;

            // 다음 데이터 값 증가시키기
            data++;
        }

        // 환형 큐에서 데이터 제거하기
        for (int i = 0; i < NUM_ELEMENTS_PER_ROUND; i++)
        {
            // dequeue 문구 출력하기
            cout << "DeCirQ (";

            // 환형 큐의 front 데이터 제거하기
            pE = genericIntCirQ.dequeue();

            // 제거된 데이터 출력하기
            cout << setw(3) << *pE << ") => ";

            // 현재 환형 큐 상태 출력하기
            cout << genericIntCirQ;
        }
    }

    return 0;
}