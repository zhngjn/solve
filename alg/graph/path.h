#pragma once
#include <unordered_map>
#include <stack>
#include <algorithm>

#include "alg/common/common.h"
#include "graph.h"
#include "search.h"

namespace alg {

void PrintPath(const std::vector<int>& path);
void PrintPath(const std::vector<LinkEdge>& path);
void PrintBridges(const std::vector<Edge>& bridges);
void PrintSeparations(const std::vector<int>& separations);

class Path {
public:
    Path(const Graph& g)
        : graph(g) {}

    /**
     * @brief Path from u to v
     */
    bool PathDsfR(int u, int v, std::unordered_map<int, bool>& visited, std::vector<int>& path) {
        if (u == v) {
            path.push_back(v);
            return true;
        }
        visited[u] = true;
        for (int i : graph.Adj(u)) {
            if (!visited[i]) {
                if (PathDsfR(i, v, visited, path)) {
                    path.push_back(u);
                    return true;
                }
            }
        }
        return false;
    }
    bool PathDsf(int u, int v, std::vector<int>& path) {
        std::unordered_map<int, bool> visited;
        bool res = PathDsfR(u, v, visited, path);

        std::reverse(path.begin(), path.end());

        return res;
    }

    /**
     * @brief Hamilton path
     */
    bool PathHamiltonR(int u, int v, int depth, std::unordered_map<int, bool>& visited, std::vector<int>& path) {
        if (u == v) {
            if (depth == 0) {
                path.push_back(v);
                return true;
            }
            else {
                return false;
            }
        }
        visited[u] = true;
        for (int i : graph.Adj(u)) {
            if (!visited[i]) {
                if (PathHamiltonR(i, v, depth - 1, visited, path)) {
                    path.push_back(u);
                    return true;
                }
            }
        }
        visited[u] = false;
        return false;
    }
    bool PathHamilton(int u, int v, std::vector<int>& path) {
        std::unordered_map<int, bool> visited;

        bool res = PathHamiltonR(u, v, graph.V - 1, visited, path);

        std::reverse(path.begin(), path.end());
        return res;
    }

    /**
     * @brief Euler path
     */
    bool PathEulerExist(int u, int v) {
        if ((graph.Deg(u) + graph.Deg(v)) % 2 != 0)
            return false;
        for (int i = 0; i < graph.V; i++) {
            if (i != u && i != v) {
                if ((graph.Deg(i) % 2) != 0)
                    return false;
            }
        }
        return true;
    }
    int PathEulerR(Graph& g, int u, std::stack<int>& st) {
        while (!g.Adj(u).empty()) {
            st.push(u);
            int v = g.Adj(u)[0];
            g.RemoveEdge(u, v);
            u = v;
        }
        return u;
    }
    bool PathEuler(int u, int v, std::vector<int>& path) {
        if (!PathEulerExist(u, v))
            return false;

        path.push_back(v);
        std::stack<int> st;
        Graph g = graph;
        while (PathEulerR(g, u, st) == u && !st.empty()) {
            u = STpop(st);
            path.push_back(u);
        }

        std::reverse(path.begin(), path.end());
        return true;
    }

    /**
     * @brief Dfs
     */
    void DfsR(int u, int& pre, DFS& dfs) {
        for (int i : graph.Adj(u)) {
            if (dfs.pre[i] == -1) {
                dfs.st[i] = u;
                dfs.pre[i] = pre++;
                DfsR(i, pre, dfs);
            }
        }
    }
    void Dfs(DFS& dfs, int u) {
        int pre = 0;
        dfs.st[u] = u;
        dfs.pre[u] = pre++;
        DfsR(u, pre, dfs);
    }

    /**
     * @brief Connected components
     */
    void DfsCCR(DFS& dfs, int u, int id) {
        dfs.cc[u] = id;
        for (int i : graph.Adj(u)) {
            if (dfs.cc[i] == -1) {
                DfsCCR(dfs, i, id);
            }
        }
    }
    void DfsCC(DFS& dfs) {
        int id = 0;
        for (int u = 0; u < graph.V; u++) {
            if (dfs.cc[u] == -1) {
                DfsCCR(dfs, u, id++);
            }
        }
    }
    void Dfs(DFS& dfs) {
        DfsCC(dfs);
        auto roots = dfs.RootsCC();
        for (int u : roots) {
            Dfs(dfs, u);
        }
    }

