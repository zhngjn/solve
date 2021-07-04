#pragma once
#include <memory>
#include <sstream>

#include "node_info.h"

namespace alg {

template <typename T>
struct Node {
    Node(const T& v, Node* l, Node* r)
        : value(v), left(l), right(r) {

    }

    T value{};
    Node* left{nullptr};
    Node* right{nullptr};
    Node* parent{nullptr};
    std::unique_ptr<NodeInfo<T>> info{nullptr};
};

template <typename T>
std::string Node2Str(const Node<T>* node) {
    if (!node) {
        return "";
    }

    std::stringstream ss;
    ss << node->value << ": ";
    if (node->info) {
        ss << "[type]:" << node->info->type << " ";
        ss << "[depth]:" << node->info->depth << " ";
        ss << "[height]:" << node->info->height << " ";
        if (node->info->left_sibling != TypeTraits<T>::Invalid) {
            ss << "[left_sibling]:" << node->info->left_sibling << " ";
        }
        if (node->info->right_sibling != TypeTraits<T>::Invalid) {
            ss << "[right_sibling]:" << node->info->right_sibling << " ";
        }
    }
    return ss.str();
}

} // namespace alg
