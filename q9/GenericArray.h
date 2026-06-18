/*
GenericArray.h
project : 다양한 자료형의 배열을 저장하고 삽입정렬하는 GenericArray template class를 구현한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

// GENERICARRAY_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GENERIC_ARRAY_H

// GENERICARRAY_H 매크로 정의하기
#define GENERIC_ARRAY_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// GenericArray template class 전방 선언하기
template<typename T>

// 다양한 자료형의 배열을 저장하는 template class 생성하기
class GenericArray {

    // 파일로부터 배열 데이터를 이력받기 위한 함수
    friend std::istream& operator>>(std::istream& is, GenericArray<T>& ga) {
        std::string title;
        int count;
        if (is >> title >> count) {
            ga.num_elements = 0;
            // 지정된 개수만큼 배열에 데이터를 읽어오기
            for (int i = 0; i < count && i < ga.capacity; ++i) {
                if (is >> ga.GA[i]) {
                    ga.num_elements++;
                }
                else {
                    break;
                }
            }
        }
        return is;
    }

    // 배열 데이터를 출력하기 위한 함수
    friend std::ostream& operator<<(std::ostream& os, const GenericArray<T>& ga) {
        os << ga.name << "(num_elements : " << ga.num_elements << ") =\n";
        // 한줄에 10개씩 정렬하여 출력하기
        for (int i = 0; i < ga.num_elements; ++i) {
            os << std::setw(9) << ga.GA[i];
            if ((i + 1) % 10 == 0 && i != ga.num_elements - 1) {
                os << "\n";
            }
        }
        return os;
    }

public:
    // 생성자
    GenericArray(std::string nm = "", int capacity = 20) {
        this->name = nm;
        this->capacity = capacity;
        this->num_elements = 0;
        this->GA = new T[capacity];
    }

    // 소멸자
    ~GenericArray() {
        if (GA != nullptr) {
            delete[] GA;
        }
    }

    // 삽입 정렬 실행하기
    void insertSort() {
        for (int i = 1; i < num_elements; ++i) {
            T key = GA[i];
            int j = i - 1;
            while (j >= 0 && GA[j] > key) {
                GA[j + 1] = GA[j];
                j--;
            }
            GA[j + 1] = key;
        }
    }

    /*
    배열 이름, 최대 저장가능 개수, 
    현재 저장된 원소 개수 동적배열 저장하기
    */
protected:
    std::string name;
    T* GA;
    int num_elements;
    int capacity; 
};

#endif

