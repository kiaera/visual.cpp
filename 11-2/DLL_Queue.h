/*
DLL_Queue.h
project : DLL template class를 상속받아 FIFO Queue를 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// DLL_QUEUE_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef DLL_QUEUE_H

// DLL_QUEUE_H 매크로 정의하기
#define DLL_QUEUE_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// DLL template class를 사용하기 위한 헤더파일
#include "DLL.h"

// DLL 기반 Queue template class 선언하기
template<typename E>
class DLL_Queue : public DLL<E>
{
    // DLL_Queue 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream& fout, DLL_Queue<E>& dllQ)
    {
        if (dllQ.isEmpty())
        {
            fout << dllQ.getName() << " is Empty now !" << std::endl;
            return fout;
        }

        return fout << static_cast<DLL<E>&>(dllQ);
    }

public:
    // 생성자
    DLL_Queue(std::string nm)
        : DLL<E>(nm)
    {}

    // 소멸자
    ~DLL_Queue()
    {}

    // Queue의 맨 앞 원소를 삭제하고 반환하기
    E* deQueue()
    {
        if (this->isEmpty())
        {
            return nullptr;
        }

        E* pE = this->front()->getElem();
        this->removeFront();

        return pE;
    }

    // Queue의 맨 뒤에 원소 삽입하기
    DLLN<E>* enQueue(E* pE)
    {
        return this->insertBack(pE);
    }
};

#endif