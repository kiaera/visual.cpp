/*
main.cpp
project : 그래프 깊이 우선 탐색과 미로 탐색 프로그램을 실행하는 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>
// 예외 처리를 사용하기 위한 헤더파일
#include <exception>
// Graph 클래스 사용하기 위한 헤더파일
#include "Graph.h"
// GraphAlgorithms 클래스 사용하기 위한 헤더파일
#include "GraphAlgorithms.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
using namespace std;

// 그래프 파일 선택 메뉴 출력하기
void printGraphFileMenu()
{
    cout << "Input graph file\n";
    cout << "  1: Mesh_2x3.txt\n";
    cout << "  2: Mesh_4x4.txt\n";
    cout << "  3: Maze_5x5.txt\n";
    cout << "  4: USA_7_cities.txt\n";
    cout << "  5: Korea_11.txt\n";
    cout << "  0: quit\n";
    cout << "Choice: ";
}

// 선택 번호에 맞는 그래프 파일 이름 반환하기
string graphFileName(int choice)
{
    switch (choice) {
    case 1:
        return "Mesh_2x3.txt";
    case 2:
        return "Mesh_4x4.txt";
    case 3:
        return "Maze_5x5.txt";
    case 4:
        return "USA_7_cities.txt";
    case 5:
        return "Korea_11.txt";
    default:
        return "";
    }
}

// 테스트 모드 선택 메뉴 출력하기
void printTestModeMenu()
{
    cout << "\nInput test mode\n";
    cout << "  1: DFS path search\n";
    cout << "  0: select another graph / quit this graph\n";
    cout << "Choice: ";
}

// DFS 경로 탐색 실행하기
void runDfsPathSearch(const Graph& graph)
{
    string startName;
    string targetName;

    cout << "Input start and target vertex names: ";
    cin >> startName >> targetName;

    PathResult result = GraphAlgorithms::dfsPath(graph, startName, targetName);

    cout << "DFS path: ";
    printPath(cout, graph, result.path);
    cout << " / cost = " << result.distance << '\n';
}

// 선택한 그래프에서 알고리즘 실행하기
void runTestMode(const Graph& graph)
{
    while (true) {
        int mode = 0;

        printTestModeMenu();
        cin >> mode;

        if (mode == 0) {
            break;
        }

        if (mode == 1) {
            runDfsPathSearch(graph);
        }
        else {
            cout << "Wrong test mode.\n";
        }
    }
}

/*
그래프 깊이 우선 탐색과 
미로 탐색 프로그램을 실행하는 메인 함수
*/
int main()
{
    while (true) {
        int choice = 0;

        printGraphFileMenu();
        cin >> choice;

        if (choice == 0) {
            break;
        }

        string fileName = graphFileName(choice);

        if (fileName.empty()) {
            cout << "Wrong graph file menu.\n";
            continue;
        }

        try {
            Graph graph = Graph::fgetGraph(fileName);

            graph.printAdjacencyList(cout);
            graph.printAdjacencyMatrix(cout);

            runTestMode(graph);
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    }

    return 0;
}