/*
Graph.cpp
project : Graph 클래스 헤더파일의 멤버함수를 구현한 CPP 파일
st_id : 22312039
Author : Cho_ilsu
Date of last update : Jun 8, 2026
*/

// Graph 클래스 선언을 포함하기 위한 헤더파일
#include "Graph.h"
// std::move를 사용하기 위한 헤더파일
#include <utility>

// Graph 클래스 생성자 정의하기
Graph::Graph(std::string name, bool directed)
    : _graphName(std::move(name)), _directed(directed)
{}

// 그래프 이름 반환하기
const std::string& Graph::name() const noexcept
{
    return _graphName;
}

// 방향 그래프 여부 반환하기
bool Graph::isDirected() const noexcept
{
    return _directed;
}

// 정점 개수 반환하기
int Graph::vertexCount() const noexcept
{
    return static_cast<int>(_vertices.size());
}

// 간선 개수 반환하기
int Graph::edgeCount() const noexcept
{
    int count = 0;

    for (const auto& edges : _adj) {
        count += static_cast<int>(edges.size());
    }

    return _directed ? count : count / 2;
}

// 정점을 추가하고 정점 번호 반환하기
int Graph::addVertex(const std::string& vertexName)
{
    auto found = _idByName.find(vertexName);

    if (found != _idByName.end()) {
        return found->second;
    }

    int id = static_cast<int>(_vertices.size());

    _vertices.push_back(Vertex{ id, vertexName });
    _adj.emplace_back();
    _idByName[vertexName] = id;

    return id;
}

// 정점 이름을 이용해 간선 추가하기
void Graph::addEdge(const std::string& fromName, const std::string& toName, double weight)
{
    int from = addVertex(fromName);
    int to = addVertex(toName);

    addEdge(from, to, weight);
}

// 정점 번호를 이용해 간선 추가하기
void Graph::addEdge(int from, int to, double weight)
{
    if (from < 0 || from >= vertexCount() || to < 0 || to >= vertexCount()) {
        throw std::out_of_range("Graph::addEdge(): invalid vertex id");
    }

    _adj[from].push_back(Edge{ from, to, weight });

    if (!_directed) {
        _adj[to].push_back(Edge{ to, from, weight });
    }
}

// 정점 존재 여부 확인하기
bool Graph::hasVertex(const std::string& vertexName) const
{
    return _idByName.find(vertexName) != _idByName.end();
}

// 정점 이름에 해당하는 정점 번호 반환하기
int Graph::idOf(const std::string& vertexName) const
{
    auto found = _idByName.find(vertexName);

    if (found == _idByName.end()) {
        throw std::invalid_argument("Unknown vertex name: " + vertexName);
    }

    return found->second;
}

// 정점 번호에 해당하는 정점 반환하기
const Vertex& Graph::vertex(int id) const
{
    if (id < 0 || id >= vertexCount()) {
        throw std::out_of_range("Graph::vertex(): invalid vertex id");
    }

    return _vertices[id];
}

// 전체 정점 목록 반환하기
const std::vector<Vertex>& Graph::vertices() const noexcept
{
    return _vertices;
}

// 특정 정점에 연결된 간선 목록 반환하기
const std::vector<Edge>& Graph::adjacentEdges(int id) const
{
    if (id < 0 || id >= vertexCount()) {
        throw std::out_of_range("Graph::adjacentEdges(): invalid vertex id");
    }

    return _adj[id];
}

// 전체 간선 목록 반환하기
std::vector<Edge> Graph::edges(bool uniqueUndirectedEdges) const
{
    std::vector<Edge> result;

    for (int u = 0; u < vertexCount(); ++u) {
        for (const Edge& e : _adj[u]) {
            if (!_directed && uniqueUndirectedEdges && e.from > e.to) {
                continue;
            }

            result.push_back(e);
        }
    }

    return result;
}

// 인접 행렬 생성하기
std::vector<std::vector<double>> Graph::adjacencyMatrix() const
{
    int n = vertexCount();
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, INF));

    for (int i = 0; i < n; ++i) {
        matrix[i][i] = 0.0;
    }

    for (int u = 0; u < n; ++u) {
        for (const Edge& e : _adj[u]) {
            matrix[e.from][e.to] = std::min(matrix[e.from][e.to], e.weight);
        }
    }

    return matrix;
}

// 인접 리스트 출력하기
void Graph::printAdjacencyList(std::ostream& os) const
{
    os << "\nGraph " << _graphName << " (" << vertexCount() << " vertices, "
        << edgeCount() << " edges)\n";

    for (const Vertex& v : _vertices) {
        os << " " << std::setw(5) << v.name << " : ";

        for (const Edge& e : _adj[v.id]) {
            os << "(" << vertex(e.to).name << ", " << e.weight << ") ";
        }

        os << '\n';
    }
}

// 인접 행렬 출력하기
void Graph::printAdjacencyMatrix(std::ostream& os) const
{
    auto matrix = adjacencyMatrix();

    os << "\nAdjacency Matrix of " << _graphName << "\n     |";

    for (const Vertex& v : _vertices) {
        os << std::setw(7) << v.name;
    }

    os << "\n------+" << std::string(vertexCount() * 7, '-') << '\n';

    for (int i = 0; i < vertexCount(); ++i) {
        os << std::setw(5) << vertex(i).name << " |";

        for (int j = 0; j < vertexCount(); ++j) {
            if (matrix[i][j] == INF) {
                os << std::setw(7) << "+oo";
            }
            else {
                os << std::setw(7) << matrix[i][j];
            }
        }

        os << '\n';
    }
}

// 파일에서 그래프 정보 읽어오기
Graph Graph::fgetGraph(const std::string& fileName, bool directed)
{
    std::ifstream fin(fileName);

    if (!fin) {
        throw std::runtime_error("Failed to open graph input file: " + fileName);
    }

    std::string graphName;
    int declaredVertexCount = 0;

    fin >> graphName >> declaredVertexCount;

    if (!fin) {
        throw std::runtime_error("Invalid graph file header: " + fileName);
    }

    Graph graph(graphName, directed);
    std::string from;
    std::string to;
    double weight = 0.0;

    while (fin >> from >> to >> weight) {
        graph.addEdge(from, to, weight);
    }

    if (declaredVertexCount != graph.vertexCount()) {
        std::cerr << "Warning: file declares " << declaredVertexCount
            << " vertices, but " << graph.vertexCount()
            << " vertices were actually found.\n";
    }

    return graph;
}

// 경로에 포함된 정점 이름들을 vector로 변환하기
std::vector<std::string> namesOfPath(const Graph& g, const std::vector<int>& path)
{
    std::vector<std::string> result;

    for (int id : path) {
        result.push_back(g.vertex(id).name);
    }

    return result;
}

// 경로 출력하기
void printPath(std::ostream& os, const Graph& g, const std::vector<int>& path)
{
    if (path.empty()) {
        os << "No path";
        return;
    }

    for (std::size_t i = 0; i < path.size(); ++i) {
        if (i > 0) {
            os << " -> ";
        }

        os << g.vertex(path[i]).name;
    }
}