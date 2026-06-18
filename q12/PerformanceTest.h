/*
main.cpp
project : insert, find 성능을 비교하는 템플릿 함수가 구현된 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 05, 2026
*/

// PERFORMANCE_TEST_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef PERFORMANCE_TEST_H
#define PERFORMANCE_TEST_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <chrono>

// 필요한 상수 선언하기
constexpr int NUM_DATA = 1'000'000;
constexpr int NUM_FIND_TEST = 100'000;

// Insert 성능 측정 템플릿 함수 생성하기
template <typename Container>
long long measureInsertPerformance(Container& container, const std::vector<std::pair<int, std::string>>& kvStr_pairs)
{
    // 시작 시간 기록하기
    auto start = std::chrono::high_resolution_clock::now();

    // 데이터 삽입하기
    for (const auto& pair : kvStr_pairs) {
        container.insert(pair);
    }

    // 종료 시간 기록하기
    auto end = std::chrono::high_resolution_clock::now();

    // 마이크로초(us) 단위로 변환하여 반환하기
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Find 성능 측정 템플릿 함수 생성하기
template <typename Container>
long long measureFindPerformance(const Container& container, const std::vector<int>& testKeys)
{
    // 시작 시간 기록하기
    auto start = std::chrono::high_resolution_clock::now();

    // 데이터 탐색하기
    for (int key : testKeys) {
        container.find(key);
    }

    // 종료 시간 기록하기
    auto end = std::chrono::high_resolution_clock::now();

    // 마이크로초(us) 단위로 변환하여 반환하기
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

#endif