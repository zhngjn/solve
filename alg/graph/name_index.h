#pragma once
#include <cstdlib>
#include "alg/tree/node.h"

namespace alg {

class NameIndex {
public:
    struct IdxChar {
        int index;
        char c;
    };
    using Node = Tnode3<IdxChar>;
    using Link = Node*;

    ~NameIndex() {
        DeleteTree(root);
    }

    int IndexByName(const char* name) {
        int index;
        root = IndexR(root, name, 0, index);
        return index;
    }

    int Count() const {
        return N;
    }

private:
    Link IndexR(Link l, const char* name, std::size_t i, int& index) {
        char c = name[i];
        if (!l) {
            l = NewNode(c);
        }
        if (c == 0) {
            if (l->value.index == -1)
                l->value.index = N++;
            index = l->value.index;
            return l;
        }
        if (c < l->value.c)
            l->left = IndexR(l->left, name, i, index);
        else if (c == l->value.c)
            l->mid = IndexR(l->mid, name, i + 1, index);
        else
            l->right = IndexR(l->right, name, i, index);
        return l;
    }

    Link NewNode(char c) {
        Link l = new Node();
        l->value.c = c;
        l->value.index = -1;
        l->left = l->mid = l->right = nullptr;
        return l;
    }

private:
    int N = 0;
    Link root = nullptr;
};

} // namespace alg
