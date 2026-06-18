/*
main.cpp
project : Dijkstra 알고리즘을 사용한 최단거리 경로 탐색 프로그램을 실행하는 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>
// 출력 정렬을 위한 헤더파일
#include <iomanip>
// 예외 처리를 사용하기 위한 헤더파일
#include <exception>
// Graph 클래스 사용하기 위한 헤더파일
#include "Graph.h"
// GraphAlgorithms 클래스 사용하기 위한 헤더파일
#include "GraphAlgorithms.h"

// std에 포함된 모든 식별자들을 사용할 수 있게 선언하기
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
경로 탐색 결과를 출력하는 함수
*/
void printPathResult(const Graph& graph, const string& title, const PathResult& result)
{
    cout << title << ": ";

    if (!result.found) {
        cout << "No path\n";
        return;
    }

    printPath(cout, graph, result.path);
    cout << " / cost = " << result.distance << '\n';
}

/**
최단 거리 행렬을 출력하는 함수
*/
void printDistanceMatrix(const Graph& graph, const vector<vector<double>>& matrix)
{
    cout << "\nFloyd-Warshall shortest distance matrix of " << graph.name() << "\n";
    cout << "     |";

    for (const Vertex& v : graph.vertices()) {
        cout << setw(7) << v.name;
    }

    cout << "\n------+" << string(graph.vertexCount() * 7, '-') << '\n';

    for (int i = 0; i < graph.vertexCount(); ++i) {
        cout << setw(5) << graph.vertex(i).name << " |";

        for (int j = 0; j < graph.vertexCount(); ++j) {
            if (matrix[i][j] == INF) {
                cout << setw(7) << "+oo";
            }
            else {
                cout << setw(7) << matrix[i][j];
            }
        }

        cout << '\n';
    }
}

/**
최소 신장 트리 결과를 출력하는 함수
*/
void printMSTResult(const Graph& graph, const string& title, const MSTResult& result)
{
    cout << title << "\n";

    if (!result.connected) {
        cout << "MST cannot include all vertices because graph is not connected.\n";
    }

    for (const Edge& e : result.edges) {
        cout << "(" << graph.vertex(e.from).name << ", "
            << graph.vertex(e.to).name << ", "
            << e.weight << ")\n";
    }

    cout << "total weight = " << result.totalWeight << '\n';
}

/**
시작 정점과 목표 정점 이름을 입력받는 함수
*/
void inputStartTarget(string& startName, string& targetName)
{
    cout << "Input start and target vertex names: ";
    cin >> startName >> targetName;
}

/**
DFS 경로 탐색을 실행하는 함수
*/
void runDfsPathSearch(const Graph& graph)
{
    string startName;
    string targetName;

    inputStartTarget(startName, targetName);

    PathResult result = GraphAlgorithms::dfsPath(graph, startName, targetName);

    printPathResult(graph, "DFS path", result);
}

/**
BFS 최단 경로 탐색을 실행하는 함수
*/
void runBfsShortestPath(const Graph& graph)
{
    string startName;
    string targetName;

    inputStartTarget(startName, targetName);

    PathResult result = GraphAlgorithms::bfsShortestPath(graph, startName, targetName);

    printPathResult(graph, "BFS shortest path", result);
}

/**
Dijkstra 최단 경로 탐색을 실행하는 함수
*/
void runDijkstraShortestPath(const Graph& graph)
{
    string startName;
    string targetName;

    inputStartTarget(startName, targetName);

    PathResult result = GraphAlgorithms::dijkstraShortestPath(graph, startName, targetName);

    printPathResult(graph, "Dijkstra shortest path", result);
}

/**
Floyd-Warshall 최단 거리 행렬을 출력하는 함수
*/
void runFloydWarshall(const Graph& graph)
{
    vector<vector<double>> matrix = GraphAlgorithms::floydWarshall(graph);

    printDistanceMatrix(graph, matrix);
}

/**
Prim 최소 신장 트리를 실행하는 함수
*/
void runPrimMST(const Graph& graph)
{
    string startName;

    cout << "Input start vertex name: ";
    cin >> startName;

    MSTResult result = GraphAlgorithms::primMST(graph, startName);

    printMSTResult(graph, "Prim MST", result);
}

/**
Kruskal 최소 신장 트리를 실행하는 함수
*/
void runKruskalMST(const Graph& graph)
{
    MSTResult result = GraphAlgorithms::kruskalMST(graph);

    printMSTResult(graph, "Kruskal MST", result);
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
            if (mode == 1) {
                runDfsPathSearch(graph);
            }
            else if (mode == 2) {
                runBfsShortestPath(graph);
            }
            else if (mode == 3) {
                runDijkstraShortestPath(graph);
            }
            else if (mode == 4) {
                runFloydWarshall(graph);
            }
            else if (mode == 5) {
                runPrimMST(graph);
            }
            else if (mode == 6) {
                runKruskalMST(graph);
            }
            else {
                cout << "Wrong test mode.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
}

/**
Dijkstra 알고리즘을 사용한 
최단거리 경로 탐색 프로그램을 실행하는 메인 함수
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