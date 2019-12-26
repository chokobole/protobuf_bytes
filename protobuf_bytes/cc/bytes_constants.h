// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PROTOBUF_BYTES_CC_BYTES_CONSTANTS_H_
#define PROTOBUF_BYTES_CC_BYTES_CONSTANTS_H_

#include "protobuf_bytes/bytes.pb.h"
#include "protobuf_bytes/cc/bytes_internal.h"

namespace protobuf_bytes {

#define PROTOBUF_MAKE_BYTES_TYPE(ELEMENT_NAME, ELEMENT_TYPE, CHANNEL_NAME, \
                                 CHANNEL_TYPE)                             \
  constexpr uint32_t BYTES_TYPE_##ELEMENT_NAME##_##CHANNEL_NAME =          \
      ::protobuf_bytes::internal::MakeBytesType(ELEMENT_TYPE, CHANNEL_TYPE)

#define PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(ELEMENT_NAME, ELEMENT_TYPE) \
  PROTOBUF_MAKE_BYTES_TYPE(ELEMENT_NAME, ELEMENT_TYPE, C1,                     \
                           ::protobuf_bytes::BytesMessage::CHANNEL_TYPE_C1);   \
  PROTOBUF_MAKE_BYTES_TYPE(ELEMENT_NAME, ELEMENT_TYPE, C2,                     \
                           ::protobuf_bytes::BytesMessage::CHANNEL_TYPE_C2);   \
  PROTOBUF_MAKE_BYTES_TYPE(ELEMENT_NAME, ELEMENT_TYPE, C3,                     \
                           ::protobuf_bytes::BytesMessage::CHANNEL_TYPE_C3);   \
  PROTOBUF_MAKE_BYTES_TYPE(ELEMENT_NAME, ELEMENT_TYPE, C4,                     \
                           ::protobuf_bytes::BytesMessage::CHANNEL_TYPE_C4)

PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    8U, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_8U);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    8S, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_8S);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    16U, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_16U);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    16S, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_16S);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    32U, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_32U);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    32S, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_32S);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    64U, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_64U);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    64S, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_64S);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    32F, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_32F);
PROTOBUF_MAKE_BYTES_TYPE_FOR_EACH_CHANNELS(
    64F, ::protobuf_bytes::BytesMessage::ELEMENT_TYPE_64F);

}  // namespace protobuf_bytes

#endif  // PROTOBUF_BYTES_CC_BYTES_CONSTANTS_H_