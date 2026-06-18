/*
main.cpp
project : Floyd-Warshall 알고리즘을 사용한 모든 정점 쌍 최단 거리 출력 프로그램
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include "Graph.h"
#include "GraphAlgorithms.h"

using namespace std;

/**
그래프 파일 선택 메뉴를 출력하는 함수
*/
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

/**
선택 번호에 맞는 그래프 파일 이름을 반환하는 함수
*/
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
    cout << "  0: select another graph / quit this graph\n";
    cout << "Choice: ";
}

/**
거리 값을 표 형식으로 출력하는 함수
*/
void printDistanceValue(ostream& os, double value)
{
    if (value == INF) {
        os << setw(7) << "+oo";
    }
    else {
        os << setw(7) << static_cast<int>(value);
    }
}

/**
Floyd-Warshall 알고리즘으로 구한 모든 정점 쌍 최단 거리표를 출력하는 함수
*/
void printFloydWarshallMatrix(const Graph& graph, const vector<vector<double>>& matrix)
{
    cout << "\nAll-pairs shortest distance table by Floyd-Warshall\n";
    cout << "      |";

    for (const Vertex& v : graph.vertices()) {
        cout << setw(7) << v.name;
    }

    cout << "\n------+";
    cout << string(graph.vertexCount() * 7, '-') << '\n';

    for (int i = 0; i < graph.vertexCount(); ++i) {
        cout << setw(5) << graph.vertex(i).name << " |";

        for (int j = 0; j < graph.vertexCount(); ++j) {
            printDistanceValue(cout, matrix[i][j]);
        }

        cout << '\n';
    }
}

/**
Floyd-Warshall 테스트 모드를 실행하는 함수
*/
void runFloydWarshallMode(const Graph& graph)
{
    vector<vector<double>> shortestDist = GraphAlgorithms::floydWarshall(graph);

    printFloydWarshallMatrix(graph, shortestDist);
}

/**
선택한 그래프에서 테스트 모드를 실행하는 함수
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
                runFloydWarshallMode(graph);
            }
            else {
                cout << "This program currently supports Floyd-Warshall mode only.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
}

/**
Floyd-Warshall 알고리즘을 사용한
모든 정점 쌍 최단 거리 출력하는 메인 함수
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