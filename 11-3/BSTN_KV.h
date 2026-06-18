/*
BSTN_KV.h
project : Generic Binary Search Tree Node template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// BSTN_KV_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef BSTN_KV_H
// BSTN_KV_H 매크로 정의하기
#define BSTN_KV_H

// Generic Binary Search Tree Node template class 선언하기
template<typename K, typename V>
class BSTN_KV
{
public:
    // 기본 생성자
    BSTN_KV()
        : key(), value(), pPr(nullptr), pLc(nullptr), pRc(nullptr)
    {}

    // key와 value를 초기화하는 생성자
    BSTN_KV(K key, V value)
        : key(key), value(value), pPr(nullptr), pLc(nullptr), pRc(nullptr)
    {}

    // key 설정하기
    void setKey(K key)
    {
        this->key = key;
    }

    // value 설정하기
    void setValue(V value)
    {
        this->value = value;
    }

    // key 반환하기
    K getKey()
    {
        return this->key;
    }

    // value 반환하기
    V getValue()
    {
        return this->value;
    }

    // 부모 노드 주소 반환하기
    BSTN_KV<K, V>* getpPr()
    {
        return pPr;
    }

    // 왼쪽 자식 노드 주소 반환하기
    BSTN_KV<K, V>* getpLc()
    {
        return pLc;
    }

    // 오른쪽 자식 노드 주소 반환하기
    BSTN_KV<K, V>* getpRc()
    {
        return pRc;
    }

    // 왼쪽 자식 노드 주소의 주소 반환하기
    BSTN_KV<K, V>** getppLc()
    {
        return &pLc;
    }

    // 오른쪽 자식 노드 주소의 주소 반환하기
    BSTN_KV<K, V>** getppRc()
    {
        return &pRc;
    }

    // 부모 노드 주소 설정하기
    void setpPr(BSTN_KV<K, V>* pTN)
    {
        pPr = pTN;
    }

    // 왼쪽 자식 노드 주소 설정하기
    void setpLc(BSTN_KV<K, V>* pTN)
    {
        pLc = pTN;
    }

    // 오른쪽 자식 노드 주소 설정하기
    void setpRc(BSTN_KV<K, V>* pTN)
    {
        pRc = pTN;
    }

private:
    // key 저장하기
    K key;

    // value 저장하기
    V value;

    // 부모 노드 주소 저장하기
    BSTN_KV<K, V>* pPr;

    // 왼쪽 자식 노드 주소 저장하기
    BSTN_KV<K, V>* pLc;

    // 오른쪽 자식 노드 주소 저장하기
    BSTN_KV<K, V>* pRc;
};

#endif