/*
main.cpp
project : GenericHashMap_KV를 이용하여 TOEIC VocaDictionary를 구현하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// 프로그램 종료 함수를 사용하기 위한 헤더파일
#include <cstdlib>

// 파일 입출력을 사용하기 위한 헤더파일
#include <fstream>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// GenericHashMap_KV class를 사용하기 위한 헤더파일
#include "GenericHashMap_KV.h"

// Voca class를 사용하기 위한 헤더파일
#include "Voca.h"

// VocaArray class를 사용하기 위한 헤더파일
#include "VocaArray.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// hash table의 bucket 개수 정의하기
#define HASH_TABLE_SIZE 101

/*
GenericHashMap_KV를 이용하여 
TOEIC VocaDictionary를 구현하는 메인 함수
*/
int main()
{
    // 입력 파일 객체 선언하기
    ifstream fin;

    // 입력 파일 열기
    fin.open("myVoca_data.txt");

    // 파일 열기에 실패한 경우 오류 메시지 출력하기
    if (fin.fail())
    {
        cout << "Fail to open input data file (myVoca_data.txt) !!" << endl;
        exit(-1);
    }

    // 입력 파일에서 VocaArray 생성하기
    VocaArray vocaDB(fin);

    // VocaArray 출력하기
    vocaDB.printVocaArray(cout);

    // string key와 Voca* value를 저장하는 hash map 생성하기
    GenericHashMap_KV<string, Voca*> thesaurusHashMap(
        "My Thesaurus Hash Map", HASH_TABLE_SIZE);

    // hash map 포인터 선언하기
    GenericHashMap_KV<string, Voca*>* pHM = &thesaurusHashMap;

    // hash map iterator 선언하기
    GenericHashMap_KV<string, Voca*>::Iterator vocaHM_Iter;

    // keyword 저장 변수 선언하기
    string keyWord;

    // Voca 포인터 변수 선언하기
    Voca* pVoca;

    // Voca Entry_KV 저장 변수 선언하기
    Entry_KV<string, Voca*> vocaEntry_KV;

    // hash map 테스트 시작 메시지 출력하기
    cout << "\nTesting Thesaurus Hash Map " << endl;
    cout << "Hash Map Name (" << pHM->getName();
    cout << "); size (" << pHM->size() << ")" << endl;

    // hash map 삽입 시작 메시지 출력하기
    cout << "Inserting Voca into Hash Map ..." << endl;

    // Voca 개수 저장하기
    int num_vocas = vocaDB.getNumVocas();

    // bucket index 저장 변수 선언하기
    int bucket_index;

    // VocaArray의 Voca 객체들을 hash map에 삽입하기
    for (int i = 0; i < num_vocas; i++)
    {
        // keyWord 가져오기
        keyWord = vocaDB[i].getKeyWord();

        // Voca 객체의 주소 저장하기
        pVoca = &vocaDB[i];

        // hash map에 key-value 삽입하기
        vocaHM_Iter = pHM->insert(keyWord, pVoca);

        // keyWord가 저장되는 bucket index 계산하기
        bucket_index = pHM->getBucketIndex(keyWord);

        // 삽입 결과 출력하기
        cout << "voca(" << *pVoca << "),\n - bucket_index = ";
        cout << bucket_index << endl;
    }

    // 삽입 후 hash map 크기 출력하기
    cout << "\nHash Map size after insertions : " << pHM->size() << endl;
    cout << "Input Voca count               : " << num_vocas << endl;
    cout << "If the same keyword appears several times, only the latest value remains.\n";

    // hash map 전체 출력 시작 메시지 출력하기
    cout << "\n============================================\n";
    cout << "Voca HashMap after insertions of Voca :" << endl;

    // hash map의 처음 위치 가져오기
    vocaHM_Iter = pHM->begin();

    // hash map의 모든 Entry_KV 출력하기
    while (vocaHM_Iter != pHM->end())
    {
        // 현재 Entry_KV 가져오기
        vocaEntry_KV = *vocaHM_Iter;

        // keyWord 가져오기
        keyWord = vocaEntry_KV.getKey();

        // Voca 포인터 가져오기
        pVoca = vocaEntry_KV.getValue();

        // key와 Voca 정보 출력하기
        cout << keyWord << " : " << *pVoca << endl;

        // 다음 Entry_KV로 이동하기
        ++vocaHM_Iter;
    }

    // bucket별 Entry_KV 개수 출력하기
    pHM->fprintBucketSizes(cout);
        
    // 마지막 Voca의 keyWord 가져오기
    keyWord = vocaDB[num_vocas - 1].getKeyWord();

    // 마지막 Voca의 keyWord를 hash map에서 검색하기
    vocaHM_Iter = pHM->find(keyWord);

    // 검색 시작 메시지 출력하기
    cout << "\nTesting search from Voca HashMap for keyWord (";
    cout << keyWord << ") : " << endl;

    // 검색 결과 출력하기
    if (vocaHM_Iter != pHM->end())
    {
        pVoca = (*vocaHM_Iter).getValue();
        cout << *pVoca << endl;
    }
    else
    {
        cout << "Keyword not found: " << keyWord << endl;
    }

    return 0;
}