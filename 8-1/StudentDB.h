/*
StudentDB.h
project : StudentDB 클래스를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// CLASS_STUDENT_DB_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_STUDENT_DB_H

// CLASS_STUDENT_DB_H 매크로 정의하기
#define CLASS_STUDENT_DB_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 클래스를 사용하기 위한 헤더파일
#include <string>

// Student 클래스를 사용하기 위한 헤더파일
#include "Student.h"

// StudentDB 클래스 선언하기
class StudentDB
{
    // 입력 연산자 함수 friend 선언하기
    friend std::istream& operator>>(std::istream& fin, StudentDB& db);

    // 출력 연산자 함수 friend 선언하기
    friend std::ostream& operator<<(std::ostream& fout, const StudentDB& db);

public:
    // 기본 생성자 선언하기
    StudentDB();

    // 생성자 선언하기
    StudentDB(std::string db_name, int num_entries);

    // 소멸자 선언하기
    ~StudentDB();

    // 학생 정렬 함수 선언하기
    void Sort_Students(ST_ATTR attr, SORT_ORDER sort_order);

private:
    // 데이터베이스 이름 저장 변수 선언하기
    std::string db_name;

    // 학생 수 저장 변수 선언하기
    int num_entries;

    // Student 객체 배열 포인터 선언하기
    Student* students;
};

#endif