    /**
     * @brief DfsEuler path
     */
    void DfsEulerR(DFS& dfs, const Edge& e, int& pre, std::vector<LinkEdge>& edges) {
        dfs.pre[e.v] = pre++;
        for (int i : graph.Adj(e.v)) {
            if (dfs.pre[i] == -1) {
                edges.push_back(LinkEdge(Edge(e.v, i), kTreeLink));
                DfsEulerR(dfs, Edge(e.v, i), pre, edges);
            }
            else if (dfs.pre[i] < dfs.pre[e.u]) {
                edges.push_back(LinkEdge(Edge(e.v, i), kBackLink));
                edges.push_back(LinkEdge(Edge(i, e.v), kBackLink));
            }
        }
        edges.push_back(LinkEdge(Edge(e.v, e.u), kParentLink));
    }
    void DfsEuler(DFS& dfs, const Edge& e, std::vector<LinkEdge>& edges) {
        int pre = 0;
        dfs.pre[e.u] = pre++;
        edges.push_back(LinkEdge(Edge(e.u, e.v), kTreeLink));
        DfsEulerR(dfs, e, pre, edges);
    }

    /**
     * @brief Bipartite
     */
    bool DfsBipartiteR(DFS& dfs, int u, int& pre, int c) {
        dfs.pre[u] = pre++;
        dfs.color2[u] = c;
        for (int i : graph.Adj(u)) {
            if (dfs.color2[i] == -1) {
                if (!DfsBipartiteR(dfs, i, pre, 1 - c)) {
                    return false;
                }
            }
            else if (dfs.color2[i] == c) {
                return false;
            }
        }
        return true;
    }
    bool DfsBipartite(DFS& dfs) {
        int pre = 0;
        for (int u = 0; u < graph.V; u++) {
            if (dfs.color2[u] == -1) {
                if (!DfsBipartiteR(dfs, u, pre, 0))
                    return false;
            }
        }
        return true;
    }

    /**
     * @brief Edge-connected components
     */
    void DfsBridgesR(DFS& dfs, const Edge& e, int& pre, std::vector<Edge>& bridges) {
        dfs.pre[e.v] = pre++;
        dfs.low[e.v] = dfs.pre[e.v];
        for (int i : graph.Adj(e.v)) {
            if (dfs.pre[i] == -1) {
                DfsBridgesR(dfs, Edge(e.v, i), pre, bridges);
                if (dfs.low[i] < dfs.low[e.v])
                    dfs.low[e.v] = dfs.low[i];

                if (dfs.pre[i] == dfs.low[i])
                    bridges.push_back(Edge(e.v, i));
            }
            else if (i != e.u) {
                if (dfs.low[i] < dfs.low[e.v])
                    dfs.low[e.v] = dfs.low[i];
            }
        }
    }
    void DfsBridges(DFS& dfs, const Edge& e, std::vector<Edge>& bridges) {
        int pre = 0;
        DfsBridgesR(dfs, e, pre, bridges);
    }

    /**
     * @brief Separation vertices
     */
//    void DfsSeparationVerticesR(DFS& dfs, const Edge& e, int& pre, std::vector<int>& separations) {
//        dfs.pre[e.v] = pre++;
//        dfs.low[e.v] = dfs.pre[e.v];
//        bool is_separation = true;
//        for (int i : graph.Adj(e.v)) {
//            if (dfs.pre[i] == -1) {
//                DfsSeparationVerticesR(dfs, Edge(e.v, i), pre, separations);
//                if (dfs.low[i] < dfs.low[e.v])
//                    dfs.low[e.v] = dfs.low[i];
//            }
//            else if (i != e.u) {
//                if (dfs.low[i] < dfs.low[e.v])
//                    dfs.low[e.v] = dfs.low[i];
//            }

//            if ((dfs.pre[i] - dfs.pre[e.v]) * (dfs.low[i] - dfs.low[e.v]) < 0)
//                is_separation = false;
//        }
//        if (is_separation)
//            separations.push_back(e.v);
//    }
//    void DfsSeparationVertices(DFS& dfs, const Edge& e, std::vector<int>& separations) {
//        int pre = 0;
//        DfsSeparationVerticesR(dfs, e, pre, separations);
//    }

private:
    Graph graph;
};

} // namespace alg
