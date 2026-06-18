/*
VocaArray.cpp
project : VocaArray class 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// VocaArray class를 사용하기 위한 헤더파일
#include "VocaArray.h"

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// 기본 생성자
VocaArray::VocaArray()
{}

// 입력 파일에서 Voca 객체들을 읽어오는 생성자
VocaArray::VocaArray(std::istream& fin)
{
    // 한 줄의 어휘 정보를 저장할 문자열 선언하기
    std::string line;

    // 파일에서 한 줄씩 읽기
    while (std::getline(fin, line))
    {
        // 공백 줄은 건너뛰기
        if (line.find_first_not_of(" \t\r\n") == std::string::npos)
        {
            continue;
        }

        // 주석 줄은 건너뛰기
        if (line[0] == '#')
        {
            continue;
        }

        // 제목 줄은 건너뛰기
        if (line.find("Voca_DB") != std::string::npos)
        {
            continue;
        }

        // Voca 객체 생성하기
        Voca voca;

        // 한 줄을 Voca 객체로 변환할 수 있으면 vector에 추가하기
        if (voca.parseLine(line))
        {
            vocas.push_back(voca);
        }
    }
}

// Voca 개수 반환하기
int VocaArray::getNumVocas() const
{
    return static_cast<int>(vocas.size());
}

// index 위치의 Voca 객체 반환하기
Voca& VocaArray::operator[](int index)
{
    return vocas[index];
}

// index 위치의 Voca 객체 반환하기
const Voca& VocaArray::operator[](int index) const
{
    return vocas[index];
}

// 전체 Voca 배열 출력하기
void VocaArray::printVocaArray(std::ostream& fout) const
{
    fout << "Voca_DB(num_vocas : " << vocas.size() << ") ";

    for (int i = 0; i < static_cast<int>(vocas.size()); ++i)
    {
        fout << vocas[i] << std::endl;
    }
}