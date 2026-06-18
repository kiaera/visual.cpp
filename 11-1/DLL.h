/*
DLL.h
project : DLL template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// DLL_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef DLL_H

// DLL_H 매크로 정의하기
#define DLL_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// DLLN template class를 사용하기 위한 헤더파일
#include "DLLN.h"

// 한 줄에 출력할 원소 개수 정의하기
#define ELEMENTS_PER_LINE 10

// 이중 연결 리스트 template class 선언하기
template<typename E>
class DLL
{
    // DLL 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream& fout, const DLL<E>& dll_E)
    {
        DLLN<E>* p = dll_E.head;

        if (dll_E.isEmpty())
        {
            fout << dll_E.name << " is Empty now !!" << std::endl;
            return fout;
        }

        int count = 0;
        while (p != nullptr)
        {
            fout << *(p->getElem()) << "   ";
            count++;

            if (count % ELEMENTS_PER_LINE == 0)
            {
                fout << std::endl;
            }

            p = p->getNext();
        }

        fout << std::endl;
        return fout;
    }

public:
    // 생성자
    DLL(std::string n)
    {
        name = n;
        num_entry = 0;
        element_type = "";
        head = nullptr;
        tail = nullptr;
    }

    // 소멸자
    ~DLL()
    {
        while (!isEmpty())
        {
            removeFront();
        }
    }

    // 이름 반환하기
    std::string getName()
    {
        return this->name;
    }

    // 이름 설정하기
    void setName(std::string n)
    {
        name = n;
    }

    // 리스트가 비어 있는지 확인하기
    bool isEmpty() const
    {
        return num_entry == 0;
    }

    // 첫 번째 노드 반환하기
    DLLN<E>* front() const
    {
        return head;
    }

    // 마지막 노드 반환하기
    DLLN<E>* back() const
    {
        return tail;
    }

    // 맨 앞에 원소 삽입하기
    DLLN<E>* insertFront(E* pE)
    {
        std::lock_guard<std::mutex> lock(cs_dll);

        DLLN<E>* newNode = new DLLN<E>(pE);

        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }

        num_entry++;
        return newNode;
    }

    // 맨 뒤에 원소 삽입하기
    DLLN<E>* insertBack(E* pE)
    {
        std::lock_guard<std::mutex> lock(cs_dll);

        DLLN<E>* newNode = new DLLN<E>(pE);

        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }

        num_entry++;
        return newNode;
    }

    // 오름차순으로 원소 삽입하기
    DLLN<E>* insertInOrder(E* pE)
    {
        std::lock_guard<std::mutex> lock(cs_dll);

        DLLN<E>* newNode = new DLLN<E>(pE);

        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
            num_entry++;
            return newNode;
        }

        DLLN<E>* p = head;

        while (p != nullptr && *(p->getElem()) < *pE)
        {
            p = p->getNext();
        }

        if (p == head)
        {
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        else if (p == nullptr)
        {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        else
        {
            DLLN<E>* prevNode = p->getPrev();

            prevNode->setNext(newNode);
            newNode->setPrev(prevNode);
            newNode->setNext(p);
            p->setPrev(newNode);
        }

        num_entry++;
        return newNode;
    }

    // 내림차순으로 원소 삽입하기
    DLLN<E>* insertInOrderReverse(E* pE)
    {
        std::lock_guard<std::mutex> lock(cs_dll);

        DLLN<E>* newNode = new DLLN<E>(pE);

        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
            num_entry++;
            return newNode;
        }

        DLLN<E>* p = head;

        while (p != nullptr && *(p->getElem()) > *pE)
        {
            p = p->getNext();
        }

        if (p == head)
        {
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        else if (p == nullptr)
        {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        else
        {
            DLLN<E>* prevNode = p->getPrev();

            prevNode->setNext(newNode);
            newNode->setPrev(prevNode);
            newNode->setNext(p);
            p->setPrev(newNode);
        }

        num_entry++;
        return newNode;
    }

    // 원소 찾기
    DLLN<E>* find(E* pE_Key)
    {
        DLLN<E>* p = head;

        while (p != nullptr)
        {
            if (*(p->getElem()) == *pE_Key)
            {
                return p;
            }

            p = p->getNext();
        }

        return nullptr;
    }

    // 오름차순 리스트에서 원소 찾기
    DLLN<E>* searchInOrder(E* pE_Key)
    {
        DLLN<E>* p = head;

        while (p != nullptr)
        {
            if (*(p->getElem()) == *pE_Key)
            {
                return p;
            }

            if (*(p->getElem()) > *pE_Key)
            {
                return nullptr;
            }

            p = p->getNext();
        }

        return nullptr;
    }

    // 내림차순 리스트에서 원소 찾기
    DLLN<E>* searchInOrderReverse(E* pE_Key)
    {
        DLLN<E>* p = head;

        while (p != nullptr)
        {
            if (*(p->getElem()) == *pE_Key)
            {
                return p;
            }

            if (*(p->getElem()) < *pE_Key)
            {
                return nullptr;
            }

            p = p->getNext();
        }

        return nullptr;
    }

    // 맨 앞 원소 삭제하기
    void removeFront()
    {
        std::lock_guard<std::mutex> lock(cs_dll);

        if (isEmpty())
        {
            return;
        }

        DLLN<E>* deleteNode = head;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = head->getNext();
            head->setPrev(nullptr);
        }

        delete deleteNode;
        num_entry--;
    }

    // 맨 뒤 원소 삭제하기
    void removeBack()
    {
        std::lock_guard<std::mutex> lock(cs_dll);

        if (isEmpty())
        {
            return;
        }

        DLLN<E>* deleteNode = tail;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->getPrev();
            tail->setNext(nullptr);
        }

        delete deleteNode;
        num_entry--;
    }

    // 원소 개수 반환하기
    int getNumEntry()
    {
        return num_entry;
    }

    // 원소 타입 반환하기
    std::string getElementType()
    {
        return element_type;
    }

    // 파일 또는 화면으로 리스트 출력하기
    void fprint(std::ostream& fout)
    {
        fout << *this;
    }

protected:
    // 지정한 노드 앞에 새 노드 삽입하기
    DLLN<E>* _insert(DLLN<E>* v, E* pE)
    {
        if (v == nullptr)
        {
            return insertBack(pE);
        }

        if (v == head)
        {
            return insertFront(pE);
        }

        DLLN<E>* newNode = new DLLN<E>(pE);
        DLLN<E>* prevNode = v->getPrev();

        prevNode->setNext(newNode);
        newNode->setPrev(prevNode);
        newNode->setNext(v);
        v->setPrev(newNode);

        num_entry++;
        return newNode;
    }

    // 지정한 노드 삭제하기
    void _remove(DLLN<E>* v)
    {
        if (v == nullptr || isEmpty())
        {
            return;
        }

        if (v == head)
        {
            removeFront();
            return;
        }

        if (v == tail)
        {
            removeBack();
            return;
        }

        DLLN<E>* prevNode = v->getPrev();
        DLLN<E>* nextNode = v->getNext();

        prevNode->setNext(nextNode);
        nextNode->setPrev(prevNode);

        delete v;
        num_entry--;
    }

    // 리스트 이름 저장하기
    std::string name;

    // 원소 개수 저장하기
    int num_entry;

    // 원소 타입 저장하기
    std::string element_type;

    // 첫 번째 노드 주소 저장하기
    DLLN<E>* head;

    // 마지막 노드 주소 저장하기
    DLLN<E>* tail;

    // 동시 접근 제어하기
    std::mutex cs_dll;
};

#endif