/*
main.cpp
project : Prim-Jarnik 알고리즘을 사용한 최소 신장 트리 탐색 프로그램을 실행하는 CPP 파일
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

/**
테스트 모드 선택 메뉴를 출력하는 함수
*/
void printTestModeMenu()
{
    cout << "\nInput test mode "
        << "(1: Depth_First_Search(DFS), "
        << "2: Breadth_First_Search(BFS), "
        << "3: Dijkstra_Shortest_Path_Search(),\n"
        << "4: test_MST_PrimJarnik, "
        << "5: test_MST_Kruskal, "
        << "0: quit) : ";
}

/**
Prim-Jarnik MST 결과를 출력하는 함수
*/
void printMSTResult(const Graph& graph, const MSTResult& result)
{
    cout << "\nEnd of finding Minimum Spanning Tree by Prim-Jarnik's Algorithm; "
        << "selectedEdgeLst.size = " << result.edges.size() << '\n';

    if (!result.connected) {
        cout << "The graph is not connected.\n";
    }

    cout << "Selected edges:\n";

    for (std::size_t i = 0; i < result.edges.size(); ++i) {
        const Edge& e = result.edges[i];

        cout << "Edge("
            << graph.vertex(e.from).name << " -> "
            << graph.vertex(e.to).name << " : "
            << static_cast<int>(e.weight) << ")";

        if (i + 1 < result.edges.size()) {
            cout << ", ";
        }
    }

    cout << "\nTotal cost = " << static_cast<int>(result.totalWeight) << '\n';
}

/**
Prim-Jarnik MST 테스트 모드를 실행하는 함수
*/
void runPrimJarnikMode(const Graph& graph)
{
    string startName;

    cout << "Input start vertex name of minimum spanning tree : ";
    cin >> startName;

    MSTResult result = GraphAlgorithms::primJarnikMSTWithTrace(graph, startName, cout);

    printMSTResult(graph, result);
}

/**
선택한 테스트 모드를 실행하는 함수
*/
void runTestMode(const Graph& graph)
{
    while (true) {
        int mode = 0;

        printTestModeMenu();
        cin >> mode;

        if (mode == 0) {
            break;
        }

        try {
            if (mode == 4) {
                runPrimJarnikMode(graph);
            }
            else {
                cout << "This program currently supports Prim-Jarnik mode only.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
}

/**
Prim-Jarnik 알고리즘을 사용한 
최소 신장 트리 탐색 프로그램을 실행하는 메인 함수
*/
int main()
{
    try {
        Graph graph = Graph::fgetGraph("Simplified_USA.txt");

        graph.printDistanceMatrix(cout);

        runTestMode(graph);
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }

    return 0;
}