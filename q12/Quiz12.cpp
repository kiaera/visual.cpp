/*
main.cpp
project : STL map과 unordered_map의 insert, find 성능을 비교하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 05, 2026
*/

#include "PerformanceTest.h"
#include <random>
    
using namespace std;
using namespace std::chrono;
using Clock = chrono::high_resolution_clock;

/*
STL map과 unordered_map의 
insert, find 성능을 비교하는 메인 함수
*/
int main()
{
    map<int, string> orderedMap;
    unordered_map<int, string> unorderedMap;
    unorderedMap.max_load_factor(0.75);
    unorderedMap.reserve(NUM_DATA);

    cout << "Comparison of performance of insert() and find() in std::map and std::unordered_map\n";
    cout << "Total num_data = " << NUM_DATA << ", num_find_test = " << NUM_FIND_TEST << "\n\n";

    cout << "[1] kv_pairs(stID, \"Student_\" + to_string(stID)) creation and insertions ...\n";
    vector<pair<int, string>> kv_pairs;
    kv_pairs.reserve(NUM_DATA);

    /*
    pair(stID, "Student_" + to_string(stID))의 kv_pairs 생성하기
    stID를 0부터 순차적으로 생성하기
    */
    for (int i = 0; i < NUM_DATA; ++i) {
        int stID = i; 
        kv_pairs.push_back({ stID, "Student_" + to_string(stID) });
    }

    long long orderedInsertTime, unorderedInsertTime;   
    orderedInsertTime = measureInsertPerformance(orderedMap, kv_pairs);
    unorderedInsertTime = measureInsertPerformance(unorderedMap, kv_pairs);

    // insert 성능 측정 결과 출력하기
    cout << "std::map insert time           :   " << orderedInsertTime << " [us]\n";
    cout << "std::unordered_map insert time :   " << unorderedInsertTime << "  [us]\n\n";

    // Find 성능 측정하기
    vector<int> testKeys;
    testKeys.reserve(NUM_FIND_TEST);

    // 난수 생성하기
    mt19937 gen(12345); 
    uniform_int_distribution<int> dist(0, NUM_DATA - 1);

    // testKeys 생성하기
    for (int i = 0; i < NUM_FIND_TEST; ++i) {
        testKeys.push_back(dist(gen));
    }

    cout << "[2] Performance measurement of find() for " << NUM_FIND_TEST << " test keys\n";
    long long orderedFindTime, unorderedFindTime;
    orderedFindTime = measureFindPerformance(orderedMap, testKeys);
    unorderedFindTime = measureFindPerformance(unorderedMap, testKeys);

    // find 성능 측정 결과 출력하기
    cout << "std::map find time           :   " << orderedFindTime << " [us]\n";
    cout << "std::unordered_map find time :   " << unorderedFindTime << " [us]\n";

    return 0;
}
