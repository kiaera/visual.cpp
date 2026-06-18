/*
main.cpp
project : Dijkstra 알고리즘을 사용한 최단거리 경로 탐색 프로그램을 실행하는 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 9, 2026
*/

#include "Graph.h"
#include "GraphAlgorithms.h"
#include <iostream>
#include <string>

using namespace std;

/*
Dijkstra 알고리즘을 사용한 
최단거리 경로 탐색 프로그램을 실행하는 메인 함수
*/
int main()
{
    Graph graph;
    string graph_file = "USA_7.txt";
    graph = Graph::fgetGraph(graph_file);
    graph.printAdjacencyList(cout);
    graph.printAdjacencyMatrix(cout);

    string start = "LA";
    string target = "BOS";

    PathResult shortest_path = GraphAlgorithms::dijkstraShortestPath(graph, start, target);

    cout << "\nShortest path (" << start << " -> " << target << ") : ";
    printPath(cout, graph, shortest_path.path);

    cout << "\nDistance (" << start << " -> " << target << ") = ";
    cout << shortest_path.distance << '\n';

    return 0;
}