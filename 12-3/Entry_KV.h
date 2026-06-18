/*
Entry_KV.h
project : HashMap에서 사용할 Entry_KV template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : June 04, 2026
*/

// ENTRY_KV_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef ENTRY_KV_H
// ENTRY_KV_H 매크로 정의하기
#define ENTRY_KV_H

// key와 value를 함께 저장하는 Entry_KV template class 선언하기
template <typename K, typename V>
class Entry_KV
{
private:
    // key 저장하기
    K key;

    // value 저장하기
    V value;

public:
    // 기본 생성자
    Entry_KV()
    {}

    // key와 value를 초기화하는 생성자
    Entry_KV(const K& k, const V& v)
        : key(k), value(v)
    {}

    // key 반환하기
    const K& getKey() const
    {
        return key;
    }

    // value 반환하기
    const V& getValue() const
    {
        return value;
    }

    // value 수정하기
    void setValue(const V& v)
    {
        value = v;
    }
};

#endif