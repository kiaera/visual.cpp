/*
GraphAlgorithms.cpp
project : GraphAlgorithms 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// GraphAlgorithms 클래스 선언을 포함하기 위한 헤더파일
#include "GraphAlgorithms.h"
// 예외 처리를 사용하기 위한 헤더파일
#include <stdexcept>

/**
previous 배열을 이용해 시작 정점부터 목표 정점까지의 경로를 생성하는 함수
*/
std::vector<int> GraphAlgorithms::buildPath(int start, int target, const std::vector<int>& previous)
{
    std::vector<int> path;

    if (target < 0 || target >= static_cast<int>(previous.size())) {
        return path;
    }

    if (previous[target] == -1 && start != target) {
        return path;
    }

    for (int cur = target; cur != -1; cur = previous[cur]) {
        path.push_back(cur);

        if (cur == start) {
            break;
        }
    }

    if (path.empty() || path.back() != start) {
        return {};
    }

    std::reverse(path.begin(), path.end());

    return path;
}

/**
깊이 우선 탐색으로 시작 정점부터 목표 정점까지의 경로를 찾는 함수
*/
PathResult GraphAlgorithms::dfsPath(const Graph& graph, const std::string& startName, const std::string& targetName)
{
    int start = graph.idOf(startName);
    int target = graph.idOf(targetName);
    int n = graph.vertexCount();

    std::vector<bool> visited(n, false);
    std::vector<int> previous(n, -1);

    std::function<bool(int)> dfs = [&](int u)
        {
            visited[u] = true;

            if (u == target) {
                return true;
            }

            for (const Edge& e : graph.adjacentEdges(u)) {
                int v = e.to;

                if (!visited[v]) {
                    previous[v] = u;

                    if (dfs(v)) {
                        return true;
                    }
                }
            }

            return false;
        };

    PathResult result;
    result.found = dfs(start);

    if (result.found) {
        result.path = buildPath(start, target, previous);
        result.distance = static_cast<double>(result.path.size() - 1);
    }

    return result;
}

/**
너비 우선 탐색으로 간선 개수가 가장 적은 경로를 찾는 함수
*/
PathResult GraphAlgorithms::bfsShortestPath(const Graph& graph, const std::string& startName, const std::string& targetName)
{
    int start = graph.idOf(startName);
    int target = graph.idOf(targetName);
    int n = graph.vertexCount();

    std::vector<bool> visited(n, false);
    std::vector<int> previous(n, -1);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == target) {
            break;
        }

        for (const Edge& e : graph.adjacentEdges(u)) {
            int v = e.to;

            if (!visited[v]) {
                visited[v] = true;
                previous[v] = u;
                q.push(v);
            }
        }
    }

    PathResult result;
    result.found = visited[target];

    if (result.found) {
        result.path = buildPath(start, target, previous);
        result.distance = static_cast<double>(result.path.size() - 1);
    }

    return result;
}

/**
다익스트라 알고리즘으로 가중치 그래프의 최단 경로를 찾는 함수
*/
PathResult GraphAlgorithms::dijkstraShortestPath(const Graph& graph, const std::string& startName, const std::string& targetName)
{
    int start = graph.idOf(startName);
    int target = graph.idOf(targetName);
    int n = graph.vertexCount();

    using Node = std::pair<double, int>;

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::vector<double> dist(n, INF);
    std::vector<int> previous(n, -1);

    dist[start] = 0.0;
    pq.push({ 0.0, start });

    while (!pq.empty()) {
        double curDist = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if (curDist > dist[u]) {
            continue;
        }

        if (u == target) {
            break;
        }

        for (const Edge& e : graph.adjacentEdges(u)) {
            if (e.weight < 0) {
                throw std::logic_error("Dijkstra cannot be used with negative edge weights.");
            }

            int v = e.to;
            double nextDist = dist[u] + e.weight;

            if (nextDist < dist[v]) {
                dist[v] = nextDist;
                previous[v] = u;
                pq.push({ nextDist, v });
            }
        }
    }

    PathResult result;
    result.found = dist[target] != INF;
    result.distance = dist[target];

    if (result.found) {
        result.path = buildPath(start, target, previous);
    }

    return result;
}

/**
플로이드 워셜 알고리즘으로 모든 정점 쌍 사이의 최단 거리를 구하는 함수
*/
std::vector<std::vector<double>> GraphAlgorithms::floydWarshall(const Graph& graph)
{
    std::vector<std::vector<double>> dist = graph.adjacencyMatrix();
    int n = graph.vertexCount();

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

/**
프림 알고리즘으로 최소 신장 트리를 구하는 함수
*/
MSTResult GraphAlgorithms::primMST(const Graph& graph, const std::string& startName)
{
    int start = graph.idOf(startName);
    int n = graph.vertexCount();

    std::vector<bool> selected(n, false);

    using Node = std::pair<double, Edge>;

    auto compare = [](const Node& a, const Node& b)
        {
            return a.first > b.first;
        };

    std::priority_queue<Node, std::vector<Node>, decltype(compare)> pq(compare);

    MSTResult result;

    selected[start] = true;

    for (const Edge& e : graph.adjacentEdges(start)) {
        pq.push({ e.weight, e });
    }

    while (!pq.empty() && static_cast<int>(result.edges.size()) < n - 1) {
        Edge e = pq.top().second;
        pq.pop();

        if (selected[e.to]) {
            continue;
        }

        selected[e.to] = true;
        result.edges.push_back(e);
        result.totalWeight += e.weight;

        for (const Edge& next : graph.adjacentEdges(e.to)) {
            if (!selected[next.to]) {
                pq.push({ next.weight, next });
            }
        }
    }

    result.connected = static_cast<int>(result.edges.size()) == n - 1;

    return result;
}

/**
크루스칼 알고리즘으로 최소 신장 트리를 구하는 함수
*/
MSTResult GraphAlgorithms::kruskalMST(const Graph& graph)
{
    int n = graph.vertexCount();

    std::vector<int> parent(n);
    std::vector<int> rank(n, 0);

    std::iota(parent.begin(), parent.end(), 0);

    std::function<int(int)> findRoot = [&](int x)
        {
            if (parent[x] != x) {
                parent[x] = findRoot(parent[x]);
            }

            return parent[x];
        };

    auto unionSet = [&](int a, int b)
        {
            int rootA = findRoot(a);
            int rootB = findRoot(b);

            if (rootA == rootB) {
                return false;
            }

            if (rank[rootA] < rank[rootB]) {
                parent[rootA] = rootB;
            }
            else if (rank[rootA] > rank[rootB]) {
                parent[rootB] = rootA;
            }
            else {
                parent[rootB] = rootA;
                ++rank[rootA];
            }

            return true;
        };

    std::vector<Edge> sortedEdges = graph.edges(true);

    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b)
        {
            return a.weight < b.weight;
        });

    MSTResult result;

    for (const Edge& e : sortedEdges) {
        if (unionSet(e.from, e.to)) {
            result.edges.push_back(e);
            result.totalWeight += e.weight;

            if (static_cast<int>(result.edges.size()) == n - 1) {
                break;
            }
        }
    }

    result.connected = static_cast<int>(result.edges.size()) == n - 1;

    return result;
}