#pragma once

#include "tree_node.h"
#include "utils.h"

namespace alg {

/**
//            0
//           / \
//         /     \
//       /         \
//      1           7
//     / \         / \
//    /   \       /   \
//   2     3     8     10
//        / \     \      \
//       /   \     \      \
//      4     5     9     11
//           /            /
//          /            /
//         6            12
//                     /  \
//                    /    \
//                   13     14
//
// pre: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
// in: 2, 1, 4, 3, 6, 5, 0, 8, 9, 7, 10, 13, 12, 14, 11
// post: 2, 4, 6, 5, 3, 1, 9, 8, 13, 14, 12, 11, 10, 7, 0
*/
BTreeMap<int> BTreeMap_1() {
    std::vector<std::tuple<int, std::optional<int>, std::optional<int>>> tuples = {
        {12, 13, 14},
        {11, 12, {}},
        {5, 6, {}},
        {10, {}, 11},
        {8, {}, 9},
        {3, 4, 5},
        {7, 8, 10},
        {1, 2, 3},
        {0, 1, 7},
    };
    return MakeBTreeMap<int>(tuples);
}

} // namespace alg
