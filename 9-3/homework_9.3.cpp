/*
main_HW9_3.cpp
project : STL priority_queue를 이용하여 학생 정보를 우선순위 기준으로 정렬 출력하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// priority_queue를 사용하기 위한 헤더파일
#include <queue>

// vector 컨테이너를 사용하기 위한 헤더파일
#include <vector>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// Student class를 사용하기 위한 헤더파일
#include "Student.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 제목 출력 함수 원형 선언하기
void Print_Title(const string& title);

// priority_queue 시험 함수 원형 선언하기
void Test_Priority_Queue(
    const vector<Student>& students,
    KeyAttr keyAttr,
    SortOrder order,
    const string& title);

/*
학생정보를 여러가지 기준에 맞춰 
오름차순 및 내림차순으로 정렬하여 출력하는 함수
*/
int main()
{
    // 학생 정보를 vector에 저장하기
    vector<Student> students =
    {
        Student("Kim", 20230031, 3.85),
        Student("Lee", 20210015, 4.10),
        Student("Park", 20220027, 3.42),
        Student("Choi", 20230005, 4.35),
        Student("Han", 20210003, 3.85),
        Student("Jung", 20240011, 2.95),
        Student("Song", 20220009, 4.35)
    };

    // 이름 오름차순 출력하기
    Test_Priority_Queue(
        students,
        KeyAttr::NAME,
        SortOrder::ASC,
        "Priority by NAME ascending");

    // 이름 내림차순 출력하기
    Test_Priority_Queue(
        students,
        KeyAttr::NAME,
        SortOrder::DESC,
        "Priority by NAME descending");

    // 학번 오름차순 출력하기
    Test_Priority_Queue(
        students,
        KeyAttr::STID,
        SortOrder::ASC,
        "Priority by stID ascending");

    // 학번 내림차순 출력하기
    Test_Priority_Queue(
        students,
        KeyAttr::STID,
        SortOrder::DESC,
        "Priority by stID descending");

    // GPA 오름차순 출력하기
    Test_Priority_Queue(
        students,
        KeyAttr::GPA,
        SortOrder::ASC,
        "Priority by GPA ascending");

    // GPA 내림차순 출력하기
    Test_Priority_Queue(
        students,
        KeyAttr::GPA,
        SortOrder::DESC,
        "Priority by GPA descending");

    return 0;
}

// 제목 출력 함수 구현하기
void Print_Title(const string& title)
{
    cout << "\n========================================\n";
    cout << title << endl;
    cout << "----------------------------------------\n";

    cout << left
        << setw(12) << "Name"
        << setw(10) << "stID"
        << "GPA" << endl;

    cout << "----------------------------------------\n";
}

// priority_queue 시험 함수 구현하기
void Test_Priority_Queue(
    const vector<Student>& students,
    KeyAttr keyAttr,
    SortOrder order,
    const string& title)
{
    // 우선순위 큐 객체 생성하기
    priority_queue<
        Student,
        vector<Student>,
        StudentCompare> pq(StudentCompare(keyAttr, order));

    // vector의 학생 정보를 priority_queue에 삽입하기
    for (const auto& s : students)
    {
        pq.push(s);
    }

    // 제목 출력하기
    Print_Title(title);

    // 가장 우선순위가 높은 학생 출력하기
    cout << "[top() : highest priority student]\n";

    if (!pq.empty())
    {
        pq.top().print();
    }

    // 모든 학생을 우선순위 순서대로 출력하기
    cout << "\n[all students popped in priority order]\n";

    while (!pq.empty())
    {
        pq.top().print();
        pq.pop();
    }
}