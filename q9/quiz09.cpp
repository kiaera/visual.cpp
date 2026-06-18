/*
main.cpp
project : GenericArray template class를 이용하여 double, string 배열을 입력받고 삽입정렬하여 출력하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 15, 2026
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

// GenericArray template class를 사용하기 위한 헤더파일
#include "GenericArray.h"

using namespace std;

/*
텍스트 파일로부터 다양한 타입의 데이터를 받아와 
배열에 저장하고 삽입정렬하여 출력하는 함수
*/
int main()
{
    // 입력 파일 객체 선언하기
    fstream fin_dbl, fin_str;

    // 한 줄에 출력할 개수, 출력할 줄 수 저장하기
    int per_line = 10, sample_lines = 2;

    // double 데이터 파일 열기
    fin_dbl.open("dblArray_data.txt");

    // 파일 열기 실패 확인하기
    if (fin_dbl.fail()) {
        cout << "Error in reading dblArray_data.txt !!!" << endl;
        exit(1);
    }

    // double형 GenericArray 객체 생성하기
    GenericArray<double> ga_dbl("DoubleArrayData", 20);

    // 파일 데이터 입력받기
    fin_dbl >> ga_dbl;

    // 파일 닫기
    fin_dbl.close();

    // 정렬 전 배열 출력하기
    cout << "ga_dbl before sorting :\n" << ga_dbl << endl;

    // 삽입정렬 수행하기
    ga_dbl.insertSort();

    // 정렬 후 배열 출력하기
    cout << endl << "ga_dbl after sorting :\n" << ga_dbl << endl;

    // string 데이터 파일 열기
    fin_str.open("strArray_data.txt");

    // 파일 열기 실패 확인하기
    if (fin_str.fail()) {
        cout << "Error in reading strArray_data.txt !!!" << endl;
        exit(1);
    }

    // string형 GenericArray 객체 생성하기
    GenericArray<string> ga_str("StringArrayData", 20); 

    // 파일 데이터 입력받기
    fin_str >> ga_str;

    // 파일 닫기
    fin_str.close();

    // 정렬 전 배열 출력하기
    cout << endl << "ga_str before sorting :\n" << ga_str << endl;

    // 삽입정렬 수행하기
    ga_str.insertSort();

    // 정렬 후 배열 출력하기
    cout << endl << "ga_str after sorting :\n" << ga_str << endl;

    return 0;
}
