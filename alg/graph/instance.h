#pragma once

#include "graph.h"

namespace alg {

/**
//     0 -------------- 6          -7-
//     |\  \            /           |
//     | \   \          /
//     |  \    \       /
//     |   1 ----2     /
//     |       / |     /
//     |     /   |    /
//     |   3     |    /
//     |     \   |    /
//     |       \ |   /
//     |        \|  /
//     |         4 /
//     |       /
//     |     /
//     |   /
//     | /
//     5
*/
Graph Graph_1() {
    Graph g(8);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(0, 5);
    g.AddEdge(0, 6);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(2, 4);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(4, 6);
    return g;
}

/**
//     0 -------------- 6
//     |\  \            /
//     | \   \          /
//     |  \    \       /
//     |   1 ----2     /
//     |       / |     /
//     |     /   |    /
//     |   3     |    /
//     |     \   |    /
//     |       \ |   /
//     |        \|  /
//     |         4 /
//     |       /
//     |     /
//     |   /
//     | /
//     5
*/
Graph Graph_2() {
    Graph g(7);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(0, 5);
    g.AddEdge(0, 6);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(2, 4);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(4, 6);
    return g;
}

/**
//     0 -------------- 6
//     |\  \            /
//     | \   \          /
//     |  \    \       /
//     |   1 ----2     /
//     |   |   / |     /
//     |   | /   |    /
//     |   3     |    /
//     |  /  \   |    /
//     |  /    \ |   /
//     |  /     \|  /
//     | /      4 /
//     | /     /
//     | /   /
//     |/  /
//     |//
//     5
*/
Graph Graph_3() {
    Graph g(7);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(0, 5);
    g.AddEdge(0, 6);
    g.AddEdge(1, 2);
    g.AddEdge(1, 3);
    g.AddEdge(2, 3);
    g.AddEdge(2, 4);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(4, 5);
    g.AddEdge(4, 6);
    return g;
}

/**
//     0 -----2
//     |\      \
//     |  \       \
//     |    \        \
//     |      \        6
//     |  1---- 7      /
//     |        |     /
//     |    3   |    /
//     |   / \  |   /
//     |  /   \ |  /
//     | /     \| /
//     5--------4
*/
Graph Graph_4() {
    Graph g(8);
    g.AddEdge(0, 2);
    g.AddEdge(0, 5);
    g.AddEdge(0, 7);
    g.AddEdge(1, 7);
    g.AddEdge(2, 6);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(4, 5);
    g.AddEdge(4, 6);
    g.AddEdge(4, 7);
    return g;
}

/**
//     0 -------------- 6      7 ------- 8
//     |\  \            /
//     | \   \          /
//     |  \    \       /
//     |   1     2     /
//     |               /       9 ------- 10
//     |              /        |\
//     |   3          /        |  \
//     |   / \       /         |    \
//     |   /   \    /          |      \
//     |  /      \  /          11 ------ 12
//     |  /       4
//     |  /     /
//     | /    /
//     | /  /
//     |/ /
//     5
*/
Graph Graph_5() {
    Graph g(13);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(0, 5);
    g.AddEdge(0, 6);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(4, 5);
    g.AddEdge(4, 6);
    g.AddEdge(7, 8);
    g.AddEdge(9, 10);
    g.AddEdge(9, 11);
    g.AddEdge(9, 12);
    g.AddEdge(11, 12);
    return g;
}

/**
//     0
//     |\\
//     |\ \                     6 -----7----- 8
//     | \ \                     \           /
//     | \  1-----2               \         /
//     | \          \ \            \       /
//     |  \             \ \         \     /
//     |   3                \ \      \   /
//     |     \                  \ \ \  9 ---- 10
//     |       \                         \
//     |         \                        \
//     |           4 \ \                   \
//     |         /      \ \                 \
//     |       /           \ \               \
//     |     /                \ \ \ \  11 ----12
//     |   /
//     5 /
*/
Graph Graph_6() {
    Graph g(13);
    g.AddEdge(0, 1);
    g.AddEdge(0, 3);
    g.AddEdge(0, 5);
    g.AddEdge(1, 2);
    g.AddEdge(2, 9);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(4, 11);
    g.AddEdge(6, 7);
    g.AddEdge(6, 9);
    g.AddEdge(7, 8);
    g.AddEdge(8, 9);
    g.AddEdge(9, 10);
    g.AddEdge(9, 12);
    g.AddEdge(11, 12);
    return g;
}

/**
//     0 ---------- 6 ---- 7 --- 8
//     |\          /        \    |
//     | \        /          \   |
//     |  \      /            \  |
//     |   1----2              \ |
//     |                        10
//     |
//     |     3           9
//     |    /  \       / |
//     |   /    \    /   |
//     |  /    / 4 /     |
//     | /   /     \     |
//     |/  /         \   |
//     5 /             \ 11---12
*/
Graph Graph_7() {
    Graph g(13);
    g.AddEdge(0, 1);
    g.AddEdge(0, 5);
    g.AddEdge(0, 6);
    g.AddEdge(1, 2);
    g.AddEdge(2, 6);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(4, 5);
    g.AddEdge(4, 9);
    g.AddEdge(4, 11);
    g.AddEdge(6, 7);
    g.AddEdge(7, 8);
    g.AddEdge(7, 10);
    g.AddEdge(8, 10);
    g.AddEdge(9, 11);
    g.AddEdge(11, 12);
    return g;
}

} // namespace alg
