/*
main.cpp
project : student_DB.txt 파일에서 학생 정보를 입력받아 정렬 기준에 따라 StudentDB를 정렬하고 콘솔 및 파일로 출력하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력을 사용하기 위한 헤더파일
#include <fstream>

// 문자열 클래스를 사용하기 위한 헤더파일
#include <string>

// StudentDB 클래스를 사용하기 위한 헤더파일
#include "StudentDB.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 메인 함수 정의하기
int main()
{
    // 입력 파일 이름 저장하기
    string input_data_file = "student_DB.txt";

    // 출력 파일 이름 저장하기
    string output_file = "output.txt";

    // 입력 파일 객체 선언하기
    ifstream fin;

    // 출력 파일 객체 선언하기
    ofstream fout;

    // StudentDB 객체 선언하기
    StudentDB stDB;

    // 입력 파일 열기
    fin.open(input_data_file);

    // 파일 열기 실패 여부 확인하기
    if (fin.fail())
    {
        // 파일 열기 실패 메시지 출력하기
        cout << "Fail to open input data file ("
            << input_data_file << ") !!!!" << endl;

        // 프로그램 비정상 종료하기
        exit(1);
    }

    // 파일 입력 시작 메시지 출력하기
    cout << "File input from " << input_data_file << " . . . . " << endl;

    // StudentDB 정보 입력받기
    fin >> stDB;

    // 입력 파일 닫기
    fin.close();

    // 출력 파일 열기
    fout.open(output_file);

    // 초기 StudentDB 상태 출력하기
    cout << endl << "Initial state of StudentDB : " << endl;
    cout << stDB;

    // 초기 StudentDB 상태 파일에 출력하기
    fout << endl << "Initial state of StudentDB : " << endl;
    fout << stDB;

    // 이름 기준 오름차순 정렬 메시지 출력하기
    cout << endl
        << "Sorted StudentDB (keyAttr = NAME, sort_order = INCR) : "
        << endl;

    // 이름 기준 오름차순 정렬 수행하기
    stDB.Sort_Students(NAME, INCR);

    // 이름 기준 정렬 결과 출력하기
    cout << stDB;

    // 이름 기준 정렬 결과 파일에 출력하기
    fout << endl
        << "Sorted StudentDB (keyAttr = NAME, sort_order = INCR) : "
        << endl;

    fout << stDB;

    // GPA 기준 내림차순 정렬 메시지 출력하기
    cout << endl
        << "Sorted StudentDB (keyAttr = GPA, sort_order = DECR) : "
        << endl;

    // GPA 기준 내림차순 정렬 수행하기
    stDB.Sort_Students(STGPA, DECR);

    // GPA 기준 정렬 결과 출력하기
    cout << stDB;

    // GPA 기준 정렬 결과 파일에 출력하기
    fout << endl
        << "Sorted StudentDB (keyAttr = GPA, sort_order = DECR) : "
        << endl;

    fout << stDB;

    // 학번 기준 오름차순 정렬 메시지 출력하기
    cout << endl
        << "Sorted StudentDB (keyAttr = STID, sort_order = INCR) : "
        << endl;

    // 학번 기준 오름차순 정렬 수행하기
    stDB.Sort_Students(STID, INCR);

    // 학번 기준 정렬 결과 출력하기
    cout << stDB;

    // 학번 기준 정렬 결과 파일에 출력하기
    fout << endl
        << "Sorted StudentDB (keyAttr = STID, sort_order = INCR) : "
        << endl;

    fout << stDB;

    // 출력 파일 닫기
    fout.close();

    // 프로그램 정상 종료하기
    return 0;
}