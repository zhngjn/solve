package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "graph",
    srcs = [
        "graph.cpp",
        "edge.cpp",
    ],
    hdrs = [
        "graph.h",
        "edge.h",
        "instance.h",
    ],
)

cc_library(
    name = "path",
    srcs = [
        "path.cpp",
    ],
    hdrs = [
        "path.h",
    ],
    deps = [
        ":graph",
        ":search",
        "//alg/common",
    ]
)

cc_library(
    name = "search",
    srcs = [
        "search.cpp",
    ],
    hdrs = [
        "search.h",
    ],
    deps = [
        "//alg/common",
    ]
)

cc_library(
    name = "name_index",
    srcs = [
        "name_index.cpp",
    ],
    hdrs = [
        "name_index.h",
    ],
    deps = [
        "//alg/tree:node",
    ]
)

cc_binary(
    name = "test_name_index",
    srcs = [
        "test_name_index.cpp",
    ],
    deps = [
        ":name_index",
    ],
)

cc_binary(
    name = "test_path",
    srcs = [
        "test_path.cpp",
    ],
    deps = [
        ":path",
    ],
)
