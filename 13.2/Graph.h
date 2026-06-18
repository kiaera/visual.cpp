/*
Graph.h
project : Graph 클래스와 Vertex, Edge 구조체를 선언한 헤더파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// GRAPH_H가 선언되어 있지 않은 경우에만 포함하기
#ifndef GRAPH_H
// GRAPH_H 매크로 정의하기
#define GRAPH_H

// 표준 입출력 사용하기 위한 헤더파일
#include <iostream>
// 출력 정렬을 위한 헤더파일
#include <iomanip>
// 파일 입력을 사용하기 위한 헤더파일
#include <fstream>
// 문자열 자료형을 사용하기 위한 헤더파일
#include <string>
// vector 컨테이너를 사용하기 위한 헤더파일
#include <vector>
// 정점 이름과 번호를 연결하기 위한 헤더파일
#include <unordered_map>
// 무한대 값을 사용하기 위한 헤더파일
#include <limits>
// 예외 처리를 사용하기 위한 헤더파일
#include <stdexcept>
// 최솟값 비교를 사용하기 위한 헤더파일
#include <algorithm>

// 연결되지 않은 정점 사이의 거리를 나타내는 무한대 값 정의하기
constexpr double INF = std::numeric_limits<double>::infinity();

// 정점 정보를 저장하는 구조체 선언하기
struct Vertex {
    int id{};
    std::string name;
};

// 간선 정보를 저장하는 구조체 선언하기
struct Edge {
    int from{};
    int to{};
    double weight{};
};

/**
정점 이름을 출력하는 연산자 함수
*/
inline std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    return os << v.name;
}

/**
간선 정보를 출력하는 연산자 함수
*/
inline std::ostream& operator<<(std::ostream& os, const Edge& e)
{
    return os << "Edge(" << e.from << " -> " << e.to << " : " << e.weight << ")";
}

// Graph 클래스 선언하기
class Graph {
private:
    std::string _graphName;
    bool _directed{};
    std::vector<Vertex> _vertices;
    std::vector<std::vector<Edge>> _adj;
    std::unordered_map<std::string, int> _idByName;

public:
    explicit Graph(std::string name = "", bool directed = false);
    const std::string& name() const noexcept;
    bool isDirected() const noexcept;
    int vertexCount() const noexcept;
    int edgeCount() const noexcept;
    int addVertex(const std::string& vertexName);
    void addEdge(const std::string& fromName, const std::string& toName, double weight = 1.0);
    void addEdge(int from, int to, double weight = 1.0);
    bool hasVertex(const std::string& vertexName) const;
    int idOf(const std::string& vertexName) const;
    const Vertex& vertex(int id) const;
    const std::vector<Vertex>& vertices() const noexcept;
    const std::vector<Edge>& adjacentEdges(int id) const;
    std::vector<std::vector<double>> adjacencyMatrix() const;
    void printDistanceMatrix(std::ostream& os) const;
    static Graph fgetGraph(const std::string& fileName, bool directed = false);
};

#endif