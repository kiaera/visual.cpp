/*
Student.h
project : 학생 정보와 우선순위 비교 기능을 구현한 Student class와 StudentCompare class를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

// STUDENT_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef STUDENT_H

// STUDENT_H 매크로 정의하기
#define STUDENT_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 비교 기준 속성 열거형 정의하기
enum class KeyAttr
{
    NAME,
    STID,
    GPA
};

// 정렬 방식 열거형 정의하기
enum class SortOrder
{
    ASC,
    DESC
};

// 학생 정보를 저장하는 클래스
class Student
{
public:
    // 기본 생성자
    Student()
    {
        name = "";
        stID = 0;
        GPA = 0.0;
    }

    // 생성자
    Student(string name, int stID, double GPA)
    {
        this->name = name;
        this->stID = stID;
        this->GPA = GPA;
    }

    // 학생 정보 출력 함수
    void print() const
    {
        cout << left
            << setw(12) << name
            << setw(10) << stID
            << fixed << setprecision(2)
            << GPA << endl;
    }

    // 이름 반환 함수
    string Get_Name() const
    {
        return name;
    }

    // 학번 반환 함수
    int Get_St_ID() const
    {
        return stID;
    }

    // GPA 반환 함수
    double Get_GPA() const
    {
        return GPA;
    }

private:
    // 학생 이름 저장하기
    string name;

    // 학번 저장하기
    int stID;

    // GPA 저장하기
    double GPA;
};

// 우선순위 비교 클래스
class StudentCompare
{
public:
    // 생성자
    StudentCompare(KeyAttr keyAttr, SortOrder order)
    {
        this->keyAttr = keyAttr;
        this->order = order;
    }

    // 우선순위 비교 함수
    bool operator()(const Student& s1, const Student& s2) const
    {
        // 이름 기준 비교하기
        if (keyAttr == KeyAttr::NAME)
        {
            if (order == SortOrder::ASC)
                return s1.Get_Name() > s2.Get_Name();
            else
                return s1.Get_Name() < s2.Get_Name();
        }

        // 학번 기준 비교하기
        else if (keyAttr == KeyAttr::STID)
        {
            if (order == SortOrder::ASC)
                return s1.Get_St_ID() > s2.Get_St_ID();
            else
                return s1.Get_St_ID() < s2.Get_St_ID();
        }

        // GPA 기준 비교하기
        else
        {
            if (order == SortOrder::ASC)
                return s1.Get_GPA() > s2.Get_GPA();
            else
                return s1.Get_GPA() < s2.Get_GPA();
        }
    }

private:
    // 비교 기준 속성 저장하기
    KeyAttr keyAttr;

    // 정렬 방식 저장하기
    SortOrder order;
};

// STUDENT_H 끝내기
#endif