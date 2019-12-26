// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <sstream>

#include "protobuf_bytes/cc/bytes.h"

using namespace protobuf_bytes;

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}

  std::string ToString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
  }
};

std::ostream& operator<<(std::ostream& os, const Point& point) {
  return os << point.ToString();
}

int main() {
  Bytes bytes;
  Bytes::View<Point> view = bytes.AsView<Point>();
  view.emplace_back(1, 2);
  view.emplace_back(3, 4);
  BytesMessage message = bytes.ToBytesMessage(false);
  std::cout << message.DebugString() << std::endl;
  Bytes bytes2;
  bytes2.FromBytesMessage(std::move(message));
  Bytes::ConstView<Point> view2 = bytes2.AsConstView<Point>();
  for (auto& p: view2) {
    std::cout << p << std::endl;
  }

  return 0;
}