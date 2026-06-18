/*
GraphAlgorithms.h
project : Kruskal 최소 신장 트리 알고리즘을 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "Graph.h"

struct MSTResult {
    bool connected{};
    double totalWeight{};
    std::vector<Edge> edges;
};

class GraphAlgorithms {
public:
    static MSTResult kruskalMST(const Graph& graph);
};

#endif