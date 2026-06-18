/*
StudentDB.cpp
project : StudentDB 클래스의 생성자, 소멸자, 학생 정렬 기능 및 입출력 연산자를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 02, 2026
*/

// StudentDB 클래스를 사용하기 위한 헤더파일
#include "StudentDB.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 기본 생성자 정의하기
StudentDB::StudentDB()
{
    // 데이터베이스 이름 초기화하기
    db_name = "";

    // 학생 수 초기화하기
    num_entries = 0;

    // Student 배열 포인터 초기화하기
    students = nullptr;
}

// 생성자 정의하기
StudentDB::StudentDB(string db_name, int num_entries)
{
    // 데이터베이스 이름 저장하기
    this->db_name = db_name;

    // 학생 수 저장하기
    this->num_entries = num_entries;

    // Student 객체 배열 동적 할당하기
    students = new Student[num_entries];
}

// 소멸자 정의하기
StudentDB::~StudentDB()
{
    // 동적 할당한 Student 배열 메모리 해제하기
    delete[] students;
}

// 학생 정렬 함수 정의하기
void StudentDB::Sort_Students(ST_ATTR attr, SORT_ORDER sort_order)
{
    // 버블 정렬 수행하기
    for (int i = 0; i < num_entries - 1; i++)
    {
        for (int j = 0; j < num_entries - 1 - i; j++)
        {
            // 현재 학생이 다음 학생보다 큰 경우
            if (students[j].Compare_Student(students[j + 1], attr, sort_order) > 0)
            {
                // 현재 학생 정보를 임시 객체에 저장하기
                Student temp = students[j];

                // 다음 학생을 현재 위치로 이동하기
                students[j] = students[j + 1];

                // 임시 객체 값을 다음 위치에 저장하기
                students[j + 1] = temp;
            }
        }
    }
}

// 입력 연산자 함수 정의하기
istream& operator>>(istream& fin, StudentDB& db)
{
    // 데이터베이스 이름과 학생 수 입력받기
    fin >> db.db_name >> db.num_entries;

    // 기존 Student 배열 메모리 해제하기
    delete[] db.students;

    // Student 객체 배열 새로 동적 할당하기
    db.students = new Student[db.num_entries];

    // 파일 입력 정보 출력하기
    cout << "File input : DB-name (" << db.db_name
        << "), num_students (" << db.num_entries << ")" << endl;

    // 모든 학생 정보 입력받기
    for (int i = 0; i < db.num_entries; i++)
    {
        // 학생 정보 입력받기
        fin >> db.students[i];
    }

    // 입력 스트림 반환하기
    return fin;
}

// 출력 연산자 함수 정의하기
ostream& operator<<(ostream& fout, const StudentDB& db)
{
    // StudentDB 정보 출력하기
    fout << "StudentDB (" << db.db_name
        << ", num_students = " << db.num_entries << ")" << endl;

    // 모든 학생 정보 출력하기
    for (int i = 0; i < db.num_entries; i++)
    {
        // 학생 정보 출력하기
        fout << db.students[i] << endl;
    }

    // 출력 스트림 반환하기
    return fout;
}