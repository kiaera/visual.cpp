/*
Person.cpp
project : Person 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// Person 클래스를 사용하기 위한 헤더파일
#include "Person.h"

// 기본 생성자 정의하기
Person::Person()
{
    // 이름 초기화하기
    name = "";

    // 주소 초기화하기
    addr = "";
}

// 생성자 정의하기
Person::Person(const std::string name, const std::string addr)
{
    // 전달받은 이름 저장하기
    this->name = name;

    // 전달받은 주소 저장하기
    this->addr = addr;
}

// 소멸자 정의하기
Person::~Person()
{}

// 입력 연산자 함수 정의하기
std::istream& operator>>(std::istream& fin, Person& p)
{
    // 이름과 주소 입력받기
    fin >> p.name >> p.addr;

    // 입력 스트림 반환하기
    return fin;
}
// 출력 연산자 함수 정의하기
std::ostream& operator<<(std::ostream& fout, const Person& p)
{
    // 이름과 주소 출력하기
    fout << p.name << ", " << p.addr;

    // 출력 스트림 반환하기
    return fout;
}