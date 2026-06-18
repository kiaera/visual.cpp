/*
main.cpp
project : 파일로부터 사원 정보를 입력받아 정렬 기준에 따라 출력하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 프로그램 제어 함수를 사용하기 위한 헤더파일
#include <cstdlib>

// Company 클래스를 사용하기 위한 헤더파일
#include "Company.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

/*
파일로부터 회사 및 사원 정보를 입력받아
다양한 기준으로 정렬하여 출력하는 함수
*/
int main()
{
    // 입력 데이터 파일 이름 저장하기
    string input_data_file = "Employee_DB.txt";

    // 파일 입력 스트림 객체 선언하기
    ifstream fin;

    // Company 객체 생성하기
    Company company;

    // 입력 파일 열기
    fin.open(input_data_file);

    // 파일 열기 실패 여부 확인하기
    if (fin.fail())
    {
        // 파일 열기 실패 메시지 출력하기
        cout << "Fail to open input data file ("
            << input_data_file
            << ") !!!!"
            << endl;

        // 프로그램 비정상 종료하기
        exit(1);
    }

    // 파일 입력 시작 메시지 출력하기
    cout << "File input from "
        << input_data_file
        << " . . . . "
        << endl;

    // 파일로부터 회사 정보 입력받기
    fin >> company;

    // 초기 상태 출력하기
    cout << endl
        << "Initial state of Company : "
        << endl;

    // 초기 회사 정보 출력하기
    cout << company;

    // 이름 기준 오름차순 정렬 메시지 출력하기
    cout << endl
        << "Sorted Company (keyAttr = NAME, sort_order = INCR) : "
        << endl;

    // 이름 기준 오름차순 정렬하기
    company.Sort_Employees(NAME, INCR);

    // 정렬 결과 출력하기
    cout << company;

    // 연봉 기준 내림차순 정렬 메시지 출력하기
    cout << endl
        << "Sorted Company (keyAttr = salary, sort_order = DECR) : "
        << endl;

    // 연봉 기준 내림차순 정렬하기
    company.Sort_Employees(SALARY, DECR);

    // 정렬 결과 출력하기
    cout << company;

    // 사번 기준 오름차순 정렬 메시지 출력하기
    cout << endl
        << "Sorted Company (keyAttr = empID, sort_order = INCR) : "
        << endl;

    // 사번 기준 오름차순 정렬하기
    company.Sort_Employees(EMPID, INCR);

    // 정렬 결과 출력하기
    cout << company;

    // 입력 파일 닫기
    fin.close();

    // 프로그램 정상 종료하기
    return 0;
}