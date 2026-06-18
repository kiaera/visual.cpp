/*
main.cpp
project : Red Black Tree의 자동 re-balancing 기능을 확인하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 29, 2026
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

/*
Red Black Tree의 자동 re-balancing 기능을 확인하는 메인 함수
*/
int main() {

    // 레드블랙트리에 넣을 숫자들 선언하기
    int entryData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                        11, 12, 13, 14, 15, 16 };
    int num_data = sizeof(entryData) / sizeof(int);
    int data;
    RBTree<int> intRBT;

    for (int i = 0; i < num_data; i++) {
        data = entryData[i];
        cout << "inserting " << data << " into intRBT" << endl;
        intRBT.insert(data);
        intRBT.printRBT();
    }

    cout << "intRBT inorder : ";
    intRBT.inorderPrint();

    return 0;
}

