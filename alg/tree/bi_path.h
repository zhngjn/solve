#pragma once
#include <vector>

namespace alg {

template <typename T>
struct BPath {
    // pre-order traverse
    std::vector<T> pre;
    // in-order traverse
    std::vector<T> in;
    // post-order traverse
    std::vector<T> post;
};

} // namespace alg
