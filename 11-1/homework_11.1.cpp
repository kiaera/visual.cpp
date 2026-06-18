/*
main.cpp
project : DLL template class를 이용하여 이중 연결 리스트의 정렬 삽입과 삭제 기능을 시험하는 프로그램
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

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

int main()
{
    // int형 이중 연결 리스트 객체 생성하기
    DLL<int> DLL_Int("DLL_Int");

    // 삽입할 정수 배열 선언하기
    int intArray[] = { 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

    // 데이터 개수 계산하기
    int num_data = sizeof(intArray) / sizeof(int);

    // 초기 상태 출력하기
    cout << "Initial status (before enQueues :: " << DLL_Int << endl;

    // 오름차순 삽입 기능 시험하기
    for (int i = 0; i < num_data; i++)
    {
        DLL_Int.insertInOrder(&intArray[i]);
        cout << "After enQueue(" << intArray[i] << ") : ";
        cout << DLL_Int;
    }

    cout << endl;

    // 맨 앞 원소 삭제 기능 시험하기
    for (int i = 0; i < num_data; i++)
    {
        DLL_Int.removeFront();
        cout << "After removeFront() : ";
        cout << DLL_Int;
    }

    return 0;
}