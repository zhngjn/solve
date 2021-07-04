#pragma once
#include <utility>
#include <iostream>
#include <stack>

#include "tree_node.h"
#include "utils.h"
#include "bi_path.h"
#include "alg/common/common.h"

namespace alg {

template <typename T>
class BTree {
public:
    BTree() = default;

    BTree(const BTreeMap<T>& tm) {
        root = MakeBTree(tm);
    }

    ~BTree() {
        DeleteBTree(root);
    }

    /**
     * @brief Create parent link
     */
    void CreateParentLinkR(Node<T>* node, Node<T>* parent) {
        if (!node)
            return;
        node->parent = parent;
        CreateParentLinkR(node->left, node);
        CreateParentLinkR(node->right, node);
    }
    void CreateParentLink() {
        CreateParentLinkR(root, nullptr);
    }

    /**
     * @brief Create node info
     */
    void CreateNodeInfoR(Node<T>* node) {
        if (!node)
            return;
        node->info = std::make_unique<NodeInfo<T>>();
        CreateNodeInfoR(node->left);
        CreateNodeInfoR(node->right);
    }
    void CreateNodeInfo() {
        CreateNodeInfoR(root);
    }

    /**
     * @brief Set depth
     */
    void SetDepthR(Node<T>* node, int d) {
        if (!node)
            return;
        node->info->depth = d;
        SetDepthR(node->left, d + 1);
        SetDepthR(node->right, d + 1);
    }
    void SetDepth() {
        int d = 0;
        SetDepthR(root, d);
    }

    /**
     * @brief Set height
     */
    int SetHeightR(Node<T>* node) {
        if (!node)
            return -1;

        int h1 = SetHeightR(node->left) + 1;
        int h2 = SetHeightR(node->right) + 1;
        int h = std::max(h1, h2);
        node->info->height = h;
        return h;
    }
    void SetHeight() {
        SetHeightR(root);
    }

    /**
     * @brief Set node type
     */
    void SetNodeTypeR(Node<T>* node) {
        if (!node)
            return;

        if (node->parent == nullptr) {
            node->info->type = kRoot;
        }
        else if (node->left == nullptr && node->right == nullptr) {
            node->info->type = kLeaf;
        }
        else {
            node->info->type = kInternal;
        }

        SetNodeTypeR(node->left);
        SetNodeTypeR(node->right);
    }
    void SetNodeType() {
        SetNodeTypeR(root);
    }

    /**
     * @brief Set sibling
     */
    void SetSiblingR(Node<T>* node) {
        if (!node)
            return;

        if (node->parent) {
            if (node == node->parent->left && node->parent->right) {
                node->info->right_sibling = node->parent->right->value;
            }
            else if (node == node->parent->right && node->parent->left) {
                node->info->left_sibling = node->parent->left->value;
            }
        }

        SetSiblingR(node->left);
        SetSiblingR(node->right);
    }
    void SetSibling() {
        SetSiblingR(root);
    }

    /**
     * Get left-most node
     */
    Node<T>* LeftMost(Node<T>* node) {
        if (!node)
            return nullptr;
        while (node->left)
            node = node->left;
        return node;
    }

    /**
     * Preorder traverse
     */
    template <typename FuncCB, typename... Args>
    void PreorderR(FuncCB&& cb, Node<T>* node, Args&&... args) {
        if (!node)
            return;

        std::forward<FuncCB>(cb)(node, std::forward<Args>(args)...);
        PreorderR(std::forward<FuncCB>(cb), node->left, std::forward<Args>(args)...);
        PreorderR(std::forward<FuncCB>(cb), node->right, std::forward<Args>(args)...);
    }
    template <typename FuncCB, typename... Args>
    void Preorder(FuncCB&& cb, Args&&... args) {
        PreorderR(std::forward<FuncCB>(cb), root, std::forward<Args>(args)...);
    }

    /**
     * Inorder traverse
     */
    template <typename FuncCB, typename... Args>
    void InorderR(FuncCB&& cb, Node<T>* node, Args&&... args) {
        if (!node)
            return;

        InorderR(std::forward<FuncCB>(cb), node->left, std::forward<Args>(args)...);
        std::forward<FuncCB>(cb)(node, std::forward<Args>(args)...);
        InorderR(std::forward<FuncCB>(cb), node->right, std::forward<Args>(args)...);
    }
    template <typename FuncCB, typename... Args>
    void Inorder(FuncCB&& cb, Args&&... args) {
        InorderR(std::forward<FuncCB>(cb), root, std::forward<Args>(args)...);
    }

    /**
     * Postorder traverse
     */
    template <typename FuncCB, typename... Args>
    void PostorderR(FuncCB&& cb, Node<T>* node, Args&&... args) {
        if (!node)
            return;

        PostorderR(std::forward<FuncCB>(cb), node->left, std::forward<Args>(args)...);
        PostorderR(std::forward<FuncCB>(cb), node->right, std::forward<Args>(args)...);
        std::forward<FuncCB>(cb)(node, std::forward<Args>(args)...);
    }
    template <typename FuncCB, typename... Args>
    void Postorder(FuncCB&& cb, Args&&... args) {
        PostorderR(std::forward<FuncCB>(cb), root, std::forward<Args>(args)...);
    }

