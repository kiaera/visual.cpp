/*
main.cpp
project : GenericHashDict_KV를 이용하여 같은 keyword에 여러 품사의 Voca를 저장하고 검색하는 프로그램
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

// Voca class를 사용하기 위한 헤더파일
#include "Voca.h"

// GenericHashDict_KV class를 사용하기 위한 헤더파일
#include "GenericHashDict_KV.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// hash table의 bucket 개수 정의하기
#define HASH_TABLE_SIZE 101

/*
GenericHashDict_KV를 이용하여 
같은 keyword에 여러 품사의 Voca를 저장하고 검색하는 메인 함수
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

    // string key와 Voca value를 저장하는 HashDict 생성하기
    GenericHashDict_KV<string, Voca> thesHashDict(
        "My Thesaurus Hash Map", HASH_TABLE_SIZE);

    // HashDict 포인터 선언하기
    GenericHashDict_KV<string, Voca>* pHashDict = &thesHashDict;

    // HashDict iterator 선언하기
    GenericHashDict_KV<string, Voca>::Iterator vocaHD_Iter;

    // 같은 key를 가진 Voca들의 범위를 저장할 Range 선언하기
    GenericHashDict_KV<string, Voca>::Range vocaHD_Range;

    // 입력 파일에서 Voca 정보를 읽어 HashDict에 저장하기
    pHashDict->fgetVocaDict(fin);

    // HashDict 출력 시작 메시지 출력하기
    cout << "\n==============================================\n";
    cout << "Voca HashMap after fgetVocaDict() :" << endl;

    // keyWord 저장 변수 선언하기
    string keyWord;

    // Voca 객체 저장 변수 선언하기
    Voca voca;

    // Entry_KV 저장 변수 선언하기
    Entry_KV<string, Voca> vocaEntry_KV;

    // HashDict의 첫 번째 Entry_KV 위치 가져오기
    vocaHD_Iter = pHashDict->begin();

    // HashDict에 저장된 모든 Entry_KV 출력하기
    while (vocaHD_Iter != pHashDict->end())
    {
        // 현재 iterator 위치의 Entry_KV 가져오기
        vocaEntry_KV = *vocaHD_Iter;

        // Entry_KV에서 key 가져오기
        keyWord = vocaEntry_KV.getKey();

        // Entry_KV에서 value 가져오기
        voca = vocaEntry_KV.getValue();

        // key와 Voca 정보 출력하기
        cout << keyWord << " : " << voca << endl;

        // 다음 Entry_KV로 이동하기
        ++vocaHD_Iter;
    }

    // bucket별 Entry_KV 개수 출력하기
    pHashDict->fprintBucketSizes(cout);

    // keyword 검색 테스트 시작 메시지 출력하기
    cout << "\nTesting keyword findings in HashDict_Voca ...." << endl;

    // 검색할 keyword 배열 선언하기
    string test_keywords[] = { "mean", "compromise", "duplicate" };

    // test_keywords에 저장된 keyword들을 차례대로 검색하기
    for (auto keyWord : test_keywords)
    {
        // 현재 검색 keyword 출력하기
        cout << "Thesaurus of " << keyWord << " in HashDict_Voca : \n";

        // 같은 keyword를 가진 Voca들의 범위 찾기
        vocaHD_Range = pHashDict->findAll(keyWord);

        // Range 안의 모든 Voca 출력하기
        for (vocaHD_Iter = vocaHD_Range.begin();
            vocaHD_Iter != vocaHD_Range.end(); ++vocaHD_Iter)
        {
            // 현재 iterator 위치의 value 가져오기
            voca = (*vocaHD_Iter).getValue();

            // 검색된 Voca 출력하기
            cout << voca << endl;
        }
    }

    return 0;
}