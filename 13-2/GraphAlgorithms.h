/*
GraphAlgorithms.h
project : GraphAlgorithms 클래스와 PathResult, MSTResult 구조체를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// GRAPH_ALGORITHMS_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GRAPH_ALGORITHMS_H
// GRAPH_ALGORITHMS_H 매크로 정의하기
#define GRAPH_ALGORITHMS_H

// Graph 클래스를 사용하기 위한 헤더파일
#include "Graph.h"
// queue와 priority_queue를 사용하기 위한 헤더파일
#include <queue>
// 람다 함수와 greater 비교 함수를 사용하기 위한 헤더파일
#include <functional>
// iota 함수를 사용하기 위한 헤더파일
#include <numeric>
// sort와 reverse 함수를 사용하기 위한 헤더파일
#include <algorithm>
// pair 자료형을 사용하기 위한 헤더파일
#include <utility>

// 경로 탐색 결과를 저장하는 구조체 선언하기
struct PathResult {
    bool found{};
    double distance{ INF };
    std::vector<int> path;
};

// 최소 신장 트리 결과를 저장하는 구조체 선언하기
struct MSTResult {
    bool connected{};
    double totalWeight{};
    std::vector<Edge> edges;
};

// 그래프 알고리즘 클래스 선언하기
class GraphAlgorithms {
public:
    static PathResult dfsPath(const Graph& graph, const std::string& startName, const std::string& targetName);
    static PathResult bfsShortestPath(const Graph& graph, const std::string& startName, const std::string& targetName);
    static PathResult dijkstraShortestPath(const Graph& graph, const std::string& startName, const std::string& targetName);
    static std::vector<std::vector<double>> floydWarshall(const Graph& graph);
    static MSTResult primMST(const Graph& graph, const std::string& startName);
    static MSTResult kruskalMST(const Graph& graph);

private:
    static std::vector<int> buildPath(int start, int target, const std::vector<int>& previous);
};

#endif