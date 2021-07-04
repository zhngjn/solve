#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "alg/common/common.h"

namespace alg {

class DFS {
public:
    DFS(int v)
        : V(v) {
        st = std::vector<int>(V, -1);
        pre = std::vector<int>(V, -1);
        cc = std::vector<int>(V, -1);
        color2 = std::vector<int>(V, -1);
        low = std::vector<int>(V, -1);
    }

    /**
     * @brief Print all the connected components in tree
     */
    void ShowTree() const {
        const auto roots = Roots();
        for (int root : roots) {
            std::cout << ToString(root);
        }
    }
    /**
     * @brief Print all the connected components
     */
    void ShowCC() const {
        std::unordered_map<int, std::vector<int>> components;
        int max_id = -1;
        for (int i = 0; i < V; i++) {
            components[cc[i]].push_back(i);
            if (cc[i] > max_id)
                max_id = cc[i];
        }
        for (int i = 0; i <= max_id; i++) {
            const auto& nodes = components[i];
            for (int u : nodes) {
                std::cout << u << ",";
            }
            std::cout << std::endl;
        }
    }

    void ShowBipartite() const {
        const auto& pre_ordered = OrderByPre();
        std::vector<int> v0, v1;
        for (int i : pre_ordered) {
            std::vector<int>& v = color2[i] == 0 ? v0 : v1;
            v.push_back(i);
        }

        // color0
        std::cout << "[c0]:";
        for (int i : v0) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
        // color1
        std::cout << "[c1]:";
        for (int i : v1) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }

    std::vector<int> OrderByPre() const {
        std::vector<std::pair<int, int>> pairs;
        for (int i = 0; i < V; i++) {
            pairs.push_back(std::make_pair(pre[i], i));
        }
        std::sort(pairs.begin(), pairs.end(), [](const auto& p1, const auto& p2){
            return p1.first < p2.first;
        });

        std::vector<int> ordered(V);
        std::transform(pairs.begin(), pairs.end(), ordered.begin(), [](const auto& p){
            return p.second;
        });
        return ordered;
    }

    /**
     * @brief convert connected component[cc] to string
     */
    std::string ToString(int cc) const {
        std::ostringstream oss;

        auto succ = Succ();

        std::vector<int> ws, ds;
        WidthAndDepth(ws, ds);

        int node_width = NodeWidth();
        int cur_depth = 0;
        std::stack<int> st;
        st.push(Root(cc));
        while (!st.empty()) {
            int u = STpop(st);

            if (ds[u] != cur_depth) {
                oss << std::endl;
                int prefix_size = ws[u] * (node_width + 1);
                for (int i = 0; i < prefix_size - 1; i++)
                    oss << " ";
                oss << "|" << std::endl;
                for (int i = 0; i < prefix_size; i++)
                    oss << " ";

                cur_depth = ds[u];
            }
            oss << "-" << std::setw(node_width) << std::right << u;

            const auto& p = succ[u];
            for (int i = p.size() - 1; i >= 0; i--) {
                st.push(p[i]);
            }
        }
        oss << std::endl;

        return oss.str();
    }

    int NodeWidth() const {
        int w = 0, n = V;
        while (n) {
            w++;
            n /= 10;
        }
        return w;
    }

    /**
     * @brief Root of connected component[cc]
     */
    int Root(int cc) const {
        while (st[cc] != cc) {
            if (st[cc] == -1)
                return -1;
            cc = st[cc];
        }
        return cc;
    }

    /**
     * @brief Roots of connected components
     */
    std::vector<int> Roots() const {
        std::vector<int> roots;
        for (int i = 0; i < V; i++) {
            if (st[i] == i) {
                roots.push_back(i);
            }
        }
        return roots;
    }
    std::vector<int> RootsCC() const {
        std::vector<int> roots;
        std::unordered_map<int, std::vector<int>> components;
        int max_id = -1;
        for (int i = 0; i < V; i++) {
            components[cc[i]].push_back(i);
            if (cc[i] > max_id)
                max_id = cc[i];
        }
        for (int i = 0; i <= max_id; i++) {
            roots.push_back(components[i][0]);
        }
        return roots;
    }

    /**
     * @brief Children links
     */
    std::unordered_map<int, std::vector<int>> Succ() const {
        std::unordered_map<int, std::vector<int>> post;
        for (int i = 0; i < V; i++) {
            if (st[i] != -1 && st[i] != i) {
                post[st[i]].push_back(i);
            }
        }
        return post;
    }

    void WidthAndDepthR(int u, int w, int d,
                        std::unordered_map<int, std::vector<int>>& post,
                        std::vector<int>& ws, std::vector<int>& ds) const {
        ws[u] = w;
        ds[u] = d;
        for (int i : post[u]) {
            WidthAndDepthR(i, w + 1, d, post, ws, ds);
            d++;
        }
    }

    /**
     * @brief Width and depth for show
     */
    void WidthAndDepth(std::vector<int>& ws, std::vector<int>& ds) const {
        ws.resize(V);
        ds.resize(V);
        auto succ = Succ();
        auto roots = Roots();
        for (int root : roots) {
            WidthAndDepthR(root, 0, 0, succ, ws, ds);
        }
    }

public:
    int V;
    // parent link
    std::vector<int> st;
    // preorder numbering
    std::vector<int> pre;
    // connected components
    std::vector<int> cc;
    // bipartite
    std::vector<int> color2;
    // minimum preorder number of back edges
    std::vector<int> low;
};

class BFS {
public:
private:
    int V;

};

} // namespace alg
