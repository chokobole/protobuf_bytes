# Protobuf Bytes

This is a `c++` class correspondent to `protobuf` bytes, which is able to use `move` semantics!

## Examples

```c++
#include <iostream>

#include "protobuf_bytes/bytes.h"

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}
};

int main() {
  protobuf_bytes::Bytes bytes;
  protobuf_bytes::Bytes::View<Point> view = bytes.AsView<Point>();
  view.emplace_back(1, 2);
  view.emplace_back(3, 4);
  protobuf_bytes::BytesMessage message = bytes.ToBytesMessage(false);  // It's using move!
  std::cout << message.DebugString() << std::endl;
}
```
