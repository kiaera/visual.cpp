/*
Graph.h
project : Graph 클래스와 Vertex, Edge 구조체를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 9, 2026
*/

// GRAPH_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

const int INF = 1e9; // 무한대 값 설정 (+oo 표현용)

/*
그래프 클래스 생성하기
*/
class Graph {
private:
    int numVertices;
    int numEdges; // 총 간선 수를 저장할 변수
    std::string graphName;
    std::vector<std::string> vertexNames;
    std::map<std::string, int> nameToIndex;
    std::vector<std::vector<int>> adjMatrix;

    int getOrCreateVertexIndex(const std::string& name);

public:
    Graph();

    static Graph fgetGraph(const std::string& filename);

    void printAdjacencyList(std::ostream& out) const;
    void printAdjacencyMatrix(std::ostream& out) const;

    int getNumVertices() const { return numVertices; }
    int getVertexIndex(const std::string& name) const;
    std::string getVertexName(int index) const;
    int getEdgeWeight(int u, int v) const;
};

#endif 