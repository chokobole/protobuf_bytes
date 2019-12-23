// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "protobuf_bytes/bytes.h"

#include "gtest/gtest.h"

namespace protobuf_bytes {

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

template <typename T, size_t N>
constexpr size_t size(const T (&array)[N]) noexcept {
  return N;
}

TEST(BytesTest, PushAndPopTest) {
  Bytes bytes;
  Bytes::View<Point> view = bytes.AsView<Point>();
  Point p(1, 2);
  Point p2(3, 4);
  view.push_back(p);
  view.push_back(p2);
  EXPECT_EQ(view.size(), 2);

  Point& p3 = view[0];
  EXPECT_EQ(p, p3);
  EXPECT_EQ(p, view.front());
  Point& p4 = view[1];
  EXPECT_EQ(p2, p4);
  EXPECT_EQ(p2, view.back());

  p3.x = 5;
  EXPECT_EQ(p3.x, 5);
  EXPECT_EQ(view[0].x, 5);

  view.pop_back();
  EXPECT_EQ(1, view.size());
  EXPECT_EQ(view.front(), view.back());
}

template <typename Iterator>
void ExpectIteratorEq(Iterator begin, Iterator end, int from, int to) {
  int n = from;
  bool incremental = to > from;
  for (auto it = begin; it != end; it++) {
    if (incremental) {
      EXPECT_EQ(*it, n++);
    } else {
      EXPECT_EQ(*it, n--);
    }
  }
  EXPECT_EQ(n, to);
}

TEST(BytesTest, IteratorTest) {
  Bytes bytes;
  Bytes::View<int> view = bytes.AsView<int>();
  for (int i = 0; i < 10; ++i) {
    view.push_back(i);
  }

  ExpectIteratorEq(view.begin(), view.end(), 0, 10);
  ExpectIteratorEq(view.cbegin(), view.cend(), 0, 10);
  ExpectIteratorEq(view.rbegin(), view.rend(), 9, -1);
  ExpectIteratorEq(view.crbegin(), view.crend(), 9, -1);

  Bytes::ConstView<int> cview = bytes.AsConstView<int>();
  ExpectIteratorEq(cview.begin(), cview.end(), 0, 10);
  ExpectIteratorEq(cview.cbegin(), cview.cend(), 0, 10);
  ExpectIteratorEq(cview.rbegin(), cview.rend(), 9, -1);
  ExpectIteratorEq(cview.crbegin(), cview.crend(), 9, -1);
}

TEST(BytesTest, InsertTest) {
  Bytes bytes;
  Bytes::View<int> view = bytes.AsView<int>();
  auto it = view.insert(view.begin(), 0);
  it = view.insert(it, 1);
  it = view.insert(view.begin() + 1, 2);
  it = view.insert(it, 3);
  view.insert(it, 3, 4);
  view.insert(view.end(), 5);
  view.push_back(6);

  int answer[] = {1, 4, 4, 4, 3, 2, 0, 5, 6};
  for (size_t i = 0; i < size(answer); ++i) {
    EXPECT_EQ(answer[i], view[i]);
  }
}

TEST(BytesTest, EraseTest) {
  Bytes bytes;
  Bytes::View<int> view = bytes.AsView<int>();
  for (int i = 0; i < 10; ++i) {
    view.push_back(i);
  }

  auto it = view.erase(view.begin() + 5);
  EXPECT_EQ(6, *it);
  EXPECT_EQ(9, view.size());

  it = view.erase(view.begin() + 5, view.begin() + 7);
  EXPECT_EQ(8, *it);
  EXPECT_EQ(7, view.size());
}

}  // namespace protobuf_bytes