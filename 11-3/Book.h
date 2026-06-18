/*
Book.h
project : Book class를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// CLASS_BOOK_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef CLASS_BOOK_H
// CLASS_BOOK_H 매크로 정의하기
#define CLASS_BOOK_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// Book 비교 기준 속성 정의하기
enum ATTR_BOOK { TITLE, PUB_DATE, AUTHOR, PRICE };

// 정렬 순서 정의하기
enum SORT_ORDER { INCR, DECR };

// 서적 정보를 저장하는 클래스 선언하기
class Book
{
    // Book 객체를 입력하기 위한 연산자 오버로딩 함수
    friend std::istream& operator>>(std::istream& fin, Book& bk);

    // Book 객체를 출력하기 위한 연산자 오버로딩 함수
    friend std::ostream& operator<<(std::ostream& fout, const Book& bk);

public:
    // 기본 생성자
    Book();

    // 서적 정보를 초기화하는 생성자
    Book(std::string title, int pub_date, std::string author, double price);

    // 소멸자
    ~Book();

    // 제목 반환하기
    std::string getTitle();

    // 출판일자 반환하기
    int getPubDate();

    // 저자 반환하기
    std::string getAuthor();

    // 가격 반환하기
    double getPrice();

    // 지정한 속성 기준으로 Book 객체 비교하기
    int compareBook(Book& other, ATTR_BOOK keyAttr, SORT_ORDER sort_order);

private:
    // 제목 저장하기
    std::string title;

    // 출판일자 저장하기
    int pub_date;

    // 저자 저장하기
    std::string author;

    // 가격 저장하기
    double price;
};

#endif