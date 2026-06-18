/*
main.cpp
project : STL multimap과 unordered_multimap의 insert, find 성능을 비교하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>
// multimap을 사용하기 위한 헤더파일
#include <map>
// unordered_multimap을 사용하기 위한 헤더파일
#include <unordered_map>
// vector를 사용하기 위한 헤더파일
#include <vector>
// pair를 사용하기 위한 헤더파일
#include <utility>
// 난수 생성을 사용하기 위한 헤더파일
#include <random>
// 실행 시간 측정을 사용하기 위한 헤더파일
#include <chrono>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// chrono에 포함된 시간 관련 식별자들을 사용할 수 있게 선언하기
using namespace std::chrono;

// 시간 측정에 사용할 clock 자료형 정의하기
using Clock = chrono::high_resolution_clock;

// 전체 데이터 개수 정의하기
constexpr int NUM_DATA = 1000000;

// find() 성능 측정에 사용할 key 개수 정의하기
constexpr int NUM_FIND_TEST = 100000;

/*
함수 이름 : measureInsertPerformance
기능 : container에 key-value pair 데이터를 insert하고 실행 시간을 측정한다.
반환값 : insert 실행에 걸린 시간
*/
template <typename Container>
long long measureInsertPerformance(Container& container,
    const vector<pair<string, string>>& kvStr_pairs)
{
    // 시작 시간 저장하기
    auto start = Clock::now();

    // container에 key-value pair 삽입하기
    for (const auto& kvStr_pair : kvStr_pairs) {
        container.insert(kvStr_pair);
    }

    // 종료 시간 저장하기
    auto end = Clock::now();

    // 실행 시간을 microsecond 단위로 계산하기
    auto elapsedMicro =
        chrono::duration_cast<chrono::microseconds>(end - start).count();

    return elapsedMicro;
}

/*
함수 이름 : measureFindPerformance
기능 : testKeys에 저장된 key들을 container에서 find하고 실행 시간을 측정한다.
반환값 : find 실행에 걸린 시간
*/
template <typename Container>
long long measureFindPerformance(const Container& container,
    const vector<string>& testKeys)
{
    // 탐색에 성공한 key 개수 저장하기
    size_t foundCount = 0;

    // 전체 탐색 key 개수 저장하기
    size_t num_test_words = testKeys.size();

    // 시작 시간 저장하기
    auto start = Clock::now();

    // testKeys에 저장된 key들을 탐색하기
    for (const auto& key : testKeys) {
        auto itr = container.find(key);

        // key를 찾은 경우 foundCount 증가시키기
        if (itr != container.end()) {
            ++foundCount;
        }
    }

    // 종료 시간 저장하기
    auto end = Clock::now();

    // 탐색 실패가 있는 경우 오류 메시지 출력하기
    if (num_test_words != foundCount) {
        cout << "Error in find operations : foundCount (" << foundCount;
        cout << ") is different from size of testKeys(" << num_test_words << ")\n";
    }

    // 실행 시간을 microsecond 단위로 계산하기
    auto elapsedMicro =
        chrono::duration_cast<chrono::microseconds>(end - start).count();

    return elapsedMicro;
}

