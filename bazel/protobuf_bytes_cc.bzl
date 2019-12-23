def protobuf_bytes_copts():
    return select({
        "//:windows": [
            "/std:c++14",
        ],
        "//conditions:default": [
            "-std=c++14",
        ],
    })