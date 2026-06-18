/*
VocaArray.h
project : Voca 객체 배열을 관리하는 VocaArray class를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// VOCA_ARRAY_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef VOCA_ARRAY_H
// VOCA_ARRAY_H 매크로 정의하기
#define VOCA_ARRAY_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// vector 자료구조를 사용하기 위한 헤더파일
#include <vector>

// Voca class를 사용하기 위한 헤더파일
#include "Voca.h"

// Voca 객체 배열을 관리하는 VocaArray class 선언하기
class VocaArray
{
private:
    // Voca 객체들을 저장하는 vector 선언하기
    std::vector<Voca> vocas;

public:
    // 기본 생성자
    VocaArray();

    // 입력 파일에서 Voca 객체들을 읽어오는 생성자
    VocaArray(std::istream& fin);

    // Voca 개수 반환하기
    int getNumVocas() const;

    // index 위치의 Voca 객체 반환하기
    Voca& operator[](int index);

    // index 위치의 Voca 객체 반환하기
    const Voca& operator[](int index) const;

    // 전체 Voca 배열 출력하기
    void printVocaArray(std::ostream& fout) const;
};

#endif