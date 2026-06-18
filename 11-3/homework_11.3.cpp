/*
main.cpp
project : BST_KV template class를 이용하여 Book 정보를 title, price, pub_date 기준으로 정렬하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 파일 입출력 사용하기 위한 헤더파일
#include <fstream>
// vector container를 사용하기 위한 헤더파일
#include <vector>
// 프로그램 종료 함수를 사용하기 위한 헤더파일
#include <cstdlib>
// BST_KV template class를 사용하기 위한 헤더파일
#include "BST_KV.h"
// Book class를 사용하기 위한 헤더파일
#include "Book.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 입력할 서적 개수 정의하기
#define NUM_STAR 10

/*
BST_KV template class를 이용하여 
Book 정보를 title, price, pub_date 기준으로 정렬하는 메인함수
*/
int main()
{
    // 파일 입력 객체 선언하기
    ifstream fin;

    // 데이터베이스 이름 저장하기
    string db_name;

    // 서적 개수 저장하기
    int num_books;

    // Book 배열 주소 저장하기
    Book* books;

    // 입력 파일 열기
    fin.open("Book_DB.txt");

    // 입력 파일 열기 실패 확인하기
    if (fin.fail())
    {
        cout << "Fail to open input data file (Book_DB.txt) !!" << endl;
        return 1;
    }

    // 데이터베이스 이름과 서적 개수 입력받기
    fin >> db_name >> num_books;

    // 입력 데이터 개수 확인하기
    if (num_books <= 0)
    {
        cout << "Input data file (Book_DB.txt) does not contain correct data !!!" << endl;
        return 1;
    }

    // Book 배열 동적 생성하기
    books = new Book[num_books]();

    // Book 정보 입력받기
    for (int i = 0; i < num_books; i++)
    {
        fin >> books[i];
    }

    // 입력 파일 닫기
    fin.close();

    // 초기 Book 정보 출력하기
    cout << "Initialized status of books : " << endl;

    for (int i = 0; i < num_books; i++)
    {
        cout << books[i] << endl;
    }

    cout << endl;

    // title을 key로 사용하는 Book BST 생성하기
    BST_KV<string, Book*> BST_Book_keyTitle("BST_Book_keyTitle");

    // 루트 주소 확인용 포인터 선언하기
    BSTN_KV<string, Book*>** ppBST_Book_keyTitle_root;

    // title 기준 BST 생성 시작 메시지 출력하기
    cout << "Binary Search Tree of Books (key : title) without Rebalancing" << endl;

    // title 기준 BST 루트 주소 가져오기
    ppBST_Book_keyTitle_root = BST_Book_keyTitle.getRootAddr();

    // title 기준으로 Book 정보 삽입하기
    for (int i = 0; i < NUM_STAR; i++)
    {
        BST_Book_keyTitle.insertInOrder(books[i].getTitle(), &books[i]);
    }

    // title 기준 중위 순회 출력하기
    cout << "Elements in " << BST_Book_keyTitle.getName() << " (in order of Name) :" << endl;
    BST_Book_keyTitle.fprint_inOrder(cout);
    cout << endl;

    // title 기준 BST 구조 출력하기
    BST_Book_keyTitle.fprint_with_Depth(cout);
    cout << endl;

    // price를 key로 사용하는 Book BST 생성하기
    BST_KV<double, Book*> BST_Book_keyPrice("BST_Book_keyPrice");

    // 루트 주소 확인용 포인터 선언하기
    BSTN_KV<double, Book*>** ppBST_Book_keyPrice_root;

    // price 기준 BST 생성 시작 메시지 출력하기
    cout << "Binary Search Tree of Books (key : price) without Rebalancing" << endl;

    // price 기준 BST 루트 주소 가져오기
    ppBST_Book_keyPrice_root = BST_Book_keyPrice.getRootAddr();

    // price 기준으로 Book 정보 삽입하기
    for (int i = 0; i < NUM_STAR; i++)
    {
        BST_Book_keyPrice.insertInOrder(books[i].getPrice(), &books[i]);
    }

    // price 기준 중위 순회 출력하기
    cout << "Elements in " << BST_Book_keyPrice.getName() << " (in order of price) :" << endl;
    BST_Book_keyPrice.fprint_inOrder(cout);
    cout << endl;

    // price 기준 BST 구조 출력하기
    BST_Book_keyPrice.fprint_with_Depth(cout);
    cout << endl;

    // pub_date를 key로 사용하는 Book BST 생성하기
    BST_KV<int, Book*> BST_Book_keyPubDate("BST_Book_keyPubDate");

    // 루트 주소 확인용 포인터 선언하기
    BSTN_KV<int, Book*>** ppBST_Book_keyPubDate_root;

    // pub_date 기준 BST 생성 시작 메시지 출력하기
    cout << "Binary Search Tree of Books (key : pub_date) without Rebalancing" << endl;

    // pub_date 기준 BST 루트 주소 가져오기
    ppBST_Book_keyPubDate_root = BST_Book_keyPubDate.getRootAddr();

    // pub_date 기준으로 Book 정보 삽입하기
    for (int i = 0; i < NUM_STAR; i++)
    {
        BST_Book_keyPubDate.insertInOrder(books[i].getPubDate(), &books[i]);
    }

    // pub_date 기준 중위 순회 출력하기
    cout << "Elements in " << BST_Book_keyPubDate.getName();
    cout << " (in order of pub_date) :" << endl;
    BST_Book_keyPubDate.fprint_inOrder(cout);
    cout << endl;

    // pub_date 기준 BST 구조 출력하기
    BST_Book_keyPubDate.fprint_with_Depth(cout);
    cout << endl;

    // 동적 생성한 Book 배열 삭제하기
    delete[] books;

    return 0;
}