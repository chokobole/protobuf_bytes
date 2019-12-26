// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "protobuf_bytes/cc/bytes.h"

namespace protobuf_bytes {

Bytes::Bytes() : type_(0) {}

Bytes::Bytes(const std::string& data, uint32_t type)
    : type_(type), data_(data) {}

Bytes::Bytes(std::string&& data, uint32_t type) noexcept
    : type_(type), data_(std::move(data)) {}

Bytes::Bytes(const Bytes& other) = default;

Bytes::Bytes(Bytes&& other) noexcept
    : type_(other.type_), data_(std::move(other.data_)) {}

Bytes::~Bytes() = default;

Bytes& Bytes::operator=(const Bytes& other) = default;
Bytes& Bytes::operator=(Bytes&& other) = default;

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

void Bytes::GetElementaAndChannelType(BytesMessage::ElementType* element_type,
                                      BytesMessage::ChannelType* channel_type) {
  internal::GetElementaAndChannelType(type_, element_type, channel_type);
}

BytesMessage Bytes::ToBytesMessage(bool copy) {
  BytesMessage message;
  message.set_type(type_);
  if (copy)
    message.set_data(data_);
  else
    message.set_data(std::move(data_));
  return message;
}

bool Bytes::FromBytesMessage(const BytesMessage& message) {
  *this = Bytes(message.data(), message.type());
  return true;
}

bool Bytes::FromBytesMessage(BytesMessage&& message) {
  std::unique_ptr<std::string> data(message.release_data());
  *this = Bytes(std::move(*data), message.type());
  return true;
}

}  // namespace protobuf_bytes