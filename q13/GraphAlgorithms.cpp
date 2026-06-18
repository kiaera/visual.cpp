/*
GraphAlgorithms.cpp
project : Dijkstra 최단 경로 알고리즘을 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 9, 2026
*/

#include "GraphAlgorithms.h"
#include <algorithm>

std::vector<int> GraphAlgorithms::buildPath(int start, int target, const std::vector<int>& previous) {
    std::vector<int> path;
    if (previous[target] == -1 && start != target) {
        return path;
    }
    for (int v = target; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

PathResult GraphAlgorithms::dijkstraShortestPath(const Graph& graph, const std::string& startName, const std::string& targetName) {
    int n = graph.getNumVertices();
    int start = graph.getVertexIndex(startName);
    int target = graph.getVertexIndex(targetName);

    std::vector<int> distance(n, INF);
    std::vector<int> previous(n, -1);
    std::vector<bool> visited(n, false);

    distance[start] = 0;

    for (int i = 0; i < n; ++i) {
        int min_dist = INF;
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distance[j] < min_dist) {
                min_dist = distance[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = true;
        if (u == target) break;

        for (int v = 0; v < n; ++v) {
            int weight = graph.getEdgeWeight(u, v);
            if (!visited[v] && weight != INF) {
                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                }
            }
        }
    }

    PathResult result;
    result.distance = distance[target];
    result.path = buildPath(start, target, previous);
    return result;
}

void printPath(std::ostream& out, const Graph& graph, const std::vector<int>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        out << graph.getVertexName(path[i]);
        if (i < path.size() - 1) {
            out << " -> ";
        }
    }
}