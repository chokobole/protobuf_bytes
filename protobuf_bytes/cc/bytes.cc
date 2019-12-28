// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "protobuf_bytes/cc/bytes.h"

namespace protobuf_bytes {

Bytes::Bytes() : type_(0) { MarkNativeEndian(); }

Bytes::Bytes(const std::string& data, uint32_t type)
    : type_(type), data_(data) {
  MarkNativeEndian();
}

Bytes::Bytes(const std::string& data, bool bigendian, uint32_t type)
    : type_(type), bigendian_(bigendian), data_(data) {}

Bytes::Bytes(std::string&& data, uint32_t type) noexcept
    : type_(type), data_(std::move(data)) {
  MarkNativeEndian();
}

Bytes::Bytes(std::string&& data, bool bigendian, uint32_t type) noexcept
    : type_(type), bigendian_(bigendian), data_(std::move(data)) {}

Bytes::Bytes(const Bytes& other) = default;

Bytes::Bytes(Bytes&& other) noexcept
    : type_(other.type_),
      bigendian_(other.bigendian_),
      data_(std::move(other.data_)) {}

Bytes::~Bytes() = default;

Bytes& Bytes::operator=(const Bytes& other) = default;
Bytes& Bytes::operator=(Bytes&& other) noexcept {
  type_ = other.type_;
  bigendian_ = other.bigendian_;
  data_ = std::move(other.data_);
  return *this;
}

size_t Bytes::size() const noexcept { return data_.size(); }

bool Bytes::empty() const noexcept { return data_.size() == 0; }

void Bytes::reserve(size_t n) { data_.reserve(n); }

void Bytes::resize(size_t n) { data_.resize(n); }

void Bytes::shrink_to_fit() { data_.shrink_to_fit(); }

void Bytes::clear() { data_.clear(); }

void Bytes::swap(Bytes& other) { data_.swap(other.data_); }

const std::string& Bytes::data() const& noexcept { return data_; }
std::string&& Bytes::data() && noexcept { return std::move(data_); }

uint32_t Bytes::type() const { return type_; }
void Bytes::set_type(uint32_t type) { type_ = type; }

bool Bytes::bigendian() const { return bigendian_; }

void Bytes::MarkNativeEndian() {
  union {
    uint8_t c[4];
    uint32_t i;
  } u;

  u.i = 0x01020304;
  bigendian_ = u.c[0] == 0x01;
}

void Bytes::GetElementaAndChannelType(BytesMessage::ElementType* element_type,
                                      BytesMessage::ChannelType* channel_type) {
  internal::GetElementaAndChannelType(type_, element_type, channel_type);
}

BytesMessage Bytes::ToBytesMessage(bool copy) {
  BytesMessage message;
  message.set_type(type_);
  message.set_bigendian(bigendian_);
  if (copy)
    message.set_data(data_);
  else
    message.set_data(std::move(data_));
  return message;
}

bool Bytes::FromBytesMessage(const BytesMessage& message) {
  *this = Bytes(message.data(), message.bigendian(), message.type());
  return true;
}

bool Bytes::FromBytesMessage(BytesMessage&& message) {
  std::unique_ptr<std::string> data(message.release_data());
  *this = Bytes(std::move(*data), message.bigendian(), message.type());
  return true;
}

}  // namespace protobuf_bytes