#pragma once

namespace alg {

template <typename T>
struct Tnode {
    T value;
    Tnode* left, *right;
};

template <typename T>
struct Tnode3 {
    T value;
    Tnode3* left, *mid, *right;
};

template <typename T>
void DeleteTree(Tnode<T>* root) {
    if (root) {
        DeleteTree(root->left);
        root->left = nullptr;
        DeleteTree(root->right);
        root->right = nullptr;
        delete root;
    }
}

template <typename T>
void DeleteTree(Tnode3<T>* root) {
    if (root) {
        DeleteTree(root->left);
        root->left = nullptr;
        DeleteTree(root->mid);
        root->mid = nullptr;
        DeleteTree(root->right);
        root->right = nullptr;
        delete root;
    }
}

} // namespace alg
