/*
main.cpp
project : Red Black Tree template 클래스를 int, char, string, Person 자료형에 적용하여 시험하는 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 28, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>
// less 비교 함수를 사용하기 위한 헤더파일
#include <functional>
// Red Black Tree template class를 사용하기 위한 헤더파일
#include "RBT.h"
// Person class와 PersonLess class를 사용하기 위한 헤더파일
#include "Person.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

/*
Red Black Tree template 클래스를 
int, char, string, Person 자료형에 적용하여 시험하는 메인 함수
*/
int main()
{
    // int형 Red Black Tree에 삽입할 데이터 배열 선언하기
    int entryData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // int형 데이터 개수 계산하기
    int num_data = sizeof(entryData) / sizeof(int);

    // 현재 삽입할 int 데이터 저장하기
    int data;

    // int형 Red Black Tree 객체 생성하기
    RBTree<int> intRBT;

    // int 데이터 삽입하면서 Red Black Tree 구조 출력하기
    for (int i = 0; i < num_data; i++)
    {
        data = entryData[i];

        cout << "inserting " << data << " into intRBT" << endl;
        intRBT.insert(data);
        intRBT.printRBT();
    }

    // int형 Red Black Tree 중위 순회 결과 출력하기
    cout << "intRBT inorder : ";
    intRBT.inorderPrint();

    // int형 Red Black Tree에서 3이 있는지 확인하기
    cout << "Contains 3? " << (intRBT.contains(3) ? "yes" : "no") << endl;

    // int형 Red Black Tree에서 3 삭제하기
    cout << "Erase 3" << endl;
    intRBT.erase(3);

    // int형 Red Black Tree에서 3 삭제 여부 확인하기
    cout << "Contains 3? " << (intRBT.contains(3) ? "yes" : "no") << endl;

    // int형 Red Black Tree 삭제 후 중위 순회 결과 출력하기
    cout << "intRBT inorder after erase : ";
    intRBT.inorderPrint();
    intRBT.printRBT();

    cout << "\n\n";

    // char형 Red Black Tree에 삽입할 데이터 배열 선언하기
    char entryChar[] = { 'A', 'B', 'C', 'D', 'E' };

    // 현재 삽입할 char 데이터 저장하기
    char ch;

    // char형 Red Black Tree 객체 생성하기
    RBTree<char> charRBT;

    // char형 데이터 개수 계산하기
    int num_char = sizeof(entryChar) / sizeof(char);

    // char 데이터 삽입하면서 Red Black Tree 구조 출력하기
    for (int i = 0; i < num_char; i++)
    {
        ch = entryChar[i];

        cout << "inserting " << ch << " into RBT_char" << endl;
        charRBT.insert(ch);
        charRBT.printRBT();
    }

    // char형 Red Black Tree 중위 순회 결과 출력하기
    cout << "charRBT inorder : ";
    charRBT.inorderPrint();

    // char형 Red Black Tree에서 B가 있는지 확인하기
    cout << "Contains B? " << (charRBT.contains('B') ? "yes" : "no") << endl;

    // char형 Red Black Tree에서 B 삭제하기
    cout << "Erase B" << endl;
    charRBT.erase('B');

    // char형 Red Black Tree에서 B 삭제 여부 확인하기
    cout << "Contains B? " << (charRBT.contains('B') ? "yes" : "no") << endl;

    // char형 Red Black Tree 삭제 후 중위 순회 결과 출력하기
    cout << "charRBT inorder after erase : ";
    charRBT.inorderPrint();
    charRBT.printRBT();

    cout << "\n\n";

    // string형 Red Black Tree에 삽입할 데이터 배열 선언하기
    string entryStrings[] = { "orange", "apple", "banana", "grape" };

    // 현재 삽입할 string 데이터 저장하기
    string str;

    // string형 Red Black Tree 객체 생성하기
    RBTree<string> strRBT;

    // string형 데이터 개수 계산하기
    int num_str = sizeof(entryStrings) / sizeof(string);

    // string 데이터 삽입하면서 Red Black Tree 구조 출력하기
    for (int i = 0; i < num_str; i++)
    {
        str = entryStrings[i];

        cout << "inserting " << str << " into RBT_string" << endl;
        strRBT.insert(str);
        strRBT.printRBT();
    }

    // string형 Red Black Tree 중위 순회 결과 출력하기
    cout << "strRBT inorder : ";
    strRBT.inorderPrint();

    // string형 Red Black Tree에서 banana 삭제하기
    cout << "\nErase \"banana\"" << endl;
    strRBT.erase("banana");

    // string형 Red Black Tree 삭제 후 중위 순회 결과 출력하기
    cout << "strRBT tree inorder after erase banana : ";
    strRBT.inorderPrint();
    strRBT.printRBT();

    cout << "\n\n";

    // Person형 Red Black Tree에 삽입할 데이터 배열 선언하기
    Person entryPersons[] = {
        {2, "Alice"},
        {1, "Bob"},
        {3, "Charlie"},
        {4, "Doroshi"},
        {5, "Eugene"}
    };

    // 현재 삽입할 Person 데이터 저장하기
    Person p;

    // Person형 Red Black Tree 객체 생성하기
    RBTree<Person, PersonLess> personRBT;

    // Person형 데이터 개수 계산하기
    int num_persons = sizeof(entryPersons) / sizeof(Person);

    // Person 데이터 삽입하면서 Red Black Tree 구조 출력하기
    for (int i = 0; i < num_persons; i++)
    {
        p = entryPersons[i];

        cout << "inserting " << p << " into personRBT" << endl;
        personRBT.insert(p);
        personRBT.printRBT();
    }

    // Person형 Red Black Tree 중위 순회 결과 출력하기
    cout << "personRBT inorder(by age) :" << endl;
    personRBT.inorderPrint();

    // Person형 Red Black Tree에서 age가 2인 데이터 삭제하기
    cout << "\nErase age=2 (Alice)" << endl;
    personRBT.erase({ 2, "Dummy" });

    // Person형 Red Black Tree 삭제 후 중위 순회 결과 출력하기
    cout << "personRBT inorder after erase{2, \"Dummy\"}: " << endl;
    personRBT.inorderPrint();
    personRBT.printRBT();

    cout << endl;

    return 0;
}