/*
GraphAlgorithms.cpp
project : Floyd-Warshall 최단 거리 알고리즘을 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

#include "GraphAlgorithms.h"

/**
Floyd-Warshall 알고리즘으로 모든 정점 쌍 사이의 최단 거리를 구하는 함수
*/
std::vector<std::vector<double>> GraphAlgorithms::floydWarshall(const Graph& graph)
{
    auto dist = graph.adjacencyMatrix();
    int n = graph.vertexCount();

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) {
                continue;
            }

            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == INF) {
                    continue;
                }

                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist;
}