load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")
load("@build_stack_rules_proto//python:python_grpc_library.bzl", "python_grpc_library")

proto_library(
    name = "greet_proto",
    srcs = [
        "proto/greet.proto",
    ],
    visibility = ["//visibility:public"]
)

cpp_grpc_library(
    name = "greet_cpp",
    deps = [":greet_proto"]
)


python_grpc_library(
    name = "greet_python",
    deps = [":greet_proto"]
)

cc_binary(
    name = "greet_client",
    srcs = ["src/client.cc"],
    deps = [":greet_cpp"]
)

cc_binary(
    name = "greet_server",
    srcs = ["src/server.cc"],
    deps = [":greet_cpp"]
)

py_binary(
    name = "py_greet_client",
    srcs = ["python/py_greet_client.py"],
    deps = [":greet_python"]
)