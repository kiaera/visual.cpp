/*
Employee.cpp
project : Employee 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// Employee 클래스를 사용하기 위한 헤더파일
#include "Employee.h"

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 기본 생성자
Employee::Employee() : Person()
{
    // 사번 초기화하기
    empID = 0;

    // 부서명 초기화하기
    department = "";

    // 연봉 초기화하기
    salary = 0;
}

// 사원 정보를 초기화하는 생성자
Employee::Employee(string name,
    string city,
    int empID,
    string department,
    double salary)
    : Person(name, city)
{
    // 사번 저장하기
    this->empID = empID;

    // 부서명 저장하기
    this->department = department;

    // 연봉 저장하기
    this->salary = salary;
}

// 소멸자
Employee::~Employee()
{}

// 지정된 속성과 정렬 순서에 따라 사원 비교하기
int Employee::Compare_Employee(const Employee& other,
    EMP_ATTR empAttr,
    SORT_ORDER order) const
{
    // 비교 결과 저장할 변수 선언하기
    int result = 0;

    // 이름 기준 비교하기
    if (empAttr == NAME)
    {
        result = name.compare(other.name);
    }

    // 거주 도시 기준 비교하기
    else if (empAttr == ADDR)
    {
        result = city.compare(other.city);
    }

    // 사번 기준 비교하기
    else if (empAttr == EMPID)
    {
        // 현재 사번이 더 큰 경우
        if (empID > other.empID)
            result = 1;

        // 현재 사번이 더 작은 경우
        else if (empID < other.empID)
            result = -1;

        // 두 사번이 같은 경우
        else
            result = 0;
    }

    // 부서 기준 비교하기
    else if (empAttr == DEPT)
    {
        result = department.compare(other.department);
    }

    // 연봉 기준 비교하기
    else if (empAttr == SALARY)
    {
        // 현재 연봉이 더 큰 경우
        if (salary > other.salary)
            result = -1;

        // 현재 연봉이 더 작은 경우
        else if (salary < other.salary)
            result = 1;

        // 연봉이 같으면 이름 기준 오름차순 비교하기
        else
            result = name.compare(other.name);

        // 비교 결과 반환하기
        return result;
    }

    // 내림차순 정렬일 경우 결과 반대로 변경하기
    if (order == DECR)
        result *= -1;

    // 비교 결과 반환하기
    return result;
}

// Employee 객체 입력하기
istream& operator>>(istream& in, Employee& e)
{
    // 이름 입력받기
    in >> e.name;

    // 거주 도시 입력받기
    in >> e.city;

    // 사번 입력받기
    in >> e.empID;

    // 부서 입력받기
    in >> e.department;

    // 연봉 입력받기
    in >> e.salary;

    // 입력 스트림 반환하기
    return in;
}

// Employee 객체 출력하기
ostream& operator<<(ostream& out, const Employee& e)
{
    // 사원 정보 출력 시작하기
    out << "Employee(";

    // 이름 출력하기
    out << setw(10) << e.name << ", ";

    // 거주 도시 출력하기
    out << setw(10) << e.city << ", ";

    // 사번 출력하기
    out << setw(4) << e.empID << ", ";

    // 부서 출력하기
    out << setw(10) << e.department << ", ";

    // 연봉 출력하기
    out << setw(4)
        << fixed
        << setprecision(0)
        << e.salary
        << ")";

    // 출력 스트림 반환하기
    return out;
}