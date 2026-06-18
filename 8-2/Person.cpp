/*
Person.cpp
project : Person 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// Person 클래스를 사용하기 위한 헤더파일
#include "Person.h"

// 기본 생성자
Person::Person()
{
    // 이름 초기화하기
    name = "";

    // 거주 도시 초기화하기
    city = "";
}

// 이름과 거주 도시를 초기화하는 생성자
Person::Person(const std::string name,
    const std::string city)
{
    // 이름 저장하기
    this->name = name;

    // 거주 도시 저장하기
    this->city = city;
}

// 소멸자
Person::~Person()
{}

// Person 객체 입력하기
std::istream& operator>>(std::istream& in, Person& p)
{
    // 이름 입력받기
    in >> p.name;

    // 거주 도시 입력받기
    in >> p.city;

    // 입력 스트림 반환하기
    return in;
}

// Person 객체 출력하기
std::ostream& operator<<(std::ostream& out, const Person& p)
{
    // 이름 출력하기
    out << p.name;

    // 거주 도시 출력하기
    out << ", " << p.city;

    // 출력 스트림 반환하기
    return out;
}