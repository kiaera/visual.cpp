/*
DLLN.h
project : DLLN template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// DLLN_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef DLLN_H

// DLLN_H 매크로 정의하기
#define DLLN_H

// template class 선언하기
template<typename E>
class DLLN
{
public:
    // 기본 생성자
    DLLN()
    {
        pE = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    // 원소 포인터를 저장하는 생성자
    DLLN(E* pE)
    {
        this->pE = pE;
        prev = nullptr;
        next = nullptr;
    }

    // 소멸자
    ~DLLN() {}

    // 원소 포인터 반환하기
    E* getElem()
    {
        return pE;
    }

    // 원소 포인터 설정하기
    void setElem(E* pE)
    {
        this->pE = pE;
    }

    // 이전 노드 주소 반환하기
    DLLN<E>* getPrev()
    {
        return this->prev;
    }

    // 다음 노드 주소 반환하기
    DLLN<E>* getNext()
    {
        return this->next;
    }

    // 이전 노드 주소 설정하기
    void setPrev(DLLN<E>* p)
    {
        this->prev = p;
    }

    // 다음 노드 주소 설정하기
    void setNext(DLLN<E>* n)
    {
        this->next = n;
    }

private:
    // 원소 주소 저장하기
    E* pE;

    // 이전 노드 주소 저장하기
    DLLN<E>* prev;

    // 다음 노드 주소 저장하기
    DLLN<E>* next;
};

#endif