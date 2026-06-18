/*
Person.h
project : Person 클래스와 PersonLess 클래스 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// PERSON_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef PERSON_H
// PERSON_H 매크로 정의하기
#define PERSON_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 사람의 나이와 이름을 저장하는 클래스 선언하기
class Person
{
    // Person 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream& fout, const Person& p)
    {
        fout << "(" << p.age << ", " << p.name << ")";
        return fout;
    }

public:
    // 기본 생성자
    Person()
        : age(0), name("")
    {}

    // 나이와 이름을 초기화하는 생성자
    Person(int age, std::string nm)
        : age(age), name(nm)
    {}

    // 소멸자
    ~Person()
    {}

    // 나이 반환하기
    int getAge() const
    {
        return age;
    }

    // 이름 반환하기
    std::string getName() const
    {
        return name;
    }

private:
    // 나이 저장하기
    int age;

    // 이름 저장하기
    std::string name;
};

// Person 객체를 나이 기준으로 비교하는 클래스 선언하기
class PersonLess
{
public:
    // p1의 나이가 p2의 나이보다 작은지 비교하기
    bool operator()(const Person& p1, const Person& p2) const
    {
        return p1.getAge() < p2.getAge();
    }
};

#endif