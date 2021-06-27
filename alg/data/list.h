#pragma once
#include "array.h"
namespace alg {

template <typename T>
struct Slist {
    Slist() {}
    Slist(const T& d, Slist<T>* n)
        : data(d), next(n) {}

    T data{};
    Slist* next{nullptr};
};

template <typename T>
Slist<T>* MakeSlist(const Array<T>& array) {
    Slist<T> head;
    Slist<T>* last = &head;
    for (std::size_t i = 0; i < array.data.size(); i++) {
        Slist<T>* node = new Slist<T>(array.data[i], nullptr);
        last->next = node;
        last = node;
    }
    return head.next;
}

template <typename T>
void DeleteSlist(Slist<T>* node) {
    while (node) {
        Slist<T>* next = node->next;
        delete node;
        node = next;
    }
}

template <typename T>
bool IsSlistSorted(const Slist<T>* node) {
    bool ret = true;
    if (node) {
        while (node->next) {
            if (node->data > node->next->data) {
                ret = false;
                break;
            }
            node = node->next;
        }
    }

    if (ret) {
        std::cout << "\e[0;32mSlist is sorted\e[0m" << std::endl;
    } else {
        std::cout << "\e[1;31mSlist is not sorted\e[0m" << std::endl;
    }

    return ret;
}

} // namespace alg
