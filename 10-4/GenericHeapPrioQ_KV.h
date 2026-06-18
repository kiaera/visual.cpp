/*
GenericHeapPrioQ_KV.h
project : GenericHeapPrioQ_KV template class를 선언하고 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 19, 2026
*/

// HEAP_PRIO_QUEUE_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef HEAP_PRIO_QUEUE_H

// HEAP_PRIO_QUEUE_H 매크로 정의하기
#define HEAP_PRIO_QUEUE_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// mutex 클래스를 사용하기 위한 헤더파일
#include <mutex>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// GenericEntry template class 사용하기 위한 헤더파일
#include "GenericEntry.h"

// CBT root index 정의하기
#define CBT_ROOT 0

// GenericHeapPrioQ_KV template class 선언하기
template<typename K, typename V>
class GenericHeapPrioQ_KV
{
    // 출력 연산자 함수 friend 선언하기
    template<typename K2, typename V2>
    friend std::ostream& operator<<(std::ostream& fout,
        const GenericHeapPrioQ_KV<K2, V2>& ghprioQ);

public:
    // 생성자
    GenericHeapPrioQ_KV(std::string nm, int capa);

    // 소멸자
    ~GenericHeapPrioQ_KV()
    {
        delete[] geArray;
    }

    // 우선순위 큐가 비어있는지 확인하기
    bool isEmpty()
    {
        return (end < 0);
    }

    // 우선순위 큐가 가득 찼는지 확인하기
    bool isFull()
    {
        return (end >= capacity - 1);
    }

    // 원소 삽입하기
    GenericEntry<K, V>* push(const GenericEntry<K, V> elem);

    // 최고 우선순위 원소 삭제하기
    GenericEntry<K, V>* pop();

    // 최고 우선순위 원소 반환하기
    GenericEntry<K, V> top()
    {
        return geArray[CBT_ROOT];
    }

    // 현재 원소 개수 반환하기
    int get_num_elements()
    {
        return num_elements;
    }

    // 마지막 위치에 원소 추가하기
    int add_at_end(const GenericEntry<K, V>& elem)
    {
        if (isFull())
        {
            return -1;
        }

        end++;
        geArray[end] = elem;
        num_elements++;

        return end;
    }

    // 마지막 원소 반환하기
    GenericEntry<K, V> getEndElement()
    {
        return geArray[end];
    }

    // root 원소 반환하기
    GenericEntry<K, V> getRootElement()
    {
        return geArray[CBT_ROOT];
    }

    // 마지막 index 반환하기
    int getEndIndex()
    {
        return end;
    }

    // 마지막 원소 제거하기
    void removeCBTEnd()
    {
        if (!isEmpty())
        {
            end--;
            num_elements--;
        }
    }

    // 부모 index 반환하기
    int parentIndex(int index)
    {
        return (index - 1) / 2;
    }

    // 왼쪽 자식 index 반환하기
    int leftChildIndex(int index)
    {
        return index * 2 + 1;
    }

    // 오른쪽 자식 index 반환하기
    int rightChildIndex(int index)
    {
        return index * 2 + 2;
    }

    // 왼쪽 자식 존재 여부 확인하기
    bool hasLeftChild(int index)
    {
        return (leftChildIndex(index) <= end);
    }

    // 오른쪽 자식 존재 여부 확인하기
    bool hasRightChild(int index)
    {
        return (rightChildIndex(index) <= end);
    }

private:
    // 우선순위 큐 이름 저장하기
    std::string name;

    // GenericEntry 배열 주소 저장하기
    GenericEntry<K, V>* geArray;

    // 우선순위 큐 최대 크기 저장하기
    int capacity;

    // 현재 원소 개수 저장하기
    int num_elements;

    // 마지막 원소 index 저장하기
    int end;

    // 임계구역 보호용 mutex 객체 선언하기
    std::mutex mtx_PrioQ;
};

// 생성자 구현하기
template<typename K, typename V>
GenericHeapPrioQ_KV<K, V>::GenericHeapPrioQ_KV(std::string nm, int capa)
{
    // 우선순위 큐 이름 저장하기
    name = nm;

    // 우선순위 큐 최대 크기 저장하기
    capacity = capa;

    // 현재 원소 개수 초기화하기
    num_elements = 0;

    // 마지막 원소 index 초기화하기
    end = -1;

    // GenericEntry 배열 동적 생성하기
    geArray = new GenericEntry<K, V>[capacity];
}

