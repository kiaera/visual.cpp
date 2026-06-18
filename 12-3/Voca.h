/*
Voca.h
project : TOEIC 어휘 정보를 저장하는 Voca class를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// VOCA_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef VOCA_H
// VOCA_H 매크로 정의하기
#define VOCA_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// vector 자료구조를 사용하기 위한 헤더파일
#include <vector>

// TOEIC 어휘 정보를 저장하는 Voca class 선언하기
class Voca
{
private:
    // 핵심 어휘 저장하기
    std::string keyWord;

    // 품사 저장하기
    std::string partOfSpeech;

    // 유의어 목록 저장하기
    std::vector<std::string> thesaurus;

    // 예문 목록 저장하기
    std::vector<std::string> exampleUsages;

public:
    // 기본 생성자
    Voca();

    // 어휘 정보를 초기화하는 생성자
    Voca(const std::string& keyWord, const std::string& partOfSpeech,
        const std::vector<std::string>& thesaurus,
        const std::vector<std::string>& exampleUsages);

    // 핵심 어휘 반환하기
    std::string getKeyWord() const;

    // 품사 반환하기
    std::string getPartOfSpeech() const;

    // 한 줄의 문자열을 Voca 객체로 변환하기
    bool parseLine(const std::string& line);

    // 품사를 출력용 약어로 변환하기
    std::string getPOSAbbrev() const;

    // Voca 객체 출력하기
    friend std::ostream& operator<<(std::ostream& fout, const Voca& voca);
};

#endif