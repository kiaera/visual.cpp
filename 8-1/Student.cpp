/*
Student.cpp
project : Student 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// Student 클래스를 사용하기 위한 헤더파일
#include "Student.h"

// 출력 정렬을 사용하기 위한 헤더파일
#include <iomanip>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 기본 생성자 정의하기
Student::Student() : Person()
{
    // 학번 초기화하기
    stID = 0;

    // 전공 초기화하기
    major = "";

    // GPA 초기화하기
    GPA = 0.0;
}

// 생성자 정의하기
Student::Student(string name, string addr, int stID, string major, double GPA)
    : Person(name, addr)
{
    // 전달받은 학번 저장하기
    this->stID = stID;

    // 전달받은 전공 저장하기
    this->major = major;

    // 전달받은 GPA 저장하기
    this->GPA = GPA;
}

// 소멸자 정의하기
Student::~Student()
{}

// 학생 비교 함수 정의하기
int Student::Compare_Student(const Student& other, ST_ATTR stAttr, SORT_ORDER order) const
{
    // 비교 결과 저장 변수 선언하기
    int result = 0;

    // 이름 기준으로 비교하기
    if (stAttr == NAME)
        result = name.compare(other.name);

    // 주소 기준으로 비교하기
    else if (stAttr == ADDR)
        result = addr.compare(other.addr);

    // 학번 기준으로 비교하기
    else if (stAttr == STID)
        result = stID - other.stID;

    // 전공 기준으로 비교하기
    else if (stAttr == MAJOR)
        result = major.compare(other.major);

    // GPA 기준으로 비교하기
    else if (stAttr == STGPA)
    {
        // 현재 학생의 GPA가 더 큰 경우
        if (GPA > other.GPA)
            result = 1;

        // 현재 학생의 GPA가 더 작은 경우
        else if (GPA < other.GPA)
            result = -1;

        // 두 학생의 GPA가 같은 경우
        else
            result = 0;
    }

    // 내림차순 정렬이면 비교 결과 반대로 바꾸기
    if (order == DECR)
        result = -result;

    // 비교 결과 반환하기
    return result;
}

// 입력 연산자 함수 정의하기
istream& operator>>(istream& fin, Student& s)
{
    // 학생의 이름, 주소, 학번, 전공, GPA 입력받기
    fin >> s.name >> s.addr >> s.stID >> s.major >> s.GPA;

    // 입력 스트림 반환하기
    return fin;
}

// 출력 연산자 함수 정의하기
ostream& operator<<(ostream& fout, const Student& s)
{
    // 학생 정보를 지정된 형식으로 출력하기
    fout << "Student("
        << setw(10) << s.name << ", "
        << setw(10) << s.addr << ", "
        << setw(4) << s.stID << ", "
        << setw(10) << s.major << ", "
        << fixed << setprecision(2) << setw(4) << s.GPA << ")";

    // 출력 스트림 반환하기
    return fout;
}