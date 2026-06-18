/*
Person.h
project : Person 클래스를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// CLASS_PERSON_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_PERSON_H

// CLASS_PERSON_H 매크로 정의하기
#define CLASS_PERSON_H

// 문자열 클래스를 사용하기 위한 헤더파일
#include <string>

// 표준 입출력 스트림을 사용하기 위한 헤더파일
#include <iostream>

// Person 클래스 선언하기
class Person
{
    // 입력 연산자 함수 friend 선언하기
    friend std::istream& operator>>(std::istream& fin, Person& p);

    // 출력 연산자 함수 friend 선언하기
    friend std::ostream& operator<<(std::ostream& fout, const Person& p);

public:
    // 기본 생성자 선언하기
    Person();

    // 생성자 선언하기
    Person(const std::string name, const std::string addr);

    // 소멸자 선언하기
    ~Person();

protected:
    // 이름 저장 변수 선언하기
    std::string name;

    // 주소 저장 변수 선언하기
    std::string addr;
};

#endif