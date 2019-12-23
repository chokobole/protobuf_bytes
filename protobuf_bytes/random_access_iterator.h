// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PROTOBUF_BYTES_RANDOM_ACCESS_ITERATOR_H_
#define PROTOBUF_BYTES_RANDOM_ACCESS_ITERATOR_H_

#include <iterator>

namespace protobuf_bytes {

template <typename T>
class RandomAccessConstIterator;

template <typename T>
class RandomAccessIterator {
 public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::iterator_traits<T*>::value_type;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::random_access_iterator_tag;

  friend class RandomAccessConstIterator<T>;

  RandomAccessIterator() = default;
  RandomAccessIterator(T* start, const T* end)
      : RandomAccessIterator(start, start, end) {}
  RandomAccessIterator(T* start, T* current, const T* end)
      : start_(start), current_(current), end_(end) {}
  RandomAccessIterator(const RandomAccessIterator& other) = default;
  ~RandomAccessIterator() = default;

  RandomAccessIterator& operator=(const RandomAccessIterator& other) = default;

  bool operator==(const RandomAccessIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const RandomAccessIterator& other) const {
    return current_ != other.current_;
  }

  bool operator<(const RandomAccessIterator& other) const {
    return current_ < other.current_;
  }

  bool operator<=(const RandomAccessIterator& other) const {
    return current_ <= other.current_;
  }

  RandomAccessIterator& operator++() {
    ++current_;
    return *this;
  }

  RandomAccessIterator operator++(int) {
    RandomAccessIterator old = *this;
    ++*this;
    return old;
  }

  RandomAccessIterator& operator--() {
    --current_;
    return *this;
  }

  RandomAccessIterator& operator--(int) {
    RandomAccessIterator old = *this;
    --*this;
    return old;
  }

  RandomAccessIterator& operator+=(difference_type rhs) {
    current_ += rhs;
    return *this;
  }

  RandomAccessIterator operator+(difference_type rhs) const {
    RandomAccessIterator it = *this;
    it += rhs;
    return it;
  }

  RandomAccessIterator& operator-=(difference_type rhs) {
    current_ -= rhs;
    return *this;
  }

  RandomAccessIterator operator-(difference_type rhs) const {
    RandomAccessIterator it = *this;
    it -= rhs;
    return it;
  }

  friend difference_type operator-(const RandomAccessIterator& lhs,
                                   const RandomAccessIterator& rhs) {
    return lhs.current_ - rhs.current_;
  }

  reference operator*() const { return *current_; }

  pointer operator->() const { return current_; }

 private:
  const T* start_ = nullptr;
  T* current_ = nullptr;
  const T* end_ = nullptr;
};

template <typename T>
class RandomAccessConstIterator {
 public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::iterator_traits<T*>::value_type;
  using pointer = const T*;
  using reference = const T&;
  using iterator_category = std::random_access_iterator_tag;

  RandomAccessConstIterator() = default;
  RandomAccessConstIterator(T* start, const T* end)
      : RandomAccessConstIterator(start, start, end) {}
  RandomAccessConstIterator(T* start, T* current, const T* end)
      : start_(start), current_(current), end_(end) {}
  RandomAccessConstIterator(const RandomAccessConstIterator& other) = default;
  RandomAccessConstIterator(const RandomAccessIterator<T>& other)
      : start_(other.start_), current_(other.current_), end_(other.end_) {}
  ~RandomAccessConstIterator() = default;

  RandomAccessConstIterator& operator=(const RandomAccessConstIterator& other) =
      default;

  RandomAccessConstIterator& operator=(RandomAccessConstIterator& other) =
      default;

  bool operator==(const RandomAccessConstIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const RandomAccessConstIterator& other) const {
    return current_ != other.current_;
  }

  bool operator<(const RandomAccessConstIterator& other) const {
    return current_ < other.current_;
  }

  bool operator<=(const RandomAccessConstIterator& other) const {
    return current_ <= other.current_;
  }

  RandomAccessConstIterator& operator++() {
    ++current_;
    return *this;
  }

  RandomAccessConstIterator operator++(int) {
    RandomAccessConstIterator old = *this;
    ++*this;
    return old;
  }

  RandomAccessConstIterator& operator--() {
    --current_;
    return *this;
  }

  RandomAccessConstIterator& operator--(int) {
    RandomAccessConstIterator old = *this;
    --*this;
    return old;
  }

  RandomAccessConstIterator& operator+=(difference_type rhs) {
    current_ += rhs;
    return *this;
  }

  RandomAccessConstIterator operator+(difference_type rhs) const {
    RandomAccessConstIterator it = *this;
    it += rhs;
    return it;
  }

  RandomAccessConstIterator& operator-=(difference_type rhs) {
    current_ -= rhs;
    return *this;
  }

  RandomAccessConstIterator operator-(difference_type rhs) const {
    RandomAccessConstIterator it = *this;
    it -= rhs;
    return it;
  }

  friend difference_type operator-(const RandomAccessConstIterator& lhs,
                                   const RandomAccessConstIterator& rhs) {
    return lhs.current_ - rhs.current_;
  }

  reference operator*() const { return *current_; }

  pointer operator->() const { return current_; }

 private:
  const T* start_ = nullptr;
  const T* current_ = nullptr;
  const T* end_ = nullptr;
};

}  // namespace protobuf_bytes

#endif  // PROTOBUF_BYTES_RANDOM_ACCESS_ITERATOR_H_