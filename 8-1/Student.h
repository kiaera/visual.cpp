/*
Student.h
project : Student 클래스를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// CLASS_STUDENT_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_STUDENT_H

// CLASS_STUDENT_H 매크로 정의하기
#define CLASS_STUDENT_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 클래스를 사용하기 위한 헤더파일
#include <string>

// Person 클래스를 사용하기 위한 헤더파일
#include "Person.h"

// 학생 정렬 기준 열거형 선언하기
enum ST_ATTR
{
    NAME,
    ADDR,
    STID,
    MAJOR,
    STGPA
};

// 정렬 방식 열거형 선언하기
enum SORT_ORDER
{
    INCR,
    DECR
};

// StudentDB 클래스 미리 선언하기
class StudentDB;

// Student 클래스 선언하기
class Student : public Person
{
    // 입력 연산자 함수 friend 선언하기
    friend std::istream& operator>>(std::istream& fin, Student& s);

    // 출력 연산자 함수 friend 선언하기
    friend std::ostream& operator<<(std::ostream& fout, const Student& s);

    // StudentDB 클래스의 접근 허용하기
    friend class StudentDB;

public:
    // 기본 생성자 선언하기
    Student();

    // 생성자 선언하기
    Student(std::string name,
        std::string addr,
        int stID,
        std::string major,
        double GPA);

    // 소멸자 선언하기
    ~Student();

    // 학생 비교 함수 선언하기
    int Compare_Student(const Student& other,
        ST_ATTR stAttr,
        SORT_ORDER order) const;

private:
    // 학번 저장 변수 선언하기
    int stID;

    // 전공 저장 변수 선언하기
    std::string major;

    // GPA 저장 변수 선언하기
    double GPA;
};

#endif