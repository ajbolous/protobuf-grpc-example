load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")


# General Proto Library deps
proto_library(
    name = "protos",
    srcs = ["protos/entity.proto"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "utils",
    srcs = glob(["logging/*.cc", "manager/*.cc"]),
    hdrs = glob(["logging/*.h", "manager/*.h"]),
    visibility = ["//visibility:public"],
    deps = ["@com_github_grpc_grpc//:grpc++"]
)