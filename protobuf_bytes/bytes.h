// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PROTOBUF_BYTES_BYTES_H_
#define PROTOBUF_BYTES_BYTES_H_

#include <sstream>
#include <string>
#include <type_traits>

#include "protobuf_bytes/bytes.pb.h"
#include "protobuf_bytes/bytes_constants.h"
#include "protobuf_bytes/bytes_internal.h"
#include "protobuf_bytes/export.h"
#include "protobuf_bytes/random_access_iterator.h"

namespace protobuf_bytes {

template <typename T>
struct BytesMessageTraits;

template <>
struct BytesMessageTraits<uint8_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_8U;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_8U_C1;
};

template <>
struct BytesMessageTraits<int8_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_8S;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_8S_C1;
};

template <>
struct BytesMessageTraits<uint16_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_16U;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_16U_C1;
};

template <>
struct BytesMessageTraits<int16_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_16S;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_16S_C1;
};

template <>
struct BytesMessageTraits<uint32_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_32U;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_32U_C1;
};

template <>
struct BytesMessageTraits<int32_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_32S;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_32S_C1;
};

template <>
struct BytesMessageTraits<uint64_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_64U;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_64U_C1;
};

template <>
struct BytesMessageTraits<int64_t> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_64S;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_64S_C1;
};

template <>
struct BytesMessageTraits<float> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_32F;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_32F_C1;
};

template <>
struct BytesMessageTraits<double> {
  static constexpr BytesMessage::ElementType element_type =
      BytesMessage::ELEMENT_TYPE_64F;
  static constexpr BytesMessage::ChannelType channel_type =
      BytesMessage::CHANNEL_TYPE_C1;
  static constexpr uint32_t bytes_type = BYTES_TYPE_64F_C1;
};

// Bytes is a container which has std::string inside, but is able to
// be used like std::vector. It is used as a c++ implementation against
// BytesMessage type of protobuf. If you want to use protobuf bytes type, but
// in c++ it can be float or int, you can use this class like below.
//
// Bytes bytes;
// Bytes::View<int> view = bytes.AsView<int>();
// or
// Bytes::View<float> view = bytes.AsView<float>();
class PROTOBUF_BYTES_EXPORT Bytes {
 public:
  template <typename T>
  class ConstView {
   public:
    using const_iterator = RandomAccessConstIterator<T>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit ConstView(const Bytes& bytes) : bytes_(bytes) {}

    const_iterator begin() const noexcept {
      return make_iterator(const_cast<T*>(data()));
    }

    const_iterator cbegin() const noexcept { return begin(); }

    const_iterator end() const noexcept {
      return make_iterator(const_cast<T*>(data() + size()));
    }

    const_iterator cend() const noexcept { return end(); }

    const_reverse_iterator rbegin() const noexcept {
      return const_reverse_iterator(cend());
    }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    const_reverse_iterator rend() const noexcept {
      return const_reverse_iterator(cbegin());
    }

    const_reverse_iterator crend() const noexcept { return rend(); }

    const T* data() const {
      return reinterpret_cast<const T*>(bytes_.data_.data());
    }

    const T& operator[](size_t idx) const { return *(cbegin() + idx); }

    const T& at(size_t idx) const {
      range_check(idx);
      return (*this)[idx];
    }

    const T& front() const { return *cbegin(); }
    const T& back() const { return *(cend() - 1); }

    size_t size() const noexcept { return bytes_.size() / sizeof(T); }

    bool empty() const noexcept { return bytes_.size() == 0; }

   private:
    void range_check(size_t idx) const {
      if (idx >= size()) {
        std::stringstream ss;
        ss << "Bytes::range_check: (" << idx << " " << size() << ")";
        throw std::out_of_range(ss.str());
      }
    }

    const_iterator make_iterator(T* ptr) const {
      return const_iterator(const_cast<T*>(data()), ptr,
                            const_cast<T*>(data() + size()));
    }

    const Bytes& bytes_;
  };

  template <typename T>
  class View {
   public:
    using iterator = RandomAccessIterator<T>;
    using const_iterator = RandomAccessConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit View(Bytes& bytes) : bytes_(bytes) {}

    void push_back(const T& value) {
      T* ptr = AddOneElementToBack();
      new (ptr) T(value);
    }

    void push_back(T&& value) {
      T* ptr = AddOneElementToBack();
      new (ptr) T(std::move(value));
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
      T* ptr = AddOneElementToBack();
      new (ptr) T(std::forward<Args>(args)...);
    }

    void pop_back() { bytes_.resize(bytes_.size() - sizeof(T)); }

    iterator insert(const_iterator position, const T& value) {
      T* ptr = AddElements(position, 1);
      new (ptr) T(value);
      return make_iterator(ptr);
    }

    iterator insert(const_iterator position, T&& value) {
      T* ptr = AddElements(position, 1);
      new (ptr) T(std::move(value));
      return make_iterator(ptr);
    }

