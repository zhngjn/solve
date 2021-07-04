#pragma once
#include <ostream>
#include <unordered_map>

#include "alg/common/traits.h"

namespace alg {

enum NodeType {
    kUnknown,
    kRoot,
    kInternal,
    kLeaf,
};

template <typename T>
struct NodeInfo {
    NodeInfo() = default;

    // node type
    NodeType type = kUnknown;
    // node depth, distance from root to the node
    int depth = -1;
    // node height, max distance from the node to leaf node
    int height = -1;
    // left sibling;
    T left_sibling = TypeTraits<T>::Invalid;
    // right sibling;
    T right_sibling = TypeTraits<T>::Invalid;

    int post_state = 0;
};

std::ostream& operator<<(std::ostream& strm, NodeType type) {
    static const std::unordered_map<NodeType, std::string> type_2_str = {
        {kUnknown, "unknown"},
        {kRoot, "root"},
        {kInternal, "internal"},
        {kLeaf, "leaf"},
    };
    if (type_2_str.find(type) != type_2_str.end())
        return strm << type_2_str.at(type);
    else
        return strm << "?";
}

} // namespace alg
