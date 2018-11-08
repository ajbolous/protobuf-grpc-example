load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")
load("@build_stack_rules_proto//python:python_grpc_library.bzl", "python_grpc_library")


cc_binary(
    name = "client",
    srcs = ["src/client.cc"],
    deps = ["//server:protos_cpp", "//common:utils"]
)

# Python GRPC deps and client binary

python_grpc_library(
    name = "protos_python",
    deps = ["//server:protos"]
)

py_binary(
    name = "py_client",
    srcs = ["python/py_client.py"],
    deps = [":protos_python"]
)

