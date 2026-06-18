/*
GraphAlgorithms.cpp
project : Kruskal 최소 신장 트리 알고리즘을 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

#include "GraphAlgorithms.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

/**
Disjoint Set 자료구조를 구현한 클래스
*/
class DisjointSet {
private:
    std::vector<int> parent_;
    std::vector<int> rank_;

public:
    /**
    DisjointSet 생성자
    */
    explicit DisjointSet(int n)
        : parent_(n), rank_(n, 0)
    {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    /**
    정점 x가 속한 집합의 대표 노드를 찾는 함수
    */
    int find(int x)
    {
        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]);
        }

        return parent_[x];
    }

    /**
    두 정점이 속한 집합을 하나로 합치는 함수
    */
    bool unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) {
            return false;
        }

        if (rank_[rootA] < rank_[rootB]) {
            std::swap(rootA, rootB);
        }

        parent_[rootB] = rootA;

        if (rank_[rootA] == rank_[rootB]) {
            ++rank_[rootA];
        }

        return true;
    }
};

/**
Kruskal 알고리즘으로 최소 신장 트리를 구하는 함수
*/
MSTResult GraphAlgorithms::kruskalMST(const Graph& graph)
{
    if (graph.isDirected()) {
        throw std::logic_error("MST is normally defined for undirected graphs.");
    }

    std::vector<Edge> edges = graph.edges(true);

    std::sort(edges.begin(), edges.end(),
        [](const Edge& a, const Edge& b)
        {
            return a.weight < b.weight;
        }
    );

    DisjointSet ds(graph.vertexCount());

    MSTResult result;

    for (const Edge& e : edges) {
        if (ds.unite(e.from, e.to)) {
            result.edges.push_back(e);
            result.totalWeight += e.weight;

            if (static_cast<int>(result.edges.size()) == graph.vertexCount() - 1) {
                break;
            }
        }
    }

    result.connected = static_cast<int>(result.edges.size()) == graph.vertexCount() - 1;

    return result;
}