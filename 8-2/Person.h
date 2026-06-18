/*
Person.h
project : Person 클래스를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// CLASS_PERSON_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_PERSON_H

// CLASS_PERSON_H 매크로 정의하기
#define CLASS_PERSON_H

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 입출력 스트림을 사용하기 위한 헤더파일
#include <iostream>

// 사람의 기본 정보를 저장하는 클래스
class Person
{
    // Person 객체를 입력하기 위한 연산자 오버로딩 함수
    friend std::istream& operator>>(std::istream&, Person&);

    // Person 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream&, const Person&);

public:
    // 기본 생성자
    Person();

    // 이름과 거주 도시를 초기화하는 생성자
    Person(const std::string name,
        const std::string city);

    // 소멸자
    ~Person();

protected:
    // 이름 저장하기
    std::string name;

    // 거주 도시 저장하기
    std::string city;
};

// 헤더파일 중복 포함 종료하기
#endif