// 원소 삽입 함수 구현하기
template<typename K, typename V>
GenericEntry<K, V>* GenericHeapPrioQ_KV<K, V>::push(const GenericEntry<K, V> elem)
{
    // 임계구역 시작하기
    mtx_PrioQ.lock();

    // 우선순위 큐가 가득 찬 경우 처리하기
    if (isFull())
    {
        // 임계구역 끝내기
        mtx_PrioQ.unlock();

        return NULL;
    }

    // 마지막 위치에 원소 추가하기
    int curIndex = add_at_end(elem);

    // min-heap 조건을 만족하도록 위로 이동하기
    while (curIndex > CBT_ROOT)
    {
        // 부모 index 저장하기
        int parent = parentIndex(curIndex);

        // 부모 key가 더 작거나 같으면 min-heap 조건 만족하기
        if (geArray[curIndex].getKey() >= geArray[parent].getKey())
        {
            break;
        }

        // 현재 원소와 부모 원소 교환하기
        GenericEntry<K, V> temp = geArray[curIndex];
        geArray[curIndex] = geArray[parent];
        geArray[parent] = temp;

        // 현재 index를 부모 index로 변경하기
        curIndex = parent;
    }

    // 삽입된 원소 주소 저장하기
    GenericEntry<K, V>* pElem = &geArray[curIndex];

    // 임계구역 끝내기
    mtx_PrioQ.unlock();

    return pElem;
}

// 최고 우선순위 원소 삭제 함수 구현하기
template<typename K, typename V>
GenericEntry<K, V>* GenericHeapPrioQ_KV<K, V>::pop()
{
    // 임계구역 시작하기
    mtx_PrioQ.lock();

    // 우선순위 큐가 비어있는 경우 처리하기
    if (isEmpty())
    {
        // 임계구역 끝내기
        mtx_PrioQ.unlock();

        return NULL;
    }

    // root 원소를 반환하기 위해 동적 생성하기
    GenericEntry<K, V>* pRoot = new GenericEntry<K, V>;

    // root 원소 복사하기
    *pRoot = geArray[CBT_ROOT];

    // 마지막 원소를 root 위치로 이동하기
    geArray[CBT_ROOT] = geArray[end];

    // 마지막 원소 제거하기
    removeCBTEnd();

    // 현재 index를 root로 설정하기
    int curIndex = CBT_ROOT;

    // min-heap 조건을 만족하도록 아래로 이동하기
    while (hasLeftChild(curIndex))
    {
        // 더 작은 자식 index 저장하기
        int smallerChild = leftChildIndex(curIndex);

        // 오른쪽 자식이 있고 오른쪽 자식의 key가 더 작은 경우 처리하기
        if (hasRightChild(curIndex)
            && geArray[rightChildIndex(curIndex)].getKey() < geArray[smallerChild].getKey())
        {
            smallerChild = rightChildIndex(curIndex);
        }

        // 현재 원소 key가 더 작거나 같으면 min-heap 조건 만족하기
        if (geArray[curIndex].getKey() <= geArray[smallerChild].getKey())
        {
            break;
        }

        // 현재 원소와 더 작은 자식 원소 교환하기
        GenericEntry<K, V> temp = geArray[curIndex];
        geArray[curIndex] = geArray[smallerChild];
        geArray[smallerChild] = temp;

        // 현재 index를 더 작은 자식 index로 변경하기
        curIndex = smallerChild;
    }

    // 임계구역 끝내기
    mtx_PrioQ.unlock();

    return pRoot;
}

// 우선순위 큐 출력 연산자 함수 구현하기
template<typename K, typename V>
std::ostream& operator<<(std::ostream& fout,
    const GenericHeapPrioQ_KV<K, V>& ghprioQ)
{
    // 우선순위 큐가 비어있는 경우 처리하기
    if (ghprioQ.num_elements == 0)
    {
        fout << "HeapPrioQ_Event is empty now !!" << std::endl;

        return fout;
    }

    // 배열 순서대로 원소 출력하기
    for (int i = 0; i <= ghprioQ.end; i++)
    {
        fout << ghprioQ.geArray[i] << " ";
    }

    fout << std::endl;

    return fout;
}

#endif