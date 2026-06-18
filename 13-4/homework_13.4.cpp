/*
main.cpp
project : Kruskal 알고리즘을 사용한 최소 신장 트리 탐색 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

#include <iostream>
#include <string>
#include <exception>
#include "Graph.h"
#include "GraphAlgorithms.h"

using namespace std;

/**
테스트 모드 선택 메뉴를 출력하는 함수
*/
void printTestModeMenu()
{
    cout << "\nInput test mode\n";
    cout << "  1: DFS path search\n";
    cout << "  2: BFS shortest path for unweighted graph\n";
    cout << "  3: Dijkstra shortest path for weighted graph\n";
    cout << "  4: Floyd-Warshall all-pairs shortest distance\n";
    cout << "  5: Prim MST\n";
    cout << "  6: Kruskal MST\n";
    cout << "  0: quit\n";
    cout << "Choice: ";
}

/**
Kruskal MST 결과를 출력하는 함수
*/
void printKruskalMSTResult(const Graph& graph, const MSTResult& result)
{
    cout << "Selected edges:\n";

    for (const Edge& e : result.edges) {
        cout << "  "
            << graph.vertex(e.from).name
            << " -- "
            << graph.vertex(e.to).name
            << "  weight="
            << static_cast<int>(e.weight)
            << '\n';
    }

    if (!result.connected) {
        cout << "The graph is not connected.\n";
    }

    cout << "Total weight = " << static_cast<int>(result.totalWeight) << '\n';
}

/**
Kruskal MST 테스트 모드를 실행하는 함수
*/
void runKruskalMSTMode(const Graph& graph)
{
    MSTResult result = GraphAlgorithms::kruskalMST(graph);

    printKruskalMSTResult(graph, result);
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
            if (mode == 6) {
                runKruskalMSTMode(graph);
            }
            else {
                cout << "This program currently supports Kruskal mode only.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
}

/**
 Kruskal 알고리즘을 사용한
 최소 신장 트리 탐색 메인 함수
 */
int main()
{
    try {
        Graph graph = Graph::fgetGraph("Korea_11.txt");

        graph.printAdjacencyList(cout);
        graph.printAdjacencyMatrix(cout);

        runTestMode(graph);
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }

    return 0;
}