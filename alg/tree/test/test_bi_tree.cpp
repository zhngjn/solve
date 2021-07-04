#include <iostream>

#include "alg/tree/bi_tree.h"
#include "alg/tree/bi_instance.h"
#include "alg/common/common.h"

using namespace alg;

int main() {
    BTreeMap<int> tm = BTreeMap_1();
    BTree tree(tm);
    tree.CreateParentLink();
    tree.CreateNodeInfo();

    tree.SetDepth();
    tree.SetHeight();
    tree.SetNodeType();
    tree.SetSibling();

    {
        std::cout << "Node info:" << std::endl;
        tree.Preorder([](Node<int>* node){
             std::cout << Node2Str(node) << std::endl;
        });
    }

    std::cout << "---------------------------------------------" << std::endl;
    {
        std::cout << "Traverse:" << std::endl;
        std::vector<int> pre, in, post;
        tree.Preorder([&pre](Node<int>* node){
            pre.push_back(node->value);
        });
        tree.Inorder([&in](Node<int>* node){
            in.push_back(node->value);
        });
        tree.Postorder([&post](Node<int>* node){
            post.push_back(node->value);
        });
        std::cout << "pre: " << Cont2Str(pre) << std::endl;
        std::cout << "in: " << Cont2Str(in) << std::endl;
        std::cout << "post: " << Cont2Str(post) << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
    {
        std::cout << "Traverse by non-recursive way:" << std::endl;
        std::vector<int> pre, in, post;
        tree.PreorderI([&pre](Node<int>* node){
            pre.push_back(node->value);
        });
        tree.InorderI([&in](Node<int>* node){
            in.push_back(node->value);
        });
        tree.PostorderI([&post](Node<int>* node){
            post.push_back(node->value);
        });
        std::cout << "pre: " << Cont2Str(pre) << std::endl;
        std::cout << "in: " << Cont2Str(in) << std::endl;
        std::cout << "post: " << Cont2Str(post) << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
    {
        std::cout << "PreIn => Post:" << std::endl;
        BPath<int> path;
        path.pre = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        path.in = {2, 1, 4, 3, 6, 5, 0, 8, 9, 7, 10, 13, 12, 14, 11};
        tree.PreIn_2_Post(path);
        std::cout << "post:" << Cont2Str(path.post) << std::endl;
    }
    {
        std::cout << "InPost => Pre:" << std::endl;
        BPath<int> path;
        path.in = {2, 1, 4, 3, 6, 5, 0, 8, 9, 7, 10, 13, 12, 14, 11};
        path.post = {2, 4, 6, 5, 3, 1, 9, 8, 13, 14, 12, 11, 10, 7, 0};
        tree.InPost_2_Pre(path);
        std::cout << "pre:" << Cont2Str(path.pre) << std::endl;
    }
    {
        std::cout << "PrePost => In:" << std::endl;
        BPath<int> path;
        path.pre = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        path.post = {2, 4, 6, 5, 3, 1, 9, 8, 13, 14, 12, 11, 10, 7, 0};
        tree.PrePost_2_In(path);
        std::cout << "in:" << Cont2Str(path.in) << std::endl;
    }
}
