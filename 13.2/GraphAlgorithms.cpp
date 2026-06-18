/*
GraphAlgorithms.cpp
project : Prim-Jarnik 최소 신장 트리 알고리즘을 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// GraphAlgorithms 클래스 선언을 포함하기 위한 헤더파일
#include "GraphAlgorithms.h"
// 예외 처리를 사용하기 위한 헤더파일
#include <stdexcept>

/**
거리 값을 출력하는 보조 함수
*/
void printDistanceValue(std::ostream& os, double value)
{
    if (value == INF) {
        os << std::setw(7) << "+oo";
    }
    else {
        os << std::setw(7) << static_cast<int>(value);
    }
}

/**
Prim-Jarnik 알고리즘의 거리 배열을 출력하는 보조 함수
*/
void printPrimDistanceRound(std::ostream& os, int round, const std::vector<double>& dist)
{
    os << "Dist after round [ " << round << "] :";

    for (double value : dist) {
        printDistanceValue(os, value);
    }

    os << '\n';
}

/**
간선 정보를 출력하는 보조 함수
*/
void printSelectedEdge(std::ostream& os, const Graph& graph, const Edge& e)
{
    os << "  => min_edge (Edge("
        << graph.vertex(e.from).name << " -> "
        << graph.vertex(e.to).name << " : "
        << static_cast<int>(e.weight) << ")) is selected\n";
}

/**
Prim-Jarnik 알고리즘을 실행하고 필요하면 round별 과정을 출력하는 내부 함수
*/
MSTResult primJarnikInternal(const Graph& graph, const std::string& startName, std::ostream* traceOut)
{
    if (graph.isDirected()) {
        throw std::logic_error("MST is normally defined for undirected graphs.");
    }

    int start = graph.idOf(startName);
    int n = graph.vertexCount();

    std::vector<bool> selected(n, false);
    std::vector<double> dist(n, INF);
    std::vector<int> parent(n, -1);

    MSTResult result;

    selected[start] = true;
    dist[start] = 0.0;

    for (const Edge& e : graph.adjacentEdges(start)) {
        dist[e.to] = e.weight;
        parent[e.to] = start;
    }

    if (traceOut != nullptr) {
        *traceOut << "\nTesting Prim-JarnikMST() with start vertex ("
            << startName << ")\n";
        *traceOut << "Start node : " << startName << '\n';
        printPrimDistanceRound(*traceOut, 0, dist);
    }

    int round = 0;

    while (static_cast<int>(result.edges.size()) < n - 1) {
        int minVertex = -1;
        double minWeight = INF;

        for (int i = 0; i < n; ++i) {
            if (!selected[i] && dist[i] < minWeight) {
                minWeight = dist[i];
                minVertex = i;
            }
        }

        if (minVertex == -1) {
            break;
        }

        Edge selectedEdge{ parent[minVertex], minVertex, dist[minVertex] };

        if (traceOut != nullptr) {
            printSelectedEdge(*traceOut, graph, selectedEdge);
        }

        result.edges.push_back(selectedEdge);
        result.totalWeight += selectedEdge.weight;
        selected[minVertex] = true;

        for (const Edge& e : graph.adjacentEdges(minVertex)) {
            if (!selected[e.to] && e.weight < dist[e.to]) {
                dist[e.to] = e.weight;
                parent[e.to] = minVertex;
            }
        }

        ++round;

        if (traceOut != nullptr) {
            printPrimDistanceRound(*traceOut, round, dist);
        }
    }

    result.connected = static_cast<int>(result.edges.size()) == n - 1;

    return result;
}

/**
Prim-Jarnik 알고리즘으로 최소 신장 트리를 구하는 함수
*/
MSTResult GraphAlgorithms::primJarnikMST(const Graph& graph, const std::string& startName)
{
    return primJarnikInternal(graph, startName, nullptr);
}

/**
Prim-Jarnik 알고리즘으로 최소 신장 트리를 구하고 round별 과정을 출력하는 함수
*/
MSTResult GraphAlgorithms::primJarnikMSTWithTrace(const Graph& graph, const std::string& startName, std::ostream& os)
{
    return primJarnikInternal(graph, startName, &os);
}