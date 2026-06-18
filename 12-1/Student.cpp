/*
Student.cpp
project : Student class 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// Student class를 사용하기 위한 헤더파일
#include "Student.h"

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 정규식을 사용하기 위한 헤더파일
#include <regex>

// 문자열 스트림을 사용하기 위한 헤더파일
#include <sstream>

// 기본 생성자
Student::Student()
{
    stID = 0;
    name = "";
    telNo.region_no = 0;
    telNo.switch_no = 0;
    telNo.line_no = 0;
    email = "";
    addr = "";
}

// 학생 정보를 초기화하는 생성자
Student::Student(int stID, const std::string& name, Tel_No telNo,
    const std::string& email, const std::string& addr)
{
    this->stID = stID;
    this->name = name;
    this->telNo = telNo;
    this->email = email;
    this->addr = addr;
}

// Student 객체를 입력하기 위한 연산자 오버로딩 함수
std::istream& operator>>(std::istream& fin, Student& st)
{
    // 한 줄의 학생 정보를 저장할 문자열 선언하기
    std::string line;

    // 공백 줄은 건너뛰고 한 줄 입력받기
    while (std::getline(fin, line)) {
        if (line.find_first_not_of(" \t\r\n") != std::string::npos) {
            break;
        }
    }

    // 더 이상 입력할 줄이 없으면 반환하기
    if (!fin) {
        return fin;
    }

    // 학생 정보 형식을 검사하기 위한 정규식 선언하기
    std::regex studentPattern(
        R"REGEX(^\s*(\d+)\s+"([^"]+)"\s+(\d{3})-(\d{4})-(\d{4})\s+([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,})\s+"([^"]+)"\s*$)REGEX"
    );

    // 정규식 결과를 저장할 객체 선언하기
    std::smatch match;

    // 입력 형식이 정규식과 맞지 않으면 fail 상태로 설정하기
    if (!std::regex_match(line, match, studentPattern)) {
        fin.setstate(std::ios::failbit);
        return fin;
    }

    // 정규식으로 분리한 학번 저장하기
    st.stID = std::stoi(match[1]);

    // 정규식으로 분리한 이름 저장하기
    st.name = match[2];

    // 정규식으로 분리한 전화번호 저장하기
    st.telNo.region_no = std::stoi(match[3]);
    st.telNo.switch_no = std::stoi(match[4]);
    st.telNo.line_no = std::stoi(match[5]);

    // 정규식으로 분리한 이메일 주소 저장하기
    st.email = match[6];

    // 정규식으로 분리한 주소 저장하기
    st.addr = match[7];

    return fin;
}

// Student 객체를 출력하기 위한 연산자 오버로딩 함수
std::ostream& operator<<(std::ostream& fout, const Student& st)
{
    // 전화번호를 010-1234-5678 형식으로 만들기
    std::ostringstream telStream;

    // 전화번호 출력 형식 설정하기
    telStream << std::setfill('0')
        << std::setw(3) << st.telNo.region_no << "-"
        << std::setw(4) << st.telNo.switch_no << "-"
        << std::setw(4) << st.telNo.line_no;

    // 학생 정보 출력하기
    fout << std::left
        << std::setw(10) << st.stID
        << std::setw(20) << st.name
        << std::setw(16) << telStream.str()
        << std::setw(24) << st.email
        << std::setw(20) << st.addr;

    return fout;
}

// 학생 정보로부터 hash code 생성하기
std::size_t Student::getHashCode() const
{
    // hash code 저장 변수 선언하기
    std::size_t hashCode = static_cast<std::size_t>(stID);

    // 이름의 각 문자를 hash code에 반영하기
    for (int i = 0; i < static_cast<int>(name.length()); ++i) {
        hashCode = hashCode * 31 + static_cast<unsigned char>(name[i]);
    }

    // 전화번호의 지역번호를 hash code에 반영하기
    hashCode = hashCode * 31 + static_cast<std::size_t>(telNo.region_no);

    // 전화번호의 국번을 hash code에 반영하기
    hashCode = hashCode * 31 + static_cast<std::size_t>(telNo.switch_no);

    // 전화번호의 끝 번호를 hash code에 반영하기
    hashCode = hashCode * 31 + static_cast<std::size_t>(telNo.line_no);

    return hashCode;
}