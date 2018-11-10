load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")

# General Proto Library deps

proto_library(
    name = "protos",
    srcs = glob(["protos/*.proto"]),
    deps = ["//common:protos"]
)

# CPP GRPC Deps and binaries (Server & Client)

cc_library(
    name = "core",
    srcs = glob(["src/core/*.cc"]),
    hdrs = glob(["src/core/*.h"]),
    deps = [":protos_cpp", "//common:utils"]
)

cpp_grpc_library(
    name = "protos_cpp",
    deps = [":protos"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "server",
    srcs = ["src/server.cc"] + glob(["src/stubs/*.impl.h", "src/stubs/*.impl.cc"]),
    deps = [":protos_cpp", ":core", "//common:utils"],
)

cc_binary(
    name = "tester",
    srcs = ["src/test.cc"],
    deps = [":protos_cpp", "//common:utils"]
)