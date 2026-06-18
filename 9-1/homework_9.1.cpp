/*
main.cpp
project : GenericArray template class를 이용하여 int, double, string 배열을 입력받고 삽입정렬하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 14, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력을 사용하기 위한 헤더파일
#include <fstream>

// 프로그램 종료 함수를 사용하기 위한 헤더파일
#include <cstdlib>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// GenericArray template class를 사용하기 위한 헤더파일
#include "GenericArray.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

/*
파일로부터 int, double, string 데이터를 입력받아
삽입정렬 전후 결과를 출력하는 함수
*/
int main()
{
    // 입력 파일 객체 선언하기
    fstream fin_int, fin_dbl, fin_str;

    // 한 줄에 출력할 개수 저장하기
    int per_line = 10;

    // 출력할 줄 수 저장하기
    int sample_lines = 2;

    // int 데이터 파일 열기
    fin_int.open("intArray_data.txt");

    // 파일 열기 실패 확인하기
    if (fin_int.fail())
    {
        cout << "Error in reading int_array data file (intArray_data.txt) !!!" << endl;
        exit(1);
    }

    // int형 GenericArray 객체 생성하기
    GenericArray<int> ga_Int("GA_Int");

    // 파일 데이터 입력받기
    fin_int >> ga_Int;

    // 파일 닫기
    fin_int.close();

    // 정렬 전 배열 출력하기
    cout << "ga_int before sorting : " << endl;
    ga_Int.Print_Array(per_line, sample_lines);
    cout << endl;

    // 삽입정렬 수행하기
    ga_Int.Insert_Sort();

    // 정렬 후 배열 출력하기
    cout << "ga_int after sorting : " << endl;
    ga_Int.Print_Array(per_line, sample_lines);
    cout << endl;

    // double 데이터 파일 열기
    fin_dbl.open("dblArray_data.txt");

    // 파일 열기 실패 확인하기
    if (fin_dbl.fail())
    {
        cout << "Error in reading dbl_array data file (dblArray_data.txt) !!!" << endl;
        exit(1);
    }

    // double형 GenericArray 객체 생성하기
    GenericArray<double> ga_Dbl("GA_Double");

    // 파일 데이터 입력받기
    fin_dbl >> ga_Dbl;

    // 파일 닫기
    fin_dbl.close();

    // 정렬 전 배열 출력하기
    cout << "ga_Dbl before sorting : " << endl;
    cout << fixed << setprecision(2);
    ga_Dbl.Print_Array(per_line, sample_lines);
    cout << endl;

    // 삽입정렬 수행하기
    ga_Dbl.Insert_Sort();

    // 정렬 후 배열 출력하기
    cout << "ga_Dbl after sorting : " << endl;
    cout << fixed << setprecision(2);
    ga_Dbl.Print_Array(per_line, sample_lines);
    cout << endl;

    // string 데이터 파일 열기
    fin_str.open("strArray_data.txt");

    // 파일 열기 실패 확인하기
    if (fin_str.fail())
    {
        cout << "Error in reading str_array data file (strArray_data.txt) !!!" << endl;
        exit(1);
    }

    // string형 GenericArray 객체 생성하기
    GenericArray<string> ga_str("GA_String");

    // 파일 데이터 입력받기
    fin_str >> ga_str;

    // 파일 닫기
    fin_str.close();

    // 정렬 전 배열 출력하기
    cout << "ga_str before sorting : " << endl;
    ga_str.Print_Array(per_line, sample_lines);
    cout << endl;

    // 삽입정렬 수행하기
    ga_str.Insert_Sort();

    // 정렬 후 배열 출력하기
    cout << "ga_str after sorting : " << endl;
    ga_str.Print_Array(per_line, sample_lines);
    cout << endl;

    return 0;
}