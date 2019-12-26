def protobuf_bytes_copts():
    return select({
        "@protobuf_bytes//:windows": [
            "/std:c++14",
        ],
        "//conditions:default": [
            "-std=c++14",
        ],
    })