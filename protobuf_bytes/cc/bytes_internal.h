// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PROTOBUF_BYTES_CC_BYTES_INTERNAL_H_
#define PROTOBUF_BYTES_CC_BYTES_INTERNAL_H_

#include "protobuf_bytes/bytes.pb.h"

namespace protobuf_bytes {
namespace internal {

// Decomposes the |type| into |element_type| and |channel_type|.
constexpr void GetElementaAndChannelType(
    uint32_t type, BytesMessage::ElementType* element_type,
    BytesMessage::ChannelType* channel_type) {
  *element_type =
      static_cast<BytesMessage::ElementType>(static_cast<uint16_t>(type >> 16));
  *channel_type =
      static_cast<BytesMessage::ChannelType>(static_cast<uint16_t>(type));
}

// Composes |element_type| and |channel_type|.
constexpr uint32_t MakeBytesType(BytesMessage::ElementType element_type,
                                 BytesMessage::ChannelType channel_type) {
  return (static_cast<uint32_t>(element_type) << 16) |
         static_cast<uint32_t>(channel_type);
}

// Returns the size of one element. If |element_type| is not one of
// BytesMessage::ElementType, then returns -1.
constexpr size_t GetElement1Size(BytesMessage::ElementType element_type) {
  switch (element_type) {
    case BytesMessage::ELEMENT_TYPE_8U:
    case BytesMessage::ELEMENT_TYPE_8S: {
      return 1;
    }
    case BytesMessage::ELEMENT_TYPE_16U:
    case BytesMessage::ELEMENT_TYPE_16S: {
      return 2;
    }
    case BytesMessage::ELEMENT_TYPE_32U:
    case BytesMessage::ELEMENT_TYPE_32S:
    case BytesMessage::ELEMENT_TYPE_32F: {
      return 4;
    }
    case BytesMessage::ELEMENT_TYPE_64U:
    case BytesMessage::ELEMENT_TYPE_64S:
    case BytesMessage::ELEMENT_TYPE_64F: {
      return 8;
    }
    default:
      return -1;
  }
}

// Returns the number of channel. If |channel_type| is not one of
// BytesChannelType, then returns -1.
constexpr size_t GetChannelSize(BytesMessage::ChannelType channel_type) {
  switch (channel_type) {
    case BytesMessage::CHANNEL_TYPE_C1:
      return 1;
    case BytesMessage::CHANNEL_TYPE_C2:
      return 2;
    case BytesMessage::CHANNEL_TYPE_C3:
      return 3;
    case BytesMessage::CHANNEL_TYPE_C4:
      return 4;
    default:
      return -1;
  }
}

}  // namespace internal
}  // namespace protobuf_bytes

#endif  // PROTOBUF_BYTES_CC_BYTES_INTERNAL_H_