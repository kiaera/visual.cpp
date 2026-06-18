/*
GenericHashDict_KV.h
project : GenericHashMap_KV를 상속받아 같은 key에 여러 value를 저장할 수 있는 GenericHashDict_KV template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// HASH_DICTIONARY_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef HASH_DICTIONARY_H
// HASH_DICTIONARY_H 매크로 정의하기
#define HASH_DICTIONARY_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// GenericHashMap_KV class를 사용하기 위한 헤더파일
#include "GenericHashMap_KV.h"

// 기본 hash table 크기 정의하기
#define DEFAULT_HASH_SIZE 101

// 같은 key에 여러 value를 저장할 수 있는 GenericHashDict_KV template class 선언하기
template <typename K, typename V>
class GenericHashDict_KV : public GenericHashMap_KV<K, V>
{
public:
    // 부모 class 자료형을 Base로 정의하기
    typedef GenericHashMap_KV<K, V> Base;

    // 부모 class의 Iterator 자료형 가져오기
    typedef typename Base::Iterator Iterator;

    // 부모 class의 bucket iterator 자료형 가져오기
    typedef typename Base::BItor BItor;

    // 부모 class의 Entry_KV iterator 자료형 가져오기
    typedef typename Base::EItor EItor;

    // 같은 key를 가진 Entry_KV들의 범위를 나타내는 Range class 선언하기
    class Range
    {
    private:
        // 범위의 시작 iterator 저장하기
        Iterator _begin;

        // 범위의 끝 iterator 저장하기
        Iterator _end;

    public:
        // 기본 생성자
        Range() = default;

        // 시작 위치와 끝 위치를 초기화하는 생성자
        Range(const Iterator& b, const Iterator& e)
            : _begin(b), _end(e)
        {}

        // 범위의 시작 iterator 반환하기
        Iterator begin()
        {
            return _begin;
        }

        // 범위의 끝 iterator 반환하기
        Iterator end()
        {
            return _end;
        }
    };

public:
    // 생성자
    GenericHashDict_KV(const std::string nm,
        int hashTblSize = DEFAULT_HASH_SIZE)
        : Base(nm, hashTblSize)
    {}

    // 같은 key가 있어도 value를 추가로 삽입하는 함수
    Iterator insert(const K& k, const V& v)
    {
        // key에 해당하는 bucket index 계산하기
        int bucketIndex = this->getBucketIndex(k);

        // 해당 bucket iterator 설정하기
        BItor b = this->BA.begin() + bucketIndex;

        // 삽입 위치를 기본적으로 bucket의 끝으로 설정하기
        EItor insertPos = b->end();

        // 같은 key가 이미 있는지 bucket 안에서 찾기
        for (EItor e = b->begin(); e != b->end(); ++e)
        {
            if (e->getKey() == k)
            {
                // 같은 key를 찾으면 그 다음 위치부터 삽입 위치를 찾기
                insertPos = e;
                ++insertPos;

                // 같은 key가 연속으로 저장되어 있으면 그 뒤까지 이동하기
                while (insertPos != b->end() && insertPos->getKey() == k)
                {
                    ++insertPos;
                }

                break;
            }
        }

        // 같은 key가 있더라도 덮어쓰지 않고 새로운 Entry_KV 삽입하기
        EItor inserted = b->insert(insertPos, Entry_KV<K, V>(k, v));

        // 저장된 Entry_KV 개수 증가시키기
        ++this->num_entry;

        // 삽입된 위치의 iterator 반환하기
        return Iterator(this->BA, b, inserted);
    }

    // 같은 key를 가진 Entry_KV들의 범위 찾기
    Range findAll(const K& k)
    {
        // key에 해당하는 bucket index 계산하기
        int bucketIndex = this->getBucketIndex(k);

        // 해당 bucket iterator 설정하기
        BItor b = this->BA.begin() + bucketIndex;

        // 같은 key 범위의 시작 위치 저장하기
        EItor first = b->end();

        // 같은 key 범위의 끝 위치 저장하기
        EItor last = b->end();

        // bucket 안에서 같은 key 찾기
        for (EItor e = b->begin(); e != b->end(); ++e)
        {
            if (e->getKey() == k)
            {
                // 같은 key의 첫 번째 위치 저장하기
                first = e;

                // 같은 key의 마지막 다음 위치 찾기
                last = e;
                ++last;

                while (last != b->end() && last->getKey() == k)
                {
                    ++last;
                }

                // 같은 bucket 안에서만 반복되도록 Range 반환하기
                return Range(
                    Iterator(this->BA, b, first, true),
                    Iterator(this->BA, b, last, true)
                );
            }
        }

        // key를 찾지 못하면 빈 Range 반환하기
        return Range(this->end(), this->end());
    }

    // 입력 파일에서 Voca 정보를 읽어 HashDict에 저장하는 함수
    int fgetVocaDict(std::istream& fin);
};

// 입력 파일에서 Voca 정보를 읽어 HashDict에 저장하는 함수 구현하기
template <typename K, typename V>
int GenericHashDict_KV<K, V>::fgetVocaDict(std::istream& fin)
{
    // 한 줄의 어휘 정보를 저장할 문자열 선언하기
    std::string line;

    // 입력된 Voca 개수 저장하기
    int count = 0;

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
        V voca;

        // 한 줄의 문자열을 Voca 객체로 변환하기
        if (voca.parseLine(line))
        {
            // keyWord를 key로 하여 HashDict에 Voca 저장하기
            insert(voca.getKeyWord(), voca);

            // 입력된 Voca 개수 증가시키기
            ++count;
        }
    }

    return count;
}

#endif