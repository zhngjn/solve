package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "node",
    srcs = [
        "node.cpp"
    ],
    hdrs = [
        "node.h"
    ],
)

cc_library(
    name = "node_info",
    srcs = [
        "node_info.cpp"
    ],
    hdrs = [
        "node_info.h"
    ],
    deps = [
        "//alg/common:traits"
    ]
)

cc_library(
    name = "tree_node",
    srcs = [
        "tree_node.cpp"
    ],
    hdrs = [
        "tree_node.h"
    ],
    deps = [
        ":node_info",
    ]
)

cc_library(
    name = "utils",
    srcs = [
        "utils.cpp",
    ],
    hdrs = [
        "utils.h",
        "bi_instance.h",
    ],
    deps = [
        ":tree_node",
    ]
)

cc_library(
    name = "bi_path",
    srcs = [
        "bi_path.cpp"
    ],
    hdrs = [
        "bi_path.h"
    ],
)

cc_library(
    name = "bi_tree",
    srcs = [
        "bi_tree.cpp"
    ],
    hdrs = [
        "bi_tree.h"
    ],
    deps = [
        ":tree_node",
        ":utils",
        ":bi_path",
        "//alg/common:common",
    ],
)
