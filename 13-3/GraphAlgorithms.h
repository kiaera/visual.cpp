/*
GraphAlgorithms.h
project : Floyd-Warshall 최단 거리 알고리즘을 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "Graph.h"

class GraphAlgorithms {
public:
    static std::vector<std::vector<double>> floydWarshall(const Graph& graph);
};

#endif