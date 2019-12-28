# Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from collections import namedtuple
from protobuf_bytes import Bytes, BytesType
import unittest

BytesMessage = namedtuple("BytesMessage", 'type bigendian data')


def make_uint16(high, low):
    return ((high & 0xFF) << 8) | (low & 0xFF)


class TestProtobufBytes(unittest.TestCase):
    def setUp(self):
        self.data = ''.join(chr(item) for item in range(12))

    def test_sizes(self):
        m = BytesMessage(type=BytesType.BYTES_TYPE_8U_C1, bigendian=False, data=self.data)
        b = Bytes(m)

        self.assertEqual(b.channel_size(), 1)
        self.assertEqual(b.element1_size(), 1)
        self.assertEqual(b.element_size(), 1)

        m = BytesMessage(type=BytesType.BYTES_TYPE_8U_C3, bigendian=False, data=self.data)
        b = Bytes(m)

        self.assertEqual(b.channel_size(), 3)
        self.assertEqual(b.element1_size(), 1)
        self.assertEqual(b.element_size(), 3)

        m = BytesMessage(type=BytesType.BYTES_TYPE_16U_C3, bigendian=False, data=self.data)
        b = Bytes(m)

        self.assertEqual(b.channel_size(), 3)
        self.assertEqual(b.element1_size(), 2)
        self.assertEqual(b.element_size(), 6)

    def test_data_at_big_endian(self):
        m = BytesMessage(type=BytesType.BYTES_TYPE_8U_C1, bigendian=True, data=self.data)
        b = Bytes(m)

        self.assertListEqual(b.data_at(0), [0])

        m = BytesMessage(type=BytesType.BYTES_TYPE_8U_C3, bigendian=True, data=self.data)
        b = Bytes(m)

        self.assertListEqual(b.data_at(0), [0, 1, 2])

        m = BytesMessage(type=BytesType.BYTES_TYPE_16U_C3, bigendian=True, data=self.data)
        b = Bytes(m)

        self.assertListEqual(b.data_at(0), [make_uint16(
            0, 1), make_uint16(2, 3), make_uint16(4, 5)])

    def test_data_at_little_endian(self):
        m = BytesMessage(type=BytesType.BYTES_TYPE_8U_C1, bigendian=False, data=self.data)
        b = Bytes(m)

        self.assertListEqual(b.data_at(0), [0])

        m = BytesMessage(type=BytesType.BYTES_TYPE_8U_C3, bigendian=False, data=self.data)
        b = Bytes(m)

        self.assertListEqual(b.data_at(0), [0, 1, 2])

        m = BytesMessage(type=BytesType.BYTES_TYPE_16U_C3, bigendian=False, data=self.data)
        b = Bytes(m)

        self.assertListEqual(b.data_at(0), [make_uint16(
            1, 0), make_uint16(3, 2), make_uint16(5, 4)])


if __name__ == '__main__':
    unittest.main()
