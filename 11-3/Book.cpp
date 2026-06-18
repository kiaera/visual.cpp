/*
Book.cpp
project : Book class 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>
// Book class를 사용하기 위한 헤더파일
#include "Book.h"

// 기본 생성자
Book::Book()
    : title(""), pub_date(0), author(""), price(0.0)
{}

// 서적 정보를 초기화하는 생성자
Book::Book(std::string title, int pub_date, std::string author, double price)
    : title(title), pub_date(pub_date), author(author), price(price)
{}

// 소멸자
Book::~Book()
{}

// 제목 반환하기
std::string Book::getTitle()
{
    return this->title;
}

// 출판일자 반환하기
int Book::getPubDate()
{
    return this->pub_date;
}

// 저자 반환하기
std::string Book::getAuthor()
{
    return this->author;
}

// 가격 반환하기
double Book::getPrice()
{
    return this->price;
}

// 지정한 속성 기준으로 Book 객체 비교하기
int Book::compareBook(Book& other, ATTR_BOOK keyAttr, SORT_ORDER sort_order)
{
    int result = 0;

    switch (keyAttr)
    {
    case TITLE:
        if (title < other.title)
        {
            result = -1;
        }
        else if (title > other.title)
        {
            result = 1;
        }
        break;

    case PUB_DATE:
        if (pub_date < other.pub_date)
        {
            result = -1;
        }
        else if (pub_date > other.pub_date)
        {
            result = 1;
        }
        break;

    case AUTHOR:
        if (author < other.author)
        {
            result = -1;
        }
        else if (author > other.author)
        {
            result = 1;
        }
        break;

    case PRICE:
        if (price < other.price)
        {
            result = -1;
        }
        else if (price > other.price)
        {
            result = 1;
        }
        break;
    }

    if (sort_order == DECR)
    {
        result = -result;
    }

    return result;
}

// Book 객체 입력하기
std::istream& operator>>(std::istream& fin, Book& bk)
{
    fin >> bk.title >> bk.pub_date >> bk.author >> bk.price;
    return fin;
}

// Book 객체 출력하기
std::ostream& operator<<(std::ostream& fout, const Book& bk)
{
    fout << "Book( "
        << std::setw(13) << std::left << bk.title << ", "
        << std::setw(8) << std::right << bk.pub_date << ", "
        << std::setw(8) << std::left << bk.author << ", "
        << std::setw(6) << std::right << bk.price << ")";

    return fout;
}