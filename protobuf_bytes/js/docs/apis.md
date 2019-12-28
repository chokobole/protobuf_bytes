# APIs

- [APIs](#apis)
  - [Enum: BytesElementType](#enum-byteselementtype)
  - [Enum: BytesChannelType](#enum-byteschanneltype)
  - [Enum: BytesType](#enum-bytestype)
  - [element1Size(elementType)](#element1sizeelementtype)
  - [channelSize(channelType)](#channelsizechanneltype)
  - [getElementAndChannelType(type)](#getelementandchanneltypetype)
  - [makeType(elementType, channelType)](#maketypeelementtype-channeltype)
  - [Class: Bytes](#class-bytes)
    - [new Bytes({ type, bigendian, data })](#new-bytes-type-bigendian-data)
    - [bytes.hasData(idx)](#byteshasdataidx)
    - [bytes.dataAt(idx)](#bytesdataatidx)
    - [bytes.length()](#byteslength)
    - [bytes.elementSize()](#byteselementsize)
    - [bytes.element1Size()](#byteselement1size)
    - [bytes.channelSize()](#byteschannelsize)

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

## element1Size(elementType)

* `elementType` {BytesElementType}
* {number}

Returns the size of one element. If `elementType` is not one of `BytesElementType`, then returns -1.

## channelSize(channelType)

* `channelType` {BytesChannelType}
* {number}

Returns the number of channel. If `channelType` is not one of `BytesChannelType`, then returns -1.

## getElementAndChannelType(type)

* `type` {BytesType}
* {object}

Decomposes the `type` and return the object containing `elementType` and `channelType`.

## makeType(elementType, channelType)

* `elementType` {BytesElementType}
* `channelType` {BytesChannelType}
* {number}

Composes `elementType` and `channelType`.

## Class: Bytes

This class represents a protobuf bytes.

### new Bytes({ type, bigendian, data })

* `type` {BytesType}
* `bigendian` {boolean}
* `data` {Uint8Array}

Creates a new bytes instance.

### bytes.hasData(idx)

* `idx` {number}
* {boolean}

Returns true if there is data at `idx`.

### bytes.dataAt(idx)

* `idx` {number}
* {Array}

Returns the element(array of number) at `idx`.

### bytes.length()

* {number}

Returns the length of data. This is not equal to byteLength.

### bytes.elementSize()

* {number}

Returns the size of element. e.g) if `type` of `bytes` is `BYTES_TYPE_8U_C3`, then it returns 3.

### bytes.element1Size()

* {number}

Returns the size of one element. e.g) if `type` of `bytes` is `BYTES_TYPE_8U_C3`, then it returns 1.

### bytes.channelSize()

* {number}

Returns the number of channel.