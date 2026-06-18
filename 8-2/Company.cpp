/*
Company.cpp
project : Company 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 3, 2026
*/

// Company 클래스를 사용하기 위한 헤더파일
#include "Company.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 기본 생성자
Company::Company()
{
    // 데이터베이스 이름 초기화하기
    db_name = "";

    // 사원 수 초기화하기
    num_entries = 0;

    // 사원 배열 포인터 초기화하기
    employees = nullptr;
}

// 회사 이름과 사원 수를 초기화하는 생성자
Company::Company(string db_name, int num_entries)
{
    // 데이터베이스 이름 저장하기
    this->db_name = db_name;

    // 사원 수 저장하기
    this->num_entries = num_entries;

    // 사원 수만큼 동적 배열 생성하기
    employees = new Employee[num_entries];
}

// 동적 할당된 사원 배열을 해제하는 소멸자
Company::~Company()
{
    // 동적 할당된 사원 배열 메모리 해제하기
    delete[] employees;
}

// 지정된 속성과 정렬 순서에 따라 사원 정렬하기
void Company::Sort_Employees(EMP_ATTR attr, SORT_ORDER sort_order)
{
    // 선택 정렬 방식으로 사원 정렬하기
    for (int i = 0; i < num_entries - 1; i++)
    {
        // 현재 위치를 기준 인덱스로 설정하기
        int selected = i;

        // 남은 사원 중 정렬 기준에 맞는 사원 찾기
        for (int j = i + 1; j < num_entries; j++)
        {
            // 비교 결과가 더 앞에 와야 하면 선택 인덱스 바꾸기
            if (employees[j].Compare_Employee(employees[selected], attr, sort_order) < 0)
                selected = j;
        }

        // 필요한 경우 두 사원 위치 바꾸기
        if (selected != i)
        {
            // 임시 객체에 현재 사원 저장하기
            Employee temp = employees[i];

            // 선택된 사원을 현재 위치로 이동하기
            employees[i] = employees[selected];

            // 임시 객체의 사원을 선택된 위치로 이동하기
            employees[selected] = temp;
        }
    }
}

// Company 객체 입력하기
istream& operator>>(istream& in, Company& company)
{
    // 회사 이름과 사원 수 입력받기
    in >> company.db_name >> company.num_entries;

    // 파일 입력 정보 출력하기
    cout << "File input : DB-name ("
        << company.db_name
        << "); num_Employees ("
        << company.num_entries
        << ")"
        << endl;

    // 기존 배열 메모리 해제하기
    delete[] company.employees;

    // 사원 배열 동적 생성하기
    company.employees = new Employee[company.num_entries];

    // 사원 정보 입력받기
    for (int i = 0; i < company.num_entries; i++)
    {
        // 파일에서 사원 한 명의 정보 입력받기
        in >> company.employees[i];
    }

    // 입력 스트림 반환하기
    return in;
}

// Company 객체 출력하기
ostream& operator<<(ostream& out, const Company& company)
{
    // 회사 이름과 사원 수 출력하기
    out << "Company ("
        << company.db_name
        << ", num_Employees = "
        << company.num_entries
        << ")"
        << endl;

    // 전체 사원 정보 출력하기
    for (int i = 0; i < company.num_entries; i++)
    {
        // 사원 한 명의 정보 출력하기
        out << company.employees[i] << endl;
    }

    // 출력 스트림 반환하기
    return out;
}