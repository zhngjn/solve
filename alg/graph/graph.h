#pragma once
#include <vector>
#include <iostream>

#include "edge.h"

namespace alg {

constexpr double kInf = 1e100;
const auto IsInf = [](double d) {
    return std::abs(d - kInf) < 1e-6;
};

class Graph {
public:
    Graph(int vertices)
        : V(vertices),
          E(0),
          adj(std::vector<std::vector<int>>(V, std::vector<int>(V, 0))) {
    }

    std::vector<Edge> Edges() const {
        std::vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adj[i][j] == 1)
                    edges.push_back(Edge(i, j));
            }
        }
        return edges;
    }

    void AddEdge(const Edge& e) {
        adj[e.u][e.v] = 1;
        adj[e.v][e.u] = 1;
        E++;
    }
    void AddEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
        E++;
    }

    void RemoveEdge(const Edge& e) {
        adj[e.u][e.v] = 0;
        adj[e.v][e.u] = 0;
        E--;
    }
    void RemoveEdge(int u, int v) {
        adj[u][v] = 0;
        adj[v][u] = 0;
        E--;
    }

    std::vector<int> Adj(int u) const {
        std::vector<int> nodes;
        for (int i = 0; i < V; i++) {
            if (adj[u][i] == 1)
                nodes.push_back(i);
        }
        return nodes;
    }

    int Deg(int u) const {
        return Adj(u).size();
    }

    void Show() const {
        std::cout << "Graph:" << V << std::endl;
        for (int i = 0; i < V; i++) {
            const auto nodes = Adj(i);
            if (!nodes.empty()) {
                for (int j : nodes) {
                    std::cout << "(" << i << "," << j << "),";
                }
                std::cout << std::endl;
            }
        }
    }

public:
    int V, E;
    std::vector<std::vector<int>> adj;
};

class DirectedGraph {
public:
    DirectedGraph(int vertices)
        : V(vertices),
          E(0),
          adj(std::vector<std::vector<int>>(V, std::vector<int>(V, 0))) {
    }

    std::vector<Edge> Edges() const {
        std::vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adj[i][j] == 1)
                    edges.push_back(Edge(i, j));
            }
        }
        return edges;
    }

    void AddEdge(const Edge& e) {
        adj[e.u][e.v] = 1;
        E++;
    }
    void AddEdge(int u, int v) {
        adj[u][v] = 1;
        E++;
    }

    void RemoveEdge(const Edge& e) {
        adj[e.u][e.v] = 0;
        E--;
    }
    void RemoveEdge(int u, int v) {
        adj[u][v] = 0;
        E--;
    }

    std::vector<int> Adj(int u) const {
        std::vector<int> nodes;
        for (int i = 0; i < V; i++) {
            if (adj[u][i] == 1)
                nodes.push_back(i);
        }
        return nodes;
    }

    void Show() const {
        std::cout << "DirectedGraph:" << V << std::endl;
        for (int i = 0; i < V; i++) {
            const auto nodes = Adj(i);
            if (!nodes.empty()) {
                for (int j : nodes) {
                    std::cout << "(" << i << "," << j << "),";
                }
                std::cout << std::endl;
            }
        }
    }

public:
    int V, E;
    std::vector<std::vector<int>> adj;
};

class WeightedGraph {
public:
    WeightedGraph(int vertices)
        : V(vertices),
          E(0),
          adj(std::vector<std::vector<double>>(V, std::vector<double>(V, kInf))) {
    }

    std::vector<Edge> Edges() const {
        std::vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (!IsInf( adj[i][j] ))
                    edges.push_back(Edge(i, j));
            }
        }
        return edges;
    }

    void AddEdge(const Edge& e) {
        adj[e.u][e.v] = e.w;
        adj[e.v][e.u] = e.w;
        E++;
    }
    void AddEdge(int u, int v, double w) {
        adj[u][v] = w;
        adj[v][u] = w;
        E++;
    }

    void RemoveEdge(const Edge& e) {
        adj[e.u][e.v] = kInf;
        adj[e.v][e.u] = kInf;
        E--;
    }
    void RemoveEdge(int u, int v) {
        adj[u][v] = kInf;
        adj[v][u] = kInf;
        E--;
    }

    std::vector<Edge> Edges(int u) const {
        std::vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            if (!IsInf( adj[u][i] ))
                edges.push_back(Edge(u, i, adj[u][i]));
        }
        return edges;
    }

    void Show() const {
        std::cout << "WeightedGraph:" << V << std::endl;
        for (int i = 0; i < V; i++) {
            const auto edges = Edges(i);
            if (!edges.empty()) {
                for (const auto& e : edges) {
                    std::cout << "(" << i << "," << e.v << "," << e.w << "),";
                }
                std::cout << std::endl;
            }
        }
    }

public:
    int V, E;
    std::vector<std::vector<double>> adj;
};

class DirectedWeightedGraph {
public:
    DirectedWeightedGraph(int vertices)
        : V(vertices),
          E(0),
          adj(std::vector<std::vector<double>>(V, std::vector<double>(V, kInf))) {
    }

    std::vector<Edge> Edges() const {
        std::vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (!IsInf( adj[i][j] ))
                    edges.push_back(Edge(i, j));
            }
        }
        return edges;
    }

    void AddEdge(const Edge& e) {
        adj[e.u][e.v] = e.w;
        E++;
    }
    void AddEdge(int u, int v, double w) {
        adj[u][v] = w;
        E++;
    }

    void RemoveEdge(const Edge& e) {
        adj[e.u][e.v] = kInf;
        E--;
    }
    void RemoveEdge(int u, int v) {
        adj[u][v] = kInf;
        E--;
    }

    std::vector<Edge> Edges(int u) const {
        std::vector<Edge> edges;
        for (int i = 0; i < V; i++) {
            if (!IsInf( adj[u][i] ))
                edges.push_back(Edge(u, i, adj[u][i]));
        }
        return edges;
    }

    void Show() const {
        std::cout << "DirectedWeightedGraph:" << V << std::endl;
        for (int i = 0; i < V; i++) {
            const auto edges = Edges(i);
            if (!edges.empty()) {
                for (const auto& e : edges) {
                    std::cout << "(" << i << "," << e.v << "," << e.w << "),";
                }
                std::cout << std::endl;
            }
        }
    }

public:
    int V, E;
    std::vector<std::vector<double>> adj;
};

} // namespace alg
