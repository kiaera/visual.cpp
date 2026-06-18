/*
GraphAlgorithms.h
project : Prim-Jarnik 최소 신장 트리 알고리즘을 선언한 헤더파일
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
// 출력 정렬을 사용하기 위한 헤더파일
#include <iomanip>

// 최소 신장 트리 결과를 저장하는 구조체 선언하기
struct MSTResult {
    bool connected{};
    double totalWeight{};
    std::vector<Edge> edges;
};

// 그래프 알고리즘 클래스 선언하기
class GraphAlgorithms {
public:
    static MSTResult primJarnikMST(const Graph& graph, const std::string& startName);
    static MSTResult primJarnikMSTWithTrace(const Graph& graph, const std::string& startName, std::ostream& os);
};

#endif