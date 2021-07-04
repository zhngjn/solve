#pragma once
#include <utility>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <algorithm>
#include <vector>

#include "tree_node.h"

namespace alg {

template <typename T>
std::pair<bool, Node<T>*> FindBTreeNode(Node<T>* node, const T& value) {
    if (node == nullptr) {
        return std::make_pair(false, nullptr);
    }

    if (node->value == value) {
        return std::make_pair(true, node);
    }
    const auto lres = FindBTreeNode(node->left, value);
    if (lres.first) {
        return lres;
    }
    else {
        return FindBTreeNode(node->right, value);
    }
}

template <typename T>
struct LRPair {
    std::unique_ptr<T> left = nullptr;
    std::unique_ptr<T> right = nullptr;
};

template <typename T>
using BTreeMap = std::unordered_map<T, LRPair<T>>;

template <typename T>
BTreeMap<T> MakeBTreeMap(const std::vector<std::tuple<T, std::optional<T>, std::optional<T>>>& tupls) {
    BTreeMap<T> tm;
    for (const auto& v : tupls) {
        LRPair<T> lr_pair;
        if (std::get<1>(v).has_value()) {
            lr_pair.left = std::make_unique<T>(std::get<1>(v).value());
        }
        if (std::get<2>(v).has_value()) {
            lr_pair.right = std::make_unique<T>(std::get<2>(v).value());
        }
        tm.emplace(std::get<0>(v), std::move(lr_pair));
    }
    return tm;
}

template <typename T>
Node<T>* MakeBTree(const BTreeMap<T>& tm) {
    std::unordered_set<Node<T>*> cache{};

    const auto node_from_cache_or_new = [&cache](const T& value) {
        std::pair<bool, Node<T>*> find_result;
        const auto pos = std::find_if(cache.begin(), cache.end(), [&value, &find_result](Node<T>* node) {
            const auto res = FindBTreeNode(node, value);
            if (res.first) {
                find_result = res;
                return true;
            }
            return false;
        });
        if (pos != cache.end()) {
            return find_result;
        }
        else {
            Node<T>* node = new Node<T>(value, nullptr, nullptr);
            return std::make_pair(false, node);
        }
    };

    const auto root_from_cache_and_remove_or_new = [&cache](const T& value) {
        const auto pos = std::find_if(cache.begin(), cache.end(), [&value](Node<T>* node) {
            return node->value == value;
        });
        if (pos != cache.end()) {
            const auto node = *pos;
            cache.erase(pos);
            return std::make_pair(true, node);
        }
        else {
            Node<T>* node = new Node<T>(value, nullptr, nullptr);
            return std::make_pair(false, node);
        }
    };

    for (const auto& item : tm) {
        const auto res = node_from_cache_or_new(item.first);
        if (item.second.left) {
            res.second->left = root_from_cache_and_remove_or_new(*item.second.left).second;
        }
        if (item.second.right) {
            res.second->right = root_from_cache_and_remove_or_new(*item.second.right).second;
        }
        if (!res.first) {
            cache.insert(res.second);
        }
    }

    assert(cache.size() == 1);
    return *cache.begin();
}

template <typename T>
void DeleteBTree(Node<T>* root) {
    if (root) {
        DeleteBTree(root->left);
        root->left = nullptr;
        DeleteBTree(root->right);
        root->right = nullptr;
        delete root;
    }
}

} // namespace alg
