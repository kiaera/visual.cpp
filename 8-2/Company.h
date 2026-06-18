/*
Company.h
project : Company 클래스를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// CLASS_COMPANY_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_COMPANY_H

// CLASS_COMPANY_H 매크로 정의하기
#define CLASS_COMPANY_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// Employee 클래스를 사용하기 위한 헤더파일
#include "Employee.h"

// 회사의 사원 데이터베이스를 관리하는 클래스
class Company
{
    // Company 객체를 입력하기 위한 연산자 오버로딩 함수
    friend std::istream& operator>>(std::istream&, Company&);

    // Company 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream&, const Company&);

public:
    // 기본 생성자
    Company();

    // 회사 이름과 사원 수를 초기화하는 생성자
    Company(std::string db_name, int num_entries);

    // 동적 할당된 사원 배열을 해제하는 소멸자
    ~Company();

    // 지정된 속성과 정렬 순서에 따라 사원 정렬하는 함수
    void Sort_Employees(EMP_ATTR attr, SORT_ORDER sort_order);

private:
    // 데이터베이스 이름 저장하기
    std::string db_name;

    // 전체 사원 수 저장하기
    int num_entries;

    // 사원 정보를 저장하는 동적 배열 포인터
    Employee* employees;
};

// 헤더파일 중복 포함 종료하기
#endif