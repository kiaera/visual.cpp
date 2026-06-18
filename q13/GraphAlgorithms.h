/*
GraphAlgorithms.h
project : Dijkstra 최단 경로 알고리즘을 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 9, 2026
*/

// GRAPH_ALGORITHMS_H이 선언되어 있지 않은 경우에만 포함
#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "Graph.h"
#include <vector>
#include <string>
#include <iostream>

struct PathResult {
    int distance;
    std::vector<int> path;
};

class GraphAlgorithms {
private:
    static std::vector<int> buildPath(int start, int target, const std::vector<int>& previous);

public:
    static PathResult dijkstraShortestPath(const Graph& graph, const std::string& startName, const std::string& targetName);
};

void printPath(std::ostream& out, const Graph& graph, const std::vector<int>& path);

#endif // GRAPH_ALGORITHMS_H