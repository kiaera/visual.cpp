/*
GenericArray.h
project : 다양한 자료형의 배열을 저장하고 삽입정렬하는 GenericArray template class를 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

// GENERICARRAY_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GENERICARRAY_H

// GENERICARRAY_H 매크로 정의하기
#define GENERICARRAY_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 출력 정렬을 사용하기 위한 헤더파일
#include <iomanip>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// rand(), srand() 함수를 사용하기 위한 헤더파일
#include <cstdlib>

// time() 함수를 사용하기 위한 헤더파일
#include <ctime>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// GenericArray template class 전방 선언하기
template<typename T>
class GenericArray;

// 입력 연산자 함수 전방 선언하기
template<typename T>
istream& operator>>(istream& fin, GenericArray<T>& ga);

// 출력 연산자 함수 전방 선언하기
template<typename T>
ostream& operator<<(ostream& fout, const GenericArray<T>& ga);

// 다양한 자료형의 배열을 저장하는 template class
template<typename T>
class GenericArray
{
    // 파일이나 키보드로 배열 데이터를 입력받기 위한 함수
    friend istream& operator>> <T>(istream& fin, GenericArray<T>& ga);

    // 배열 데이터를 출력하기 위한 함수
    friend ostream& operator<< <T>(ostream& fout, const GenericArray<T>& ga);

public:
    // 생성자
    GenericArray(string nm, int capacity = 0);

    // 소멸자
    ~GenericArray();

    // 중복되지 않는 난수 배열 생성 함수
    void Gen_Big_Rand_Array(int size, T offset);

    // 배열 원소 개수 설정 함수
    void Set_Num_Elements(int num_elements)
    {
        this->num_elements = num_elements;
    }

    // 배열 원소를 섞는 함수
    void Shuffle();

    // 삽입정렬 수행 함수
    void Insert_Sort();

    // 배열 출력 함수
    void Print_Array(int per_line, int sample_lines);

    // 배열 시작 주소 반환 함수
    T* getGA()
    {
        return GA;
    }

protected:
    // 배열 이름 저장하기
    string name;

    // 동적 배열 저장하기
    T* GA;

    // 현재 저장된 원소 개수 저장하기
    int num_elements;

    // 최대 저장 가능 개수 저장하기
    int capacity;
};

// 생성자 구현하기
template<typename T>
GenericArray<T>::GenericArray(string nm, int capacity)
{
    // 배열 이름 저장하기
    this->name = nm;

    // 최대 저장 가능 개수 저장하기
    this->capacity = capacity;

    // 현재 원소 개수 0으로 초기화하기
    this->num_elements = 0;

    // capacity가 0보다 크면 동적 배열 생성하기
    if (capacity > 0)
        GA = new T[capacity];

    // 그렇지 않으면 nullptr 저장하기
    else
        GA = nullptr;
}

// 소멸자 구현하기
template<typename T>
GenericArray<T>::~GenericArray()
{
    // 동적 배열 메모리 해제하기
    if (GA != nullptr)
        delete[] GA;
}

// 입력 연산자 함수 구현하기
template<typename T>
istream& operator>>(istream& fin, GenericArray<T>& ga)
{
    // 파일에 저장된 배열 이름 저장하기
    string data_name;

    // 배열 크기 저장하기
    int size;

    // 배열 이름과 크기 입력받기
    fin >> data_name >> size;

    // 배열 이름 저장하기
    ga.name = data_name;

    // 최대 저장 가능 개수 저장하기
    ga.capacity = size;

    // 현재 원소 개수 저장하기
    ga.num_elements = size;

    // 기존 동적 배열이 존재하면 메모리 해제하기
    if (ga.GA != nullptr)
        delete[] ga.GA;

    // 새로운 동적 배열 생성하기
    ga.GA = new T[size];

    // 배열 데이터 입력받기
    for (int i = 0; i < size; i++)
        fin >> ga.GA[i];

    return fin;
}

// 출력 연산자 함수 구현하기
template<typename T>
ostream& operator<<(ostream& fout, const GenericArray<T>& ga)
{
    // 배열 원소 출력하기
    for (int i = 0; i < ga.num_elements; i++)
        fout << ga.GA[i] << " ";

    return fout;
}

// 중복되지 않는 난수 배열 생성 함수 구현하기
template<typename T>
void GenericArray<T>::Gen_Big_Rand_Array(int size, T offset)
{
    // 기존 동적 배열이 존재하면 메모리 해제하기
    if (GA != nullptr)
        delete[] GA;

    // 최대 저장 가능 개수 저장하기
    capacity = size;

    // 현재 원소 개수 저장하기
    num_elements = size;

    // 새로운 동적 배열 생성하기
    GA = new T[size];

    // offset을 더한 값 저장하기
    for (int i = 0; i < size; i++)
        GA[i] = static_cast<T>(i) + offset;

    // 배열 원소 섞기
    Shuffle();
}

// 배열 원소를 섞는 함수 구현하기
template<typename T>
void GenericArray<T>::Shuffle()
{
    // 난수 발생기 초기화하기
    srand((unsigned int)time(NULL));

    // 배열 원소 서로 교환하기
    for (int i = 0; i < num_elements; i++)
    {
        // 큰 범위의 난수 인덱스 생성하기
        int j = ((rand() << 15) + rand()) % num_elements;

        // 두 원소 교환하기
        T temp = GA[i];
        GA[i] = GA[j];
        GA[j] = temp;
    }
}

// 삽입정렬 함수 구현하기
template<typename T>
void GenericArray<T>::Insert_Sort()
{
    // 두 번째 원소부터 정렬 수행하기
    for (int i = 1; i < num_elements; i++)
    {
        // 현재 삽입할 값 저장하기
        T key = GA[i];

        // 비교 시작 위치 저장하기
        int j = i - 1;

        // key보다 큰 값을 뒤로 이동하기
        while (j >= 0 && GA[j] > key)
        {
            GA[j + 1] = GA[j];
            j--;
        }

        // 올바른 위치에 key 삽입하기
        GA[j + 1] = key;
    }
}

// 배열 출력 함수 구현하기
template<typename T>
void GenericArray<T>::Print_Array(int per_line, int sample_lines)
{
    // 출력할 전체 원소 개수 계산하기
    int count = per_line * sample_lines;

    // 출력 개수가 실제 원소 개수보다 크면 조정하기
    if (count > num_elements)
        count = num_elements;

    // 배열 원소 출력하기
    for (int i = 0; i < count; i++)
    {
        cout << setw(8) << GA[i];

        // 한 줄 출력 완료 시 줄바꿈하기
        if ((i + 1) % per_line == 0)
            cout << endl;
    }

    // 마지막 줄이 꽉 차지 않았으면 줄바꿈하기
    if (count % per_line != 0)
        cout << endl;
}

#endif