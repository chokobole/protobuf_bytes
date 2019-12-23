// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PROTOBUF_BYTES_EXPORT_H_
#define PROTOBUF_BYTES_EXPORT_H_

#if defined(PROTOBUF_BYTES_COMPONENT_BUILD)

#if defined(_WIN32)
#ifdef PROTOBUF_BYTES_COMPILE_LIBRARY
#define PROTOBUF_BYTES_EXPORT __declspec(dllexport)
#else
#define PROTOBUF_BYTES_EXPORT __declspec(dllimport)
#endif  // defined(PROTOBUF_BYTES_COMPILE_LIBRARY)

#else
#ifdef PROTOBUF_BYTES_COMPILE_LIBRARY
#define PROTOBUF_BYTES_EXPORT __attribute__((visibility("default")))
#else
#define PROTOBUF_BYTES_EXPORT
#endif  // defined(PROTOBUF_BYTES_COMPILE_LIBRARY)
#endif  // defined(_WIN32)

#else
#define PROTOBUF_BYTES_EXPORT
#endif  // defined(PROTOBUF_BYTES_COMPONENT_BUILD)

#endif  // PROTOBUF_BYTES_EXPORT_H_