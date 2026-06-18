/*
main.cpp
project : Regular Expression을 사용하여 학생 정보를 입력받고 hash value를 계산하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// 파일 입출력을 사용하기 위한 헤더파일
#include <fstream>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// Student class를 사용하기 위한 헤더파일
#include "Student.h"

// 4비트 hash value의 범위 정의하기
#define MAX_HASH_4BIT 16

// 8비트 hash value의 범위 정의하기
#define MAX_HASH_8BIT 256

/*
Regular Expression을 사용하여 
학생 정보를 입력받고 hash value를 계산하는 메인 함수
*/
int main()
{
    // 입력 파일 이름 저장하기
    const std::string fileName = "Students_data.txt";

    // 최대 학생 수 저장하기
    const int MAX_STUDENTS = 100;

    // 학생 객체 배열 선언하기
    Student students[MAX_STUDENTS];

    // 입력받은 학생 수 저장하기
    int numStudents = 0;

    // 4비트 hash value 저장 변수 선언하기
    std::size_t hash_value_4;

    // 8비트 hash value 저장 변수 선언하기
    std::size_t hash_value_8;

    // 입력 파일 열기
    std::ifstream fin(fileName);

    // 파일 열기에 실패한 경우 오류 메시지 출력하기
    if (!fin) {
        std::cerr << "File open error: " << fileName << std::endl;
        return 1;
    }

    // 파일에서 학생 정보 입력받기
    while (numStudents < MAX_STUDENTS && (fin >> students[numStudents])) {
        ++numStudents;
    }

    // 파일 끝이 아닌데 입력이 실패한 경우 오류 메시지 출력하기
    if (!fin.eof()) {
        std::cerr << "Input format error while reading student data." << std::endl;
        return 1;
    }

    // 입력 학생 수 출력하기
    std::cout << "Number of input students: " << numStudents << "\n\n";

    // 출력 제목 출력하기
    std::cout << std::left
        << std::setw(10) << "StID"
        << std::setw(20) << "Name"
        << std::setw(16) << "Telephone"
        << std::setw(24) << "E-mail"
        << std::setw(20) << "Address"
        << std::setw(16) << "HashValue(4bit)"
        << std::setw(16) << "HashValue(8bit)"
        << std::endl;

    // 구분선 출력하기
    std::cout << std::string(120, '-') << std::endl;

    // 학생 정보와 hash value 출력하기
    for (int i = 0; i < numStudents; ++i) {
        // 학생 정보의 hash code 계산하기
        std::size_t hashCode = students[i].getHashCode();

        // 4비트 hash value 계산하기
        hash_value_4 = hashCode % MAX_HASH_4BIT;

        // 8비트 hash value 계산하기
        hash_value_8 = hashCode % MAX_HASH_8BIT;

        // 학생 정보 출력하기
        std::cout << students[i] << " ";

        // hash value 출력하기
        std::cout << std::setw(16) << hash_value_4
            << std::setw(16) << hash_value_8
            << std::endl;
    }

    // 구분선 출력하기
    std::cout << std::string(120, '-') << std::endl;

    return 0;
}