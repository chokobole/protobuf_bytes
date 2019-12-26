# Protobuf Bytes

`protobuf` bytes is represented as a `std::string` in the `c++` world. There is a dilemma "Should I give up `move` semantics and use `std::vector<T>`?". Now don't worry! This repository gives you a new `c++` class correspondent to `protobuf` bytes, which is able to use `move` semantics and mimic `std::vector<T>` apis!

## Contents
- [Protobuf Bytes](#protobuf-bytes)
  - [Contents](#contents)
  - [How to use](#how-to-use)
    - [bazel](#bazel)
    - [nodeJS](#nodejs)
  - [Examples](#examples)
  - [Usages](#usages)
    - [Type](#type)
    - [View](#view)
    - [Serialization / Deserialization](#serialization--deserialization)
    - [Cast to pointer](#cast-to-pointer)
    - [std::string methods](#stdstring-methods)

## How to use

### bazel

To use `protobuf_bytes`, add the followings to your `WORKSPACE` file.

```python
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "protobuf_bytes",
    sha256 = "<sha256>",
    strip_prefix = "protobuf_bytes-<commit>",
    urls = [
        "https://github.com/chokobole/protobuf_bytes/archive/<commit>.tar.gz",
    ],
)

load("@protobuf_bytes//bazel:protobuf_bytes_deps.bzl", "protobuf_bytes_deps")

protobuf_bytes_deps()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()
```

Import the `bytes.proto` and use like below.

```protobuf
import "protobuf_bytes/bytes.proto";

message FooMessage {
  protobuf_bytes.BytesMessage bytes = 1;
}
```

Then, in your `BUILD` files, import and use the rules.

```python
load("@protobuf_bytes//bazel:protobuf_bytes_cc.bzl", "protobuf_bytes_copts")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "[name]_proto",
    srcs = ["[name].proto"],
    deps = ["@protobuf_bytes//:bytes_proto"],
)

cc_proto_library(
    name = "[name]_cc_proto",
    deps = [":[name]_proto"],
)

cc_library(
    name = "[name]",
    copts = protobuf_bytes_copts(),
    deps = [
      ":[name]_cc_proto",
      "@protobuf_bytes",
    ]
)
```

### nodeJS

please read [protobuf_bytes/js/README.md](protobuf_bytes/js/README.md).

## Examples

You can find the full code [examples/pointcloud.cc](examples/pointcloud.cc)!

```c++
#include <iostream>

#include "protobuf_bytes/cc/bytes.h"

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}
};

int main() {
  protobuf_bytes::Bytes bytes;
  bytes.set_type(BYTES_TYPE_8U_C3);
  protobuf_bytes::Bytes::View<Point> view = bytes.AsView<Point>();
  view.emplace_back(1, 2);
  view.emplace_back(3, 4);
  protobuf_bytes::BytesMessage message = bytes.ToBytesMessage(false);  // It's using move!
  std::cout << message.DebugString() << std::endl;
}
```

## Usages

### Type

`BytesMessages` has members `type` anad `data`.

```protobuf
message BytesMessage {
  enum ElementType {
    ELEMENT_TYPE_CUSTOM = 0;
    ELEMENT_TYPE_8U = 1;
    ELEMENT_TYPE_8S = 2;
    ELEMENT_TYPE_16U = 3;
    ELEMENT_TYPE_16S = 4;
    ELEMENT_TYPE_32U = 5;
    ELEMENT_TYPE_32S = 6;
    ELEMENT_TYPE_64U = 7;
    ELEMENT_TYPE_64S = 8;
    ELEMENT_TYPE_32F = 9;
    ELEMENT_TYPE_64F = 10;
  };
  enum ChannelType {
    CHANNEL_TYPE_CUSTOM = 0;
    CHANNEL_TYPE_C1 = 1;
    CHANNEL_TYPE_C2 = 2;
    CHANNEL_TYPE_C3 = 3;
    CHANNEL_TYPE_C4 = 4;
  };
  uint32 type = 1;
  bytes data = 2;
}
```

`type` is the combination of `ElementType` and `ChannelType` like below.

```c++
// bytes_internal.h
constexpr uint32_t MakeBytesType(BytesMessage::ElementType element_type,
                                 BytesMessage::ChannelType channel_type) {
  return (static_cast<uint32_t>(element_type) << 16) |
         static_cast<uint32_t>(channel_type);
}
```

There are predefined `type`s.

```c++
BYTES_TYPE_8U_C1 // ELEMENT_TYPE_8U + CHANNEL_TYPE_C1
BYTES_TYPE_8U_C2 // ELEMENT_TYPE_8U + CHANNEL_TYPE_C2
BYTES_TYPE_8U_C3 // ELEMENT_TYPE_8U + CHANNEL_TYPE_C3
BYTES_TYPE_8U_C4 // ELEMENT_TYPE_8U + CHANNEL_TYPE_C4
...
BYTES_TYPE_64F_C1 // ELEMENT_TYPE_64F + CHANNEL_TYPE_C1
BYTES_TYPE_64F_C2 // ELEMENT_TYPE_64F + CHANNEL_TYPE_C2
BYTES_TYPE_64F_C3 // ELEMENT_TYPE_64F + CHANNEL_TYPE_C3
BYTES_TYPE_64F_C4 // ELEMENT_TYPE_64F + CHANNEL_TYPE_C4
```

### View

If you want to use mimicking `std::vector<T>`, you should call `Bytes::ConstView<T> Bytes::AsConstView<T>()` or `Bytes::View<T> Bytes::AsView<T>()`. One is readonly version and the other is writable version.

```c++
protobuf_bytes::Bytes bytes;
bytes.AsView<Point>();  // can modify
bytes.AsConstView<Point>();  // can't modify
```

### Serialization / Deserialization

To serialize, you have to call `BytesMessage Bytes::ToBytesMessage(bool copy = true)` method.

```c++
protobuf_bytes::Bytes bytes;
bytes.ToBytesMessage();  // copy
bytes.ToBytesMessage(false);  // move
```

To deserialize, there are overloaded 2 methods `bool Bytes::FromBytesMessage(const BytesMessage& message)` and `bool Bytes::FromBytesMessage(BytesMessage&& message)`. Currenlty it just returns `true`.

```c++
protobuf_bytes::Bytes bytes;
protobuf_bytes::BytesMessage message;
bytes.FromBytesMessage(message);  // copy
bytes.FromBytesMessage(std::move(message));  // move
```

### Cast to pointer

To cast `T*` or `const T*`, you have to call template method `T cast()`.

```c++
protobuf_bytes::Bytes bytes;
Point* ptr = bytes.cast<Point*>();
const Point* cptr = bytes.cast<const Point*>();
```

### std::string methods

There are opened `std::string` methods for the member `data` of `Bytes` class.

```c++
size_t size() const noexcept;

bool empty() const noexcept;

void reserve(size_t n);

void resize(size_t n);

void shrink_to_fit();

void clear();

void swap(Bytes& other);
```