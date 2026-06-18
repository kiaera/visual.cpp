/*
Employee.h
project : Employee 클래스를 선언한 헤더파일 및 정렬 관련 열거형을 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// CLASS_EMPLOYEE_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_EMPLOYEE_H

// CLASS_EMPLOYEE_H 매크로 정의하기
#define CLASS_EMPLOYEE_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// Person 클래스를 상속받기 위한 헤더파일
#include "Person.h"

// 정렬 기준 속성을 나타내는 열거형
enum EMP_ATTR
{
    NAME,
    ADDR,
    EMPID,
    DEPT,
    SALARY
};

// 정렬 순서를 나타내는 열거형
enum SORT_ORDER
{
    INCR,
    DECR
};

// Company 클래스 전방 선언하기
class Company;

// 사원 정보를 저장하는 클래스
class Employee : public Person
{
    // Employee 객체를 입력하기 위한 연산자 오버로딩 함수
    friend std::istream& operator>>(std::istream&, Employee&);

    // Employee 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream&, const Employee&);

    // Company 클래스에서 private 멤버에 접근할 수 있도록 선언하기
    friend class Company;

public:
    // 기본 생성자
    Employee();

    // 사원 정보를 초기화하는 생성자
    Employee(std::string name,
        std::string city,
        int empID,
        std::string department,
        double salary);

    // 소멸자
    ~Employee();

    // 지정된 속성과 정렬 순서에 따라 사원 비교하는 함수
    int Compare_Employee(const Employee& other,
        EMP_ATTR empAttr,
        SORT_ORDER order) const;

private:
    // 사번 저장하기
    int empID;

    // 근무 부서 저장하기
    std::string department;

    // 연봉 저장하기
    double salary;
};

// 헤더파일 중복 포함 종료하기
#endif