# Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from enum import IntEnum
from struct import unpack


class BytesElementType(IntEnum):
    ELEMENT_TYPE_CUSTOM = 0
    ELEMENT_TYPE_8U = 1
    ELEMENT_TYPE_8S = 2
    ELEMENT_TYPE_16U = 3
    ELEMENT_TYPE_16S = 4
    ELEMENT_TYPE_32U = 5
    ELEMENT_TYPE_32S = 6
    ELEMENT_TYPE_64U = 7
    ELEMENT_TYPE_64S = 8
    ELEMENT_TYPE_32F = 9
    ELEMENT_TYPE_64F = 10


class BytesChannelType(IntEnum):
    CHANNEL_TYPE_CUSTOM = 0
    CHANNEL_TYPE_C1 = 1
    CHANNEL_TYPE_C2 = 2
    CHANNEL_TYPE_C3 = 3
    CHANNEL_TYPE_C4 = 4


def element1_size(element_type):
    """Returns the size of one element.

    Args:
      element_type: BytesElementType

    Returns:
      int, If element_type is not one of BytesElementType, then returns -1.
    """
    return {
        BytesElementType.ELEMENT_TYPE_8U: 1,
        BytesElementType.ELEMENT_TYPE_8S: 1,
        BytesElementType.ELEMENT_TYPE_16U: 2,
        BytesElementType.ELEMENT_TYPE_16S: 2,
        BytesElementType.ELEMENT_TYPE_32U: 4,
        BytesElementType.ELEMENT_TYPE_32S: 4,
        BytesElementType.ELEMENT_TYPE_32F: 4,
        BytesElementType.ELEMENT_TYPE_64U: 8,
        BytesElementType.ELEMENT_TYPE_64S: 8,
        BytesElementType.ELEMENT_TYPE_64F: 8,
    }.get(element_type, -1)


def channel_size(channel_type):
    """Returns the number of channel.

    Args:
      channel_type: BytesChannelType

    Returns:
      int, If channel_type is not one of BytesChannelType, then returns -1.
    """
    return {
        BytesChannelType.CHANNEL_TYPE_C1: 1,
        BytesChannelType.CHANNEL_TYPE_C2: 2,
        BytesChannelType.CHANNEL_TYPE_C3: 3,
        BytesChannelType.CHANNEL_TYPE_C4: 4,
    }.get(channel_type, -1)


def get_element_and_channel_type(type):
    """Decomposes the type.

    Args:
      type: BytesType

    Returns:
      object containing element_type and channel_type.
    """
    return {
        'element_type': (type >> 16) & 0xFFFF,
        'channel_type': type & 0xFFFF,
    }


def make_type(element_type, channel_type):
    """Compose element_type and channel_type.

    Args:
      element_type: BytesElementType
      channel_type: BytesChannelType

    Returns:
      int
    """
    return ((element_type & 0xFFFF) << 16) | (channel_type & 0xFFFF)


class BytesType(IntEnum):
    BYTES_TYPE_8U_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_8U_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_8U_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_8U_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_8S_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_8S_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_8S_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_8S_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_16U_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_16U_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_16U_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_16U_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_16S_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_16S_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_16S_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_16S_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_32U_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_32U_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_32U_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_32U_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_32S_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_32S_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_32S_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_32S_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_32F_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_32F_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_32F_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_32F_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_64U_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_64U_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_64U_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_64U_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_64S_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_64S_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_64S_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_64S_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C4)
    BYTES_TYPE_64F_C1 = make_type(
        BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C1)
    BYTES_TYPE_64F_C2 = make_type(
        BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C2)
    BYTES_TYPE_64F_C3 = make_type(
        BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C3)
    BYTES_TYPE_64F_C4 = make_type(
        BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C4)


class Bytes(object):
    def __init__(self, bytes_message):
        type_info = get_element_and_channel_type(bytes_message.type)
        self.element_type = type_info['element_type']
        self.channel_type = type_info['channel_type']
        self.data = bytes_message.data
        self._read_func = self._bind_read_func()
        self._element_size = None
        self._element1_size = None
        self._channel_size = None
        self._length = None

    def _bind_read_func(self):
        return {
            BytesElementType.ELEMENT_TYPE_8U: lambda b: unpack('B', b)[0],
            BytesElementType.ELEMENT_TYPE_8S: lambda b: unpack('b', b)[0],
            BytesElementType.ELEMENT_TYPE_16U: lambda b: unpack('<H', b)[0],
            BytesElementType.ELEMENT_TYPE_16S: lambda b: unpack('<h', b)[0],
            BytesElementType.ELEMENT_TYPE_32U: lambda b: unpack('<I', b)[0],
            BytesElementType.ELEMENT_TYPE_32S: lambda b: unpack('<i', b)[0],
            BytesElementType.ELEMENT_TYPE_64U: lambda b: unpack('<L', b)[0],
            BytesElementType.ELEMENT_TYPE_64S: lambda b: unpack('<l', b)[0],
            BytesElementType.ELEMENT_TYPE_32F: lambda b: unpack('<f', b)[0],
            BytesElementType.ELEMENT_TYPE_64F: lambda b: unpack('<d', b)[0],
        }.get(self.element_type, None)

    def has_data(self, idx):
        """Returns true if there is data at |idx|.

        Returns:
          bool
        """
        return idx < self.length()

    def data_at(self, idx):
        """Returns the element at |idx|.

        Returns:
          list of int
        """
        v = []
        offset = self.element_size() * idx
        for _ in range(self.channel_size()):
            blist = []
            for _ in range(self.element1_size()):
                blist.append(offset)
                offset += 1
            v.append(self._read_func(bytes(blist)))
        return v

    def length(self):
        """Returns the length of data. This is not equal to byteLength.

        Returns:
          int
        """
        if self._length is None:
            self._length = len(self.data) // self.element_size()
        return self._length

    def element_size(self):
        """Returns the size of element.

        Returns:
          int, e.g) if type of bytes is BYTES_TYPE_8U_C3, then it returns 3.
        """
        if self._element_size is None:
            self._element_size = self.element1_size() * self.channel_size()
        return self._element_size

    def element1_size(self):
        """Returns the size of one element.

        Returns:
          int, e.g) if type of bytes is BYTES_TYPE_8U_C3, then it returns 1.
        """
        if self._element1_size is None:
            self._element1_size = element1_size(self.element_type)
        return self._element1_size

    def channel_size(self):
        """Returns the number of one channel.

        Returns:
          int
        """
        if self._channel_size is None:
            self._channel_size = channel_size(self.channel_type)
        return self._channel_size
