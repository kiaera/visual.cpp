/*
GenericCirQ.h
project : GenericCirQ template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// GENERIC_CIRQ_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GENERIC_CIRQ_H

// GENERIC_CIRQ_H 매크로 정의하기
#define GENERIC_CIRQ_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// thread 클래스를 사용하기 위한 헤더파일
#include <thread>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// GenericCirQ template class 전방 선언하기
template<typename T>
class Generic_CirQ;

// 출력 연산자 함수 전방 선언하기
template<typename T>
std::ostream& operator<<(std::ostream& fout,
    const Generic_CirQ<T>& gCirQ);

// GenericCirQ template class 선언하기
template<typename T>
class Generic_CirQ
{
    // 출력 연산자 함수 friend 선언하기
    friend std::ostream& operator<< <T>(
        std::ostream& fout,
        const Generic_CirQ<T>& gCirQ);

public:
    // 생성자
    Generic_CirQ(std::string nm, int capa)
    {
        // 큐 이름 저장하기
        name = nm;

        // 큐 최대 크기 저장하기
        capacity = capa;

        // 현재 저장된 원소 개수 초기화하기
        num_elements = 0;

        // front 인덱스 초기화하기
        front = 0;

        // back 인덱스 초기화하기
        back = 0;

        // 동적 배열 생성하기
        GA = new T[capacity];
    }

    // 소멸자
    ~Generic_CirQ()
    {
        // 동적 배열 해제하기
        delete[] GA;
    }

    // enqueue 함수 선언하기
    T* enqueue(const T element);

    // dequeue 함수 선언하기
    T* dequeue();

    // 큐가 비어있는지 확인하기
    bool isEmpty()
    {
        return (num_elements == 0);
    }

    // 큐가 가득 찼는지 확인하기
    bool isFull()
    {
        return (num_elements >= capacity);
    }

    // 현재 저장된 원소 개수 반환하기
    int Get_Num_Elements()
    {
        return num_elements;
    }

private:
    // 큐 이름 저장하기
    std::string name;

    // 동적 배열 주소 저장하기
    T* GA;

    // 현재 저장된 원소 개수 저장하기
    int num_elements;

    // 큐 최대 크기 저장하기
    int capacity;

    // front 인덱스 저장하기
    int front;

    // back 인덱스 저장하기
    int back;

    // 임계구역 보호용 mutex 객체 선언하기
    std::mutex mtx_criQ;
};

// GenericCirQ 객체 출력 함수 구현하기
template<typename T>
std::ostream& operator<<(std::ostream& fout,
    const Generic_CirQ<T>& gCirQ)
{
    // 큐 상태 출력하기
    fout << gCirQ.name
        << "(capacity= "
        << gCirQ.capacity
        << ", current num_elements = "
        << gCirQ.num_elements
        << ") :"
        << std::endl;

    // 큐가 비어있는 경우 처리하기
    if (gCirQ.num_elements == 0)
    {
        fout << "CirQ is empty now !!"
            << std::endl;

        return fout;
    }

    // 현재 출력할 인덱스 저장하기
    int index = gCirQ.front;

    // 큐 원소 출력 반복하기
    for (int i = 0; i < gCirQ.num_elements; i++)
    {
        fout << gCirQ.GA[index] << " ";

        // 다음 인덱스로 이동하기
        index = (index + 1) % gCirQ.capacity;
    }

    fout << std::endl;

    return fout;
}

// enqueue 함수 구현하기
template<typename T>
T* Generic_CirQ<T>::enqueue(const T element)
{
    // 임계구역 시작하기
    mtx_criQ.lock();

    // 큐가 가득 찬 경우 처리하기
    if (isFull())
    {
        // 임계구역 끝내기
        mtx_criQ.unlock();

        return NULL;
    }

    // back 위치에 원소 저장하기
    GA[back] = element;

    // 저장된 원소 주소 저장하기
    T* pElement = &GA[back];

    // back 인덱스 이동하기
    back = (back + 1) % capacity;

    // 원소 개수 증가시키기
    num_elements++;

    // 임계구역 끝내기
    mtx_criQ.unlock();

    return pElement;
}

// dequeue 함수 구현하기
template<typename T>
T* Generic_CirQ<T>::dequeue()
{
    // 임계구역 시작하기
    mtx_criQ.lock();

    // 큐가 비어있는 경우 처리하기
    if (isEmpty())
    {
        // 임계구역 끝내기
        mtx_criQ.unlock();

        return NULL;
    }

    // 반환할 원소 저장 객체 생성하기
    T* pElement = new T;

    // front 위치 원소 복사하기
    *pElement = GA[front];

    // front 인덱스 이동하기
    front = (front + 1) % capacity;

    // 원소 개수 감소시키기
    num_elements--;

    // 임계구역 끝내기
    mtx_criQ.unlock();

    return pElement;
}

// GENERIC_CIRQ_H 종료하기
#endif