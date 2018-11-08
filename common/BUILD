# General Proto Library deps
proto_library(
    name = "protos",
    srcs = ["protos/entity.proto"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "logging",
    srcs = glob(["logging/*.cc"]),
    hdrs = glob(["logging/*.h"]),
    visibility = ["//visibility:public"]
)