/*
STL multimap과 unordered_multimap의 
insert, find 성능을 비교하는 메인 함수
*/
int main()
{
    // 프로그램 제목 출력하기
    cout << "[Comparison of performance of insert() and find() in std::multimap and std::unordered_multimap]\n";

    // 전체 데이터 수와 find 테스트 수 출력하기
    cout << "Total num_data = " << NUM_DATA << ", num_find_test = "
        << NUM_FIND_TEST << '\n';

    // 균형 이진 탐색 트리 기반 multimap 생성하기
    multimap<string, string> orderedMultiMap;

    // 해시 테이블 기반 unordered_multimap 생성하기
    unordered_multimap<string, string> unorderedMultiMap;

    // unordered_multimap의 최대 load factor 설정하기
    unorderedMultiMap.max_load_factor(0.75);

    // unordered_multimap의 bucket 공간 미리 확보하기
    unorderedMultiMap.reserve(NUM_DATA);

    // 데이터 생성 및 삽입 시작 메시지 출력하기
    cout << "\n[1] Data creations and insertions ...\n";

    // key-value pair를 저장할 vector 선언하기
    vector<pair<string, string>> kv_pairs;

    // vector 공간 미리 확보하기
    kv_pairs.reserve(NUM_DATA);

    // key-value pair 데이터 생성하기
    for (int i = 0; i < NUM_DATA; i++) {
        string key = "key_" + to_string(i);
        string value = "value_" + to_string(i);
        kv_pairs.push_back(make_pair(key, value));
    }

    // insert 실행 시간 저장 변수 선언하기
    long long orderedInsertTime, unorderedInsertTime;

    // multimap의 insert 실행 시간 측정하기
    orderedInsertTime = measureInsertPerformance(orderedMultiMap, kv_pairs);

    // multimap의 insert 실행 시간 출력하기
    cout << "std::multimap insert time          : "
        << orderedInsertTime << " [us]\n";

    // unordered_multimap의 insert 실행 시간 측정하기
    unorderedInsertTime = measureInsertPerformance(unorderedMultiMap, kv_pairs);

    // unordered_multimap의 insert 실행 시간 출력하기
    cout << "std::unordered_multimap insert time: "
        << unorderedInsertTime << " [us]\n";

    // unordered_multimap의 hash table 정보 출력하기
    cout << "\n[2] Information of unordered_multimap hash table\n";

    // bucket 하나에 들어간 최대 원소 개수 저장하기
    size_t maxBucketSize = 0;

    // 사용 중인 bucket 개수 저장하기
    size_t usedBucketCount = 0;

    // 각 bucket의 원소 개수 확인하기
    for (size_t i = 0; i < unorderedMultiMap.bucket_count(); ++i) {
        size_t bucketSize = unorderedMultiMap.bucket_size(i);

        // bucket이 비어 있지 않으면 사용 중인 bucket 개수 증가시키기
        if (bucketSize > 0) {
            ++usedBucketCount;
        }

        // 최대 bucket 크기 갱신하기
        if (bucketSize > maxBucketSize) {
            maxBucketSize = bucketSize;
        }
    }

    // 사용 중인 bucket 비율 계산하기
    double usedBucketRatio =
        static_cast<double>(usedBucketCount) / unorderedMultiMap.bucket_count() * 100.0;

    // unordered_multimap의 전체 원소 개수 출력하기
    cout << "size               : " << setw(8)
        << unorderedMultiMap.size() << '\n';

    // 전체 bucket 개수 출력하기
    cout << "bucket_count       : " << setw(8)
        << unorderedMultiMap.bucket_count() << '\n';

    // 사용 중인 bucket 개수 출력하기
    cout << "used_bucket_count  : " << setw(8)
        << usedBucketCount << '\n';

    // 비어 있는 bucket 개수 출력하기
    cout << "empty_bucket_count : " << setw(8)
        << unorderedMultiMap.bucket_count() - usedBucketCount << '\n';

    // 현재 load factor 출력하기
    cout << "load_factor        : "
        << unorderedMultiMap.load_factor() << '\n';

    // 최대 load factor 출력하기
    cout << "max_load_factor    : "
        << unorderedMultiMap.max_load_factor() << '\n';

    // 최대 bucket 크기 출력하기
    cout << "max_bucket_size    : "
        << maxBucketSize << '\n';

    // 사용 중인 bucket 비율 출력하기
    cout << "used_bucket_ratio  : "
        << fixed << setprecision(2) << usedBucketRatio << " %\n";

    // find 테스트에 사용할 key들을 저장할 vector 선언하기
    vector<string> testKeys;

    // testKeys 공간 미리 확보하기
    testKeys.reserve(NUM_FIND_TEST);

    // Mersenne Twister 난수 생성기 생성하기
    mt19937 gen(12345);

    // 0부터 NUM_DATA - 1까지 균등 분포 난수 생성하기
    uniform_int_distribution<int> dist(0, NUM_DATA - 1);

    // find 테스트에 사용할 key 생성하기
    for (int i = 0; i < NUM_FIND_TEST; ++i) {
        int index = dist(gen);
        testKeys.push_back("key_" + to_string(index));
    }

    // find 성능 측정 시작 메시지 출력하기
    cout << "\n[3] Performance measurement results of find() for "
        << NUM_FIND_TEST << " test words\n";

    // find 실행 시간 저장 변수 선언하기
    long long orderedFindTime, unorderedFindTime;

    // multimap의 find 실행 시간 측정하기
    orderedFindTime = measureFindPerformance(orderedMultiMap, testKeys);

    // unordered_multimap의 find 실행 시간 측정하기
    unorderedFindTime = measureFindPerformance(unorderedMultiMap, testKeys);

    // multimap의 find 실행 시간 출력하기
    cout << "std::multimap find time          : "
        << setw(8) << orderedFindTime << " [us]\n";

    // unordered_multimap의 find 실행 시간 출력하기
    cout << "std::unordered_multimap find time: "
        << setw(8) << unorderedFindTime << " [us]\n";

    return 0;
}