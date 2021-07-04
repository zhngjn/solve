#include <cassert>

#include "path.h"
#include "instance.h"

using namespace alg;

int main() {
    // path dsf
    std::cout << "*** path dsf" << std::endl;
    {
        Path path(Graph_1());
        std::vector<int> p;
        assert(path.PathDsf(0, 4, p) == true);
        PrintPath(p);
    }
    {
        Path path(Graph_1());
        std::vector<int> p;
        assert(path.PathDsf(1, 7, p) == false);
        PrintPath(p);
    }

    // hamilton path
    std::cout << "*** hamilton path" << std::endl;
    {
        Path path(Graph_2());
        std::vector<int> p;
        assert(path.PathHamilton(0, 5, p) == false);
        PrintPath(p);
    }
    {
        Path path(Graph_3());
        std::vector<int> p;
        assert(path.PathHamilton(0, 5, p) == true);
        PrintPath(p);
    }

    // euler path
    std::cout << "*** euler path" << std::endl;
    {
        Path path(Graph_2());
        std::vector<int> p;
        assert(path.PathEuler(0, 0, p) == true);
        PrintPath(p);
    }

    // dfs
    std::cout << "*** dfs" << std::endl;
    {
        const auto& graph = Graph_4();
        Path path(graph);
        DFS dfs(graph.V);
        path.Dfs(dfs, 0);
        dfs.ShowTree();
    }

    // dfs cc
    std::cout << "*** dfs cc" << std::endl;
    {
        const auto& graph = Graph_5();
        Path path(graph);
        DFS dfs(graph.V);
        path.DfsCC(dfs);
        dfs.ShowCC();
    }

    // dfs forest
    std::cout << "*** dfs forest" << std::endl;
    {
        const auto& graph = Graph_5();
        Path path(graph);
        DFS dfs(graph.V);
        path.Dfs(dfs);
        dfs.ShowTree();
    }

    // dfs euler
    std::cout << "*** dfs euler" << std::endl;
    {
        const auto& graph = Graph_4();
        Path path(graph);
        DFS dfs(graph.V);
        std::vector<LinkEdge> edges;
        path.DfsEuler(dfs, Edge(0, 2), edges);
        PrintPath(edges);
    }

    // dfs bipartite
    std::cout << "*** dfs bipartite" << std::endl;
    {
        const auto& graph = Graph_4();
        Path path(graph);
        DFS dfs(graph.V);
        assert(path.DfsBipartite(dfs) == false);
    }
    {
        const auto& graph = Graph_6();
        Path path(graph);
        DFS dfs(graph.V);
        assert(path.DfsBipartite(dfs) == true);
        dfs.ShowBipartite();
    }

    // dfs ecc
    std::cout << "*** dfs ecc" << std::endl;
    {
        const auto& graph = Graph_7();
        Path path(graph);
        DFS dfs(graph.V);
        std::vector<Edge> bridges;
        path.DfsBridges(dfs, Edge(0, 1), bridges);
        PrintBridges(bridges);
    }

    // dfs bcc
//    std::cout << "*** dfs bcc" << std::endl;
//    {
//        const auto& graph = Graph_7();
//        Path path(graph);
//        DFS dfs(graph.V);
//        std::vector<int> separations;
//        path.DfsSeparationVertices(dfs, Edge(0, 1), separations);
//        PrintSeparations(separations);
//    }
}
