load("//bazel:protobuf_bytes_cc.bzl", "protobuf_bytes_copts")

cc_binary(
    name = "pointcloud",
    srcs = ["pointcloud.cc"],
    copts = protobuf_bytes_copts(),
    deps = ["//:protobuf_bytes"],
)