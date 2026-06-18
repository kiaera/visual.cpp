/*
GraphAlgorithms.h
project : GraphAlgorithms 클래스와 PathResult 구조체를 선언한 헤더파일
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
// 재귀 람다 함수를 저장하기 위한 헤더파일
#include <functional>

// 경로 탐색 결과를 저장하는 구조체 선언하기
struct PathResult {
    bool found{};
    double distance{ INF };
    std::vector<int> path;
};

// 그래프 알고리즘 클래스 선언하기
class GraphAlgorithms {
public:
    static PathResult dfsPath(const Graph& graph, const std::string& startName, const std::string& targetName);

private:
    static std::vector<int> buildPath(int start, int target, const std::vector<int>& previous);
};

#endif