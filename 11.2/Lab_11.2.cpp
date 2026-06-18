/*
main.cpp
project : Red Black Tree의 자동 re-balancing 기능을 확인하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// less 비교 함수를 사용하기 위한 헤더파일
#include <functional>

// RBTree template class를 사용하기 위한 헤더파일
#include "RBT.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

int main()
{
    // Red Black Tree에 삽입할 정수 데이터 배열 선언하기
    int entryData[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16
    };

    // 데이터 개수 계산하기
    int num_data = sizeof(entryData) / sizeof(int);

    // 현재 삽입 또는 삭제할 데이터 저장하기
    int data;

    // int형 Red Black Tree 객체 생성하기
    RBTree<int> intRBT;

    // 데이터 삽입하면서 re-balancing 결과 출력하기
    for (int i = 0; i < num_data; i++)
    {
        data = entryData[i];

        cout << "inserting " << data << " into intRBT" << endl;
        intRBT.insert(data);
        intRBT.printRBT();
    }

    // 중위 순회 결과 출력하기
    cout << "intRBT inorder : ";
    intRBT.inorderPrint();

    cout << "\n===========================\n";
    cout << "Testing erases of RBT .....\n";

    // 데이터 삭제하면서 re-balancing 결과 출력하기
    for (int i = 0; i < num_data; i++)
    {
        data = entryData[i];

        intRBT.erase(data);
        cout << "After erase (" << data << ")\n";
        intRBT.printRBT();
        cout << endl;
    }

    return 0;
}