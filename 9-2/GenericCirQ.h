/*
GenericCirQ.h
project : GenericArray template class를 상속받아 환형 큐 GenericCirQ template class를 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

// GENERICCIRQ_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GENERICCIRQ_H

// GENERICCIRQ_H 매크로 정의하기
#define GENERICCIRQ_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// GenericArray template class를 사용하기 위한 헤더파일
#include "GenericArray.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// GenericCirQ template class 전방 선언하기
template<typename T>
class GenericCirQ;

// 출력 연산자 함수 전방 선언하기
template<typename T>
ostream& operator<<(ostream& fout, const GenericCirQ<T>& gCirQ);

// 환형 큐를 구현한 template class
template<typename T>
class GenericCirQ : public GenericArray<T>
{
    // 환형 큐 객체 출력 함수
    friend ostream& operator<< <T>(ostream& fout, const GenericCirQ<T>& gCirQ);

public:
    // 생성자
    GenericCirQ(string nm, int capacity);

    // 소멸자
    ~GenericCirQ() {}

    // 환형 큐의 front 데이터를 제거하는 함수
    T* dequeue();

    // 환형 큐의 back 위치에 데이터 삽입하는 함수
    T* enqueue(const T element);

    // 환형 큐가 비어있는지 확인하는 함수
    bool is_Empty()
    {
        return (this->num_elements == 0);
    }

    // 환형 큐가 가득 찼는지 확인하는 함수
    bool is_Full()
    {
        return (this->num_elements >= this->capacity);
    }

    // 현재 저장된 원소 개수 반환 함수
    int size()
    {
        return this->num_elements;
    }

    // 환형 큐 출력 함수
    void fprint(ostream& fout, int elements_per_line);

private:
    // 환형 큐의 front 위치 저장하기
    int front;

    // 환형 큐의 back 위치 저장하기
    int back;
};

// 생성자 구현하기
template<typename T>
GenericCirQ<T>::GenericCirQ(string nm, int capacity)
    : GenericArray<T>(nm, capacity)
{
    // front 위치 초기화하기
    front = 0;

    // back 위치 초기화하기
    back = 0;
}

// 환형 큐의 back 위치에 데이터 삽입하는 함수 구현하기
template<typename T>
T* GenericCirQ<T>::enqueue(const T element)
{
    // 환형 큐가 가득 찼으면 nullptr 반환하기
    if (is_Full())
        return nullptr;

    // back 위치에 데이터 저장하기
    this->GA[back] = element;

    // back 위치를 다음 칸으로 이동하기
    back = (back + 1) % this->capacity;

    // 현재 저장된 원소 개수 증가시키기
    this->num_elements++;

    // 삽입된 데이터 주소 반환하기
    return &(this->GA[(back - 1 + this->capacity) % this->capacity]);
}

// 환형 큐의 front 데이터를 제거하는 함수 구현하기
template<typename T>
T* GenericCirQ<T>::dequeue()
{
    // 환형 큐가 비어있으면 nullptr 반환하기
    if (is_Empty())
        return nullptr;

    // 제거할 데이터 주소 저장하기
    T* pE = &(this->GA[front]);

    // front 위치를 다음 칸으로 이동하기
    front = (front + 1) % this->capacity;

    // 현재 저장된 원소 개수 감소시키기
    this->num_elements--;

    // 제거된 데이터 주소 반환하기
    return pE;
}

// 환형 큐 출력 함수 구현하기
template<typename T>
void GenericCirQ<T>::fprint(ostream& fout, int elements_per_line)
{
    // 환형 큐가 비어있는 경우 출력하기
    if (is_Empty())
    {
        fout << "CirQ is empty now !!" << endl;
        return;
    }

    // 환형 큐 원소 출력하기
    for (int i = 0; i < this->num_elements; i++)
    {
        // 실제 배열 인덱스 계산하기
        int index = (front + i) % this->capacity;

        // 배열 원소 출력하기
        fout << this->GA[index];

        // 마지막 원소가 아니면 쉼표 출력하기
        if (i != this->num_elements - 1)
            fout << ", ";
    }

    fout << endl;
}

// 출력 연산자 함수 구현하기
template<typename T>
ostream& operator<<(ostream& fout, const GenericCirQ<T>& gCirQ)
{
    // 환형 큐 정보 출력하기
    fout << gCirQ.name
        << "(capacity= " << gCirQ.capacity
        << ", current num_elements = "
        << gCirQ.num_elements << ") : ";

    // 환형 큐가 비어있는 경우 출력하기
    if (gCirQ.num_elements == 0)
    {
        fout << "CirQ is empty now !!" << endl;
        return fout;
    }

    // 환형 큐 원소 출력하기
    for (int i = 0; i < gCirQ.num_elements; i++)
    {
        // 실제 배열 인덱스 계산하기
        int index = (gCirQ.front + i) % gCirQ.capacity;

        // 배열 원소 출력하기
        fout << gCirQ.GA[index];

        // 마지막 원소가 아니면 쉼표 출력하기
        if (i != gCirQ.num_elements - 1)
            fout << ", ";
    }

    fout << endl;

    return fout;
}

// GENERICCIRQ_H 끝내기
#endif