/*
main_ICD.cpp
project : STL map과 pair를 이용하여 도시간 거리표를 출력하는 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : May 16, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>

// 파일 입출력을 사용하기 위한 헤더파일
#include <fstream>

// 출력 형식 제어를 사용하기 위한 헤더파일
#include <iomanip>

// map 컨테이너를 사용하기 위한 헤더파일
#include <map>

// set 컨테이너를 사용하기 위한 헤더파일
#include <set>

// pair 자료형을 사용하기 위한 헤더파일
#include <utility>

// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 거리 입력 함수
void Add_Inter_City_Dist(
    map<pair<string, string>, int>& distanceMap,
    const string& city1,
    const string& city2,
    int distance)
{
    // 두 도시 이름을 pair로 묶어 key로 사용하고 거리 저장하기
    distanceMap[make_pair(city1, city2)] = distance;
}

// 두 도시 간 거리 조회 함수
bool Get_Distance(
    const map<pair<string, string>, int>& distanceMap,
    const string& city1,
    const string& city2,
    int& distance)
{
    // 두 도시 이름으로 key 생성하기
    pair<string, string> cityPair = make_pair(city1, city2);

    // map에서 두 도시 사이 거리 찾기
    auto it = distanceMap.find(cityPair);

    // 거리가 존재하지 않으면 false 반환하기
    if (it == distanceMap.end())
        return false;

    // 찾은 거리 값을 참조 변수에 저장하기
    distance = it->second;

    return true;
}

// 파일에서 도시간 거리 정보를 입력받는 함수
int Fget_City_Pair_Dist_Tbl(
    istream& fin,
    set<string>& cities,
    map<pair<string, string>, int>& distMap)
{
    // 데이터 제목 저장하기
    string title;

    // 도시 이름 저장 변수 선언하기
    string city1, city2;

    // 거리 저장 변수 선언하기
    int distance;

    // 입력된 거리 정보 개수 저장하기
    int count = 0;

    // 첫 번째 줄의 제목 입력받기
    fin >> title;

    // 파일 끝까지 도시 이름과 거리 입력받기
    while (fin >> city1 >> city2 >> distance)
    {
        // 도시 이름을 set에 저장하기
        cities.insert(city1);
        cities.insert(city2);

        // city1에서 city2로 가는 거리 저장하기
        Add_Inter_City_Dist(distMap, city1, city2, distance);

        // city2에서 city1로 가는 거리 저장하기
        Add_Inter_City_Dist(distMap, city2, city1, distance);

        // 입력된 거리 정보 개수 증가시키기
        count++;
    }

    return count;
}

// 전체 거리표 출력 함수
void Print_Distance_Table(
    const map<pair<string, string>, int>& distanceMap,
    const set<string>& cities)
{
    // 거리 저장 변수 선언하기
    int distance;

    // 표 제목 출력하기
    cout << setw(5) << "City" << " |";

    // 도시 이름 목록 출력하기
    for (const string& city : cities)
        cout << setw(6) << city;

    cout << endl;

    // 구분선 출력하기
    cout << "------+";

    for (int i = 0; i < cities.size(); i++)
        cout << "------";

    cout << endl;

    // 각 도시별 거리 정보 출력하기
    for (const string& city1 : cities)
    {
        // 행 이름 출력하기
        cout << setw(5) << city1 << " |";

        // 열 도시와의 거리 출력하기
        for (const string& city2 : cities)
        {
            // 자기 자신이면 0 출력하기
            if (city1 == city2)
            {
                cout << setw(6) << 0;
            }

            // 두 도시 사이 거리 정보가 있으면 거리 출력하기
            else if (Get_Distance(distanceMap, city1, city2, distance))
            {
                cout << setw(6) << distance;
            }

            // 거리 정보가 없으면 - 출력하기
            else
            {
                cout << setw(6) << "-";
            }
        }

        cout << endl;
    }
}

/*
도시간 거리 파일을 열어 정보를 입력받고
전체 도시간 거리표를 출력하는 함수
*/
int main()
{
    // 파일 입력 객체 선언하기
    ifstream fin;

    // 도시간 거리 정보를 저장할 map 선언하기
    map<pair<string, string>, int> interCityDistMap;

    // 도시 이름을 중복 없이 저장할 set 선언하기
    set<string> cities;

    // 도시간 거리 정보 파일 열기
    fin.open("KR_InterCityDist_11.txt");

    // 파일 열기 실패 확인하기
    if (fin.fail())
    {
        cout << "Error in opening KR_InterCityDist_11.txt !!\n";
        return -1;
    }

    // 파일에서 도시간 거리 정보 입력받기
    Fget_City_Pair_Dist_Tbl(fin, cities, interCityDistMap);

    // 파일 닫기
    fin.close();

    // 전체 도시간 거리표 출력하기
    Print_Distance_Table(interCityDistMap, cities);

    return 0;
}