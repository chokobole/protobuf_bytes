# APIs

- [APIs](#apis)
  - [Enum: BytesElementType](#enum-byteselementtype)
  - [Enum: BytesChannelType](#enum-byteschanneltype)
  - [Enum: BytesType](#enum-bytestype)
  - [element1_size(element_type)](#element1sizeelementtype)
  - [channel_size(channel_type)](#channelsizechanneltype)
  - [get_element_and_channel_type(type)](#getelementandchanneltypetype)
  - [make_type(element_type, channel_type)](#maketypeelementtype-channeltype)
  - [Class: Bytes](#class-bytes)
    - [Bytes(bytes_message)](#bytesbytesmessage)
    - [self.has_data(idx)](#selfhasdataidx)
    - [self.data_at(idx)](#selfdataatidx)
    - [self.length()](#selflength)
    - [self.element_size()](#selfelementsize)
    - [self.element1_size()](#selfelement1size)
    - [self.channel_size()](#selfchannelsize)

## Enum: BytesElementType

* ELEMENT_TYPE_CUSTOM
* ELEMENT_TYPE_8U
* ELEMENT_TYPE_8S
* ELEMENT_TYPE_16U
* ELEMENT_TYPE_16S
* ELEMENT_TYPE_32U
* ELEMENT_TYPE_32S
* ELEMENT_TYPE_64U
* ELEMENT_TYPE_64S
* ELEMENT_TYPE_32F
* ELEMENT_TYPE_64F

## Enum: BytesChannelType

* CHANNEL_TYPE_CUSTOM
* CHANNEL_TYPE_C1
* CHANNEL_TYPE_C2
* CHANNEL_TYPE_C3
* CHANNEL_TYPE_C4

## Enum: BytesType

* BYTES_TYPE_8U_C1
* BYTES_TYPE_8U_C2
* BYTES_TYPE_8U_C3
* BYTES_TYPE_8U_C4
* BYTES_TYPE_8S_C1
* BYTES_TYPE_8S_C2
* BYTES_TYPE_8S_C3
* BYTES_TYPE_8S_C4
* BYTES_TYPE_16U_C1
* BYTES_TYPE_16U_C2
* BYTES_TYPE_16U_C3
* BYTES_TYPE_16U_C4
* BYTES_TYPE_16S_C1
* BYTES_TYPE_16S_C2
* BYTES_TYPE_16S_C3
* BYTES_TYPE_16S_C4
* BYTES_TYPE_32U_C1
* BYTES_TYPE_32U_C2
* BYTES_TYPE_32U_C3
* BYTES_TYPE_32U_C4
* BYTES_TYPE_32S_C1
* BYTES_TYPE_32S_C2
* BYTES_TYPE_32S_C3
* BYTES_TYPE_32S_C4
* BYTES_TYPE_32F_C1
* BYTES_TYPE_32F_C2
* BYTES_TYPE_32F_C3
* BYTES_TYPE_32F_C4
* BYTES_TYPE_64U_C1
* BYTES_TYPE_64U_C2
* BYTES_TYPE_64U_C3
* BYTES_TYPE_64U_C4
* BYTES_TYPE_64S_C1
* BYTES_TYPE_64S_C2
* BYTES_TYPE_64S_C3
* BYTES_TYPE_64S_C4
* BYTES_TYPE_64F_C1
* BYTES_TYPE_64F_C2
* BYTES_TYPE_64F_C3
* BYTES_TYPE_64F_C4

## element1_size(element_type)

* `element_type` {BytesElementType}
* {int}

Returns the size of one element. If `element_type` is not one of `BytesElementType`, then returns -1.

## channel_size(channel_type)

* `channel_type` {BytesChannelType}
* {int}

Returns the number of channel. If `channel_type` is not one of `BytesChannelType`, then returns -1.

## get_element_and_channel_type(type)

* `type` {BytesType}
* {object}

Decomposes the `type` and return the object containing `element_type` and `channel_type`.

## make_type(element_type, channel_type)

* `element_type` {BytesElementType}
* `channel_type` {BytesChannelType}
* {int}

Composes `element_type` and `channel_type`.

## Class: Bytes

This class represents a protobuf bytes.

### Bytes(bytes_message)

* `bytes_message` {BytesMessage}

Creates a new bytes instance.

### self.has_data(idx)

* `idx` {int}
* {boolean}

Returns true if there is data at `idx`.

### self.data_at(idx)

* `idx` {int}
* {list}

Returns the element(list of int) at `idx`.

### self.length()

* {int}

Returns the length of data. This is not equal to byteLength.

### self.element_size()

* {int}

Returns the size of element. e.g) if `type` of `bytes` is `BYTES_TYPE_8U_C3`, then it returns 3.

### self.element1_size()

* {int}

Returns the size of one element. e.g) if `type` of `bytes` is `BYTES_TYPE_8U_C3`, then it returns 1.

### self.channel_size()

* {int}

Returns the number of channel.