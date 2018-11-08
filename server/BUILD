load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")

# General Proto Library deps

proto_library(
    name = "protos",
    srcs = ["protos/entities.proto"],
    deps = ["//common:protos"],
    visibility = ["//visibility:public"]
)

# CPP GRPC Deps and binaries (Server & Client)

cpp_grpc_library(
    name = "protos_cpp",
    deps = [":protos"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "server",
    srcs = ["src/server.cc"] + glob(["src/stubs/*.impl.h"]),
    deps = [":protos_cpp", "//database:protos_cpp", "//common:logging"]
)

