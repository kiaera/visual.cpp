/*
Graph.cpp
project : Graph 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 9, 2026
*/

#include "Graph.h"
#include <fstream>
#include <iomanip>

Graph::Graph() : numVertices(0), numEdges(0), graphName("") {}

int Graph::getOrCreateVertexIndex(const std::string& name) {
    if (nameToIndex.find(name) == nameToIndex.end()) {
        nameToIndex[name] = numVertices;
        vertexNames.push_back(name);
        numVertices++;
    }
    return nameToIndex[name];
}

Graph Graph::fgetGraph(const std::string& filename) {
    Graph g;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return g;
    }

    int expectedVertices;
    file >> g.graphName >> expectedVertices;

    std::vector<std::pair<std::pair<std::string, std::string>, int>> edges;
    std::string uName, vName;
    int weight;

    while (file >> uName >> vName >> weight) {
        g.getOrCreateVertexIndex(uName);
        g.getOrCreateVertexIndex(vName);
        edges.push_back({ {uName, vName}, weight });
    }
    file.close();

    // 읽어온 총 간선 수 저장
    g.numEdges = edges.size();

    // 행렬 초기화
    g.adjMatrix.assign(g.numVertices, std::vector<int>(g.numVertices, INF));
    for (int i = 0; i < g.numVertices; ++i) {
        g.adjMatrix[i][i] = 0;
    }

    // 무방향 그래프 간선 주입
    for (const auto& edge : edges) {
        int u = g.nameToIndex[edge.first.first];
        int v = g.nameToIndex[edge.first.second];
        int w = edge.second;
        g.adjMatrix[u][v] = w;
        g.adjMatrix[v][u] = w;
    }

    return g;
}

/*
정보 출력하기
*/
void Graph::printAdjacencyList(std::ostream& out) const {
    out << "Graph " << graphName << " (" << numVertices << " vertices, " << numEdges << " edges)\n";
    for (int i = 0; i < numVertices; ++i) {
        out << std::setw(3) << vertexNames[i] << " :";
        for (int j = 0; j < numVertices; ++j) {
            if (i != j && adjMatrix[i][j] != INF) {
                out << " (" << vertexNames[j] << ", " << adjMatrix[i][j] << ")";
            }
        }
        out << "\n";
    }
    out << "\n";
}

/*
그래프 출력하기
*/
void Graph::printAdjacencyMatrix(std::ostream& out) const {
    out << "Adjacency Matrix of " << graphName << "\n";

    out << "    |";
    for (const auto& name : vertexNames) {
        out << std::setw(6) << name;
    }
    out << "\n----+" << std::string(numVertices * 6, '-') << "\n";

    for (int i = 0; i < numVertices; ++i) {
        out << std::setw(3) << vertexNames[i] << " |";
        for (int j = 0; j < numVertices; ++j) {
            if (adjMatrix[i][j] == INF) {
                out << std::setw(6) << "+oo";
            }
            else {
                out << std::setw(6) << adjMatrix[i][j];
            }
        }
        out << "\n";
    }
}

int Graph::getVertexIndex(const std::string& name) const {
    auto it = nameToIndex.find(name);
    if (it != nameToIndex.end()) return it->second;
    return -1;
}

std::string Graph::getVertexName(int index) const {
    if (index >= 0 && index < numVertices) return vertexNames[index];
    return "";
}

int Graph::getEdgeWeight(int u, int v) const {
    return adjMatrix[u][v];
}