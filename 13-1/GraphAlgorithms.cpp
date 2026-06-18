/*
GraphAlgorithms.cpp
project : GraphAlgorithms 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// GraphAlgorithms 클래스 선언을 포함하기 위한 헤더파일
#include "GraphAlgorithms.h"
// reverse 함수를 사용하기 위한 헤더파일
#include <algorithm>

// previous 배열을 이용해 시작 정점부터 목표 정점까지의 경로 만들기
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

// 깊이 우선 탐색으로 시작 정점부터 목표 정점까지의 경로 찾기
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