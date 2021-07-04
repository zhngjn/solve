#include <iostream>

#include "path.h"

namespace alg {

void PrintPath(const std::vector<int>& path) {
    std::cout << "path:";
    for (std::size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1)
            std::cout << " - ";
    }
    std::cout << std::endl;
}

void PrintPath(const std::vector<LinkEdge>& path) {
    std::cout << "path:";
    for (std::size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1)
            std::cout << " - ";
    }
    std::cout << std::endl;
}

void PrintBridges(const std::vector<Edge>& bridges) {
    std::cout << "bridges:";
    for (std::size_t i = 0; i < bridges.size(); i++) {
        std::cout << "[" << bridges[i].u << " " << bridges[i].v << "], ";
    }
    std::cout << std::endl;
}

void PrintSeparations(const std::vector<int>& separations) {
    std::cout << "separation vertices:";
    for (std::size_t i = 0; i < separations.size(); i++) {
        std::cout << separations[i] << ", ";
    }
    std::cout << std::endl;
}

} // namespace alg
