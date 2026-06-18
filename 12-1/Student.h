/*
Student.h
project : Regular Expression을 사용하여 학생 정보를 입력받는 Student class를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// STUDENT_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef STUDENT_H
// STUDENT_H 매크로 정의하기
#define STUDENT_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 전화번호 정보를 저장하는 구조체 선언하기
typedef struct {
    int region_no;
    int switch_no;
    int line_no;
} Tel_No;

// 학생 정보를 저장하는 Student class 선언하기
class Student {
    // Student 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream& fout, const Student& st);

    // Student 객체를 입력하기 위한 연산자 오버로딩 함수
    friend std::istream& operator>>(std::istream& fin, Student& st);

public:
    // 기본 생성자
    Student();

    // 학생 정보를 초기화하는 생성자
    Student(int stID, const std::string& name, Tel_No telNo,
        const std::string& email, const std::string& addr);

    // 학생 정보로부터 hash code 생성하기
    std::size_t getHashCode() const;

private:
    // 학번 저장하기
    int stID;

    // 이름 저장하기
    std::string name;

    // 전화번호 저장하기
    Tel_No telNo;

    // 이메일 주소 저장하기
    std::string email;

    // 주소 저장하기
    std::string addr;
};

#endif