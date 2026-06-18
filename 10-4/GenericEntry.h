/*
GenericEntry.h
project : Heap Priority Queue에 저장할 key-value 항목을 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// GENERIC_ENTRY_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GENERIC_ENTRY_H

// GENERIC_ENTRY_H 매크로 정의하기
#define GENERIC_ENTRY_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// GenericEntry template class 선언하기
template<typename K, typename V>
class GenericEntry
{
    // 출력 연산자 함수 friend 선언하기
    template<typename K2, typename V2>
    friend std::ostream& operator<<(std::ostream& fout, const GenericEntry<K2, V2>& ge);

public:
    // 기본 생성자
    GenericEntry()
    {
        key = K();
        value = V();
    }

    // 매개변수 생성자
    GenericEntry(K k, V v)
    {
        key = k;
        value = v;
    }

    // key 반환하기
    K getKey() const
    {
        return key;
    }

    // value 반환하기
    V getValue() const
    {
        return value;
    }

    // key 설정하기
    void setKey(K k)
    {
        key = k;
    }

    // value 설정하기
    void setValue(V v)
    {
        value = v;
    }

private:
    // 우선순위 key 저장하기
    K key;

    // value 저장하기
    V value;
};

// GenericEntry 출력 연산자 함수 구현하기
template<typename K, typename V>
std::ostream& operator<<(std::ostream& fout, const GenericEntry<K, V>& ge)
{
    fout << "[Key:" << ge.key << ", " << ge.value << "]";

    return fout;
}

#endif