    /**
     * Preorder traverse by non-recursive way
     */
    template <typename FuncCB, typename... Args>
    void PreorderI(FuncCB&& cb, Args&&... args) {
        if (!root)
            return;

        std::stack<Node<T>*> st;
        st.push(root);
        while (!st.empty()) {
            const auto node = STpop(st);
            std::forward<FuncCB>(cb)(node, std::forward<Args>(args)...);

            if (node->right)
                st.push(node->right);
            if (node->left)
                st.push(node->left);
        }
    }

    /**
     * Inorder traverse by non-recursive way
     */
    template <typename FuncCB, typename... Args>
    void InorderI(FuncCB&& cb, Args&&... args) {
        if (!root)
            return;

        std::stack<Node<T>*> st;
        const auto push_left_nodes = [&st](Node<T>* node){
            while (node) {
                st.push(node);
                node = node->left;
            }
        };

        push_left_nodes(root);
        while (!st.empty()) {
            const auto node = STpop(st);
            std::forward<FuncCB>(cb)(node, std::forward<Args>(args)...);

            push_left_nodes(node->right);
        }
    }

    /**
     * Postorder traverse by non-recursive way
     */
    template <typename FuncCB, typename... Args>
    void PostorderI(FuncCB&& cb, Args&&... args) {
        if (!root)
            return;

        std::stack<Node<T>*> st;
        st.push(root);
        while (!st.empty()) {
            auto node = st.top();
            if (node->info->post_state == 0) {
                node->info->post_state = 1;
                if (node->right)
                    st.push(node->right);
                if (node->left)
                    st.push(node->left);
            }
            else if (node->info->post_state == 1) {
                std::forward<FuncCB>(cb)(node, std::forward<Args>(args)...);
                st.pop();
            }
        }
    }

    /**
     * @brief Get postorder by preorder and inorder
     */
    void PreIn_2_Post_R(const std::vector<T>& pre, int pre_l, int pre_r,
                        const std::vector<T>& in, int in_l, int in_r,
                        std::vector<T>& post) {
        if (pre_l >= pre_r)
            return;

        T value = pre[pre_l];
        int in_m = std::distance(in.begin(), std::find(in.begin(), in.end(), value));
        int pre_m = pre_l + (in_m - in_l);
        PreIn_2_Post_R(pre, pre_l + 1, pre_m + 1, in, in_l, in_m, post);
        PreIn_2_Post_R(pre, pre_m + 1, pre_r, in, in_m + 1, in_r, post);
        post.push_back(value);
    }
    void PreIn_2_Post(BPath<T>& path) {
        PreIn_2_Post_R(path.pre, 0, path.pre.size(),
                       path.in, 0, path.in.size(),
                       path.post);
    }

    /**
     * @brief Get preorder by inorder and postorder
     */
    void InPost_2_Pre_R(const std::vector<T>& in, int in_l, int in_r,
                        const std::vector<T>& post, int post_l, int post_r,
                        std::vector<T>& pre) {
        if (post_l >= post_r)
            return;

        T value = post[post_r - 1];
        pre.push_back(value);
        int in_m = std::distance(in.begin(), std::find(in.begin(), in.end(), value));
        int post_m = post_l + (in_m - in_l);
        InPost_2_Pre_R(in, in_l, in_m, post, post_l, post_m, pre);
        InPost_2_Pre_R(in, in_m + 1, in_r, post, post_m, post_r - 1, pre);
    }
    void InPost_2_Pre(BPath<T>& path) {
        InPost_2_Pre_R(path.in, 0, path.in.size(),
                       path.post, 0, path.post.size(),
                       path.pre);
    }

    /**
     * @brief Get inorder by preorder and postorder
     */
    void PrePost_2_In_R(const std::vector<T>& pre, int pre_l, int pre_r,
                        const std::vector<T>& post, int post_l, int post_r,
                        std::vector<T>& in) {
        if (pre_l >= pre_r)
            return;

        T value = pre[pre_l];
        if (pre_l + 1 < pre_r) {
            int post_m = std::distance(post.begin(), std::find(post.begin(), post.end(), pre[pre_l + 1]));
            if (post_m + 2 == post_r) {
                std::cerr << "\e[1;31mAmbiguous to contruct inorder from preorder and postorder \e[0m" << std::endl;
            }
            int pre_m = pre_l + 1 + (post_m - post_l);
            PrePost_2_In_R(pre, pre_l + 1, pre_m + 1, post, post_l, post_m + 1, in);
            in.push_back(value);
            PrePost_2_In_R(pre, pre_m + 1, pre_r, post, post_m + 1, post_r, in);
        }
        else {
            in.push_back(value);
        }
    }
    void PrePost_2_In(BPath<T>& path) {
        PrePost_2_In_R(path.pre, 0, path.pre.size(),
                       path.post, 0, path.post.size(),
                       path.in);
    }

public:
    Node<T>* root = nullptr;
};

} // namespace alg