    void insert(const_iterator position, size_t n, const T& value) {
      T* ptr = AddElements(position, n);
      for (size_t i = 0; i < n; ++i) {
        new (ptr + i) T(value);
      }
    }

    iterator erase(const_iterator position) {
      ptrdiff_t diff = position - begin();
      bytes_.data_.erase(diff * sizeof(T), sizeof(T));
      return begin() + diff;
    }

    iterator erase(const_iterator first, const_iterator last) {
      ptrdiff_t diff = first - begin();
      bytes_.data_.erase(diff * sizeof(T), (last - first) * sizeof(T));
      return begin() + diff;
    }

    iterator begin() const noexcept {
      return make_iterator(const_cast<T*>(data()));
    }
    const_iterator cbegin() const noexcept { return begin(); }

    iterator end() const noexcept {
      return make_iterator(const_cast<T*>(data() + size()));
    }
    const_iterator cend() const noexcept { return end(); }

    reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return rend(); }

    const T* data() const {
      return reinterpret_cast<const T*>(bytes_.data_.data());
    }
    T* data() {
      return reinterpret_cast<T*>(const_cast<char*>(bytes_.data_.data()));
    }

    T& operator[](size_t idx) { return *(begin() + idx); }

    const T& operator[](size_t idx) const { return *(cbegin() + idx); }

    T& at(size_t idx) {
      range_check(idx);
      return (*this)[idx];
    }

    const T& at(size_t idx) const {
      range_check(idx);
      return (*this)[idx];
    }

    T& front() { return *begin(); }
    const T& front() const { return *cbegin(); }
    T& back() { return *(end() - 1); }
    const T& back() const { return *(cend() - 1); }

    size_t size() const noexcept { return bytes_.size() / sizeof(T); }

    bool empty() const noexcept { return bytes_.size() == 0; }

    void reserve(size_t n) { bytes_.reserve(n * sizeof(T)); }

    void resize(size_t n) { bytes_.resize(n * sizeof(T)); }

    void shrink_to_fit() { bytes_.shrink_to_fit(); }

    void clear() { bytes_.clear(); }

   private:
    T* AddOneElementToBack() {
      size_t size = bytes_.size();
      bytes_.data_.resize(size + sizeof(T));
      return reinterpret_cast<T*>(
          const_cast<char*>(bytes_.data_.data() + size));
    }

    T* AddElements(const_iterator position, size_t n) {
      ptrdiff_t diff = position - begin();
      bytes_.data_.insert(diff * sizeof(T), sizeof(T) * n, 0);
      return reinterpret_cast<T*>(const_cast<char*>(bytes_.data_.data())) +
             diff;
    }

    iterator make_iterator(T* ptr) const {
      return iterator(const_cast<T*>(data()), ptr,
                      const_cast<T*>(data() + size()));
    }

    void range_check(size_t idx) const {
      if (idx >= size()) {
        std::stringstream ss;
        ss << "Bytes::range_check: (" << idx << " " << size() << ")";
        throw std::out_of_range(ss.str());
      }
    }

    Bytes& bytes_;
  };

  Bytes();
  template <typename T>
  Bytes(const T* s, size_t n, uint32_t type = BytesMessageTraits<T>::bytes_type)
      : data_(reinterpret_cast<const char*>(s), n), type_(type) {}
  Bytes(const std::string& data, uint32_t type = 0);
  Bytes(std::string&& data, uint32_t type = 0) noexcept;
  Bytes(const Bytes& other);
  Bytes(Bytes&& other) noexcept;
  ~Bytes();

  Bytes& operator=(const Bytes& other);
  Bytes& operator=(Bytes&& other);

  template <typename T, std::enable_if_t<std::is_pointer<T>::value>* = nullptr>
  T cast() const noexcept {
    return reinterpret_cast<T>(data_.data());
  }

  template <typename T, std::enable_if_t<std::is_pointer<T>::value>* = nullptr>
  T cast() noexcept {
    return reinterpret_cast<T>(const_cast<char*>(data_.data()));
  }

  size_t size() const noexcept;

  bool empty() const noexcept;

  void reserve(size_t n);

  void resize(size_t n);

  void shrink_to_fit();

  void clear();

  void swap(Bytes& other);

  const std::string& data() const& noexcept;
  std::string&& data() && noexcept;

  uint32_t type() const;
  void set_type(uint32_t type);

  void GetElementaAndChannelType(BytesMessage::ElementType* element_type,
                                 BytesMessage::ChannelType* channel_type);

  template <typename T>
  ConstView<T> AsConstView() const noexcept {
    return ConstView<T>(*this);
  }

  template <typename T>
  View<T> AsView() noexcept {
    return View<T>(*this);
  }

  BytesMessage ToBytesMessage(bool copy = true);
  bool FromBytesMessage(const BytesMessage& message);
  bool FromBytesMessage(BytesMessage&& message);

 private:
  template <typename T>
  friend class View;
  template <typename T>
  friend class ConstView;

  std::string data_;
  uint32_t type_;
};

}  // namespace protobuf_bytes

#endif  // PROTOBUF_BYTES_BYTES_H_