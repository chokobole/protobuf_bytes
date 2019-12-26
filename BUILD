load("@rules_proto//proto:defs.bzl", "proto_library")
load("//bazel:protobuf_bytes_cc.bzl", "protobuf_bytes_copts")

exports_files(["LICENSE"])

config_setting(
    name = "windows",
    constraint_values = ["@bazel_tools//platforms:windows"],
    visibility = ["//visibility:public"],
)

proto_library(
    name = "bytes_proto",
    visibility = ["//visibility:public"],
    srcs = ["protobuf_bytes/bytes.proto"],
)

cc_proto_library(
    name = "bytes_cc_proto",
    visibility = ["//visibility:public"],
    deps = [":bytes_proto"],
)

cc_library(
    name = "protobuf_bytes",
    hdrs = [
        "protobuf_bytes/cc/bytes_constants.h",
        "protobuf_bytes/cc/bytes_internal.h",
        "protobuf_bytes/cc/bytes.h",
        "protobuf_bytes/cc/export.h",
        "protobuf_bytes/cc/random_access_iterator.h",
    ],
    srcs = [
        "protobuf_bytes/cc/bytes.cc",
    ],
    copts = protobuf_bytes_copts(),
    visibility = ["//visibility:public"],
    deps = [
        ":bytes_cc_proto",
    ],
)

cc_test(
    name = "protobuf_bytes_unittest",
    srcs = ["protobuf_bytes/cc/bytes_unittest.cc"],
    copts = protobuf_bytes_copts(),
    deps = [
        ":protobuf_bytes",
        "@com_google_googletest//:gtest_main",
    ],
)