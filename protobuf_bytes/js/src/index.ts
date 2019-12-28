// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

export enum BytesElementType {
  ELEMENT_TYPE_CUSTOM = 0,
  ELEMENT_TYPE_8U = 1,
  ELEMENT_TYPE_8S = 2,
  ELEMENT_TYPE_16U = 3,
  ELEMENT_TYPE_16S = 4,
  ELEMENT_TYPE_32U = 5,
  ELEMENT_TYPE_32S = 6,
  ELEMENT_TYPE_64U = 7,
  ELEMENT_TYPE_64S = 8,
  ELEMENT_TYPE_32F = 9,
  ELEMENT_TYPE_64F = 10,
}

export enum BytesChannelType {
  CHANNEL_TYPE_CUSTOM = 0,
  CHANNEL_TYPE_C1 = 1,
  CHANNEL_TYPE_C2 = 2,
  CHANNEL_TYPE_C3 = 3,
  CHANNEL_TYPE_C4 = 4,
}

function getDataView(data: Uint8Array): DataView {
  const { buffer, byteOffset, byteLength } = data;
  return new DataView(buffer, byteOffset, byteLength);
}

// Returns the size of one element. If |elementType| is not one of BytesElementType, then returns -1.
export function element1Size(elementType: BytesElementType): number {
  switch (elementType) {
    case BytesElementType.ELEMENT_TYPE_8U:
    case BytesElementType.ELEMENT_TYPE_8S:
      return 1;
    case BytesElementType.ELEMENT_TYPE_16U:
    case BytesElementType.ELEMENT_TYPE_16S:
      return 2;
    case BytesElementType.ELEMENT_TYPE_32U:
    case BytesElementType.ELEMENT_TYPE_32S:
    case BytesElementType.ELEMENT_TYPE_32F:
      return 4;
    case BytesElementType.ELEMENT_TYPE_64U:
    case BytesElementType.ELEMENT_TYPE_64S:
    case BytesElementType.ELEMENT_TYPE_64F:
      return 8;
    default:
      return -1;
  }
}

// Returns the number of channel. If |channelType| is not one of BytesChannelType, then returns -1.
export function channelSize(channelType: BytesChannelType): number {
  switch (channelType) {
    case BytesChannelType.CHANNEL_TYPE_C1:
      return 1;
    case BytesChannelType.CHANNEL_TYPE_C2:
      return 2;
    case BytesChannelType.CHANNEL_TYPE_C3:
      return 3;
    case BytesChannelType.CHANNEL_TYPE_C4:
      return 4;
    default:
      return -1;
  }
}

// Decomposes the |type| and return the object containing |elementType| and |channelType|.
export function getElementAndChannelType(
  type: number
): { elementType: number; channelType: number } {
  return { elementType: (type >> 16) & 0xffff, channelType: type & 0xffff };
}

// Composes |elementType| and |channelType|.
export function makeType(elementType: number, channelType: number): number {
  return ((elementType & 0xffff) << 16) | (channelType & 0xffff);
}

export enum BytesType {
  BYTES_TYPE_8U_C1 = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_8U_C2 = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_8U_C3 = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_8U_C4 = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_8S_C1 = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_8S_C2 = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_8S_C3 = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_8S_C4 = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_16U_C1 = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_16U_C2 = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_16U_C3 = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_16U_C4 = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_16S_C1 = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_16S_C2 = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_16S_C3 = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_16S_C4 = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_32U_C1 = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_32U_C2 = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_32U_C3 = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_32U_C4 = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_32S_C1 = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_32S_C2 = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_32S_C3 = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_32S_C4 = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_32F_C1 = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_32F_C2 = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_32F_C3 = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_32F_C4 = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_64U_C1 = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_64U_C2 = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_64U_C3 = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_64U_C4 = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_64S_C1 = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_64S_C2 = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_64S_C3 = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_64S_C4 = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C4),
  BYTES_TYPE_64F_C1 = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C1),
  BYTES_TYPE_64F_C2 = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C2),
  BYTES_TYPE_64F_C3 = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C3),
  BYTES_TYPE_64F_C4 = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C4),
}

export interface BytesMessage {
  type: number;
  bigendian: boolean;
  data: Uint8Array;
}

export class Bytes {
  elementType: BytesElementType;

  channelType: BytesChannelType;

  bigendian: boolean;

  dataView: DataView;

  private readFunc:
    | ((byteOffset: number, littenEndian?: boolean | undefined) => number)
    | ((byteOffset: number, littleEndian?: boolean | undefined) => bigint)
    | null;

  private _length = 0;

  private _elementSize = 0;

  private _element1Size = 0;

  private _channelSize = 0;

  constructor({type, bigendian, data}: BytesMessage) {
    const { elementType, channelType } = getElementAndChannelType(type);
    this.elementType = elementType;
    this.channelType = channelType;
    this.bigendian = bigendian;
    this.dataView = getDataView(data);
    this.readFunc = this._bindReadFunc()!;
  }

  _bindReadFunc():
    | ((byteOffset: number, littenEndian?: boolean | undefined) => number)
    | ((byteOffset: number, littleEndian?: boolean | undefined) => bigint)
    | null {
    switch (this.elementType) {
      case BytesElementType.ELEMENT_TYPE_8U:
        return this.dataView.getUint8.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_8S:
        return this.dataView.getInt8.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_16U:
        return this.dataView.getUint16.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_16S:
        return this.dataView.getInt16.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_32U:
        return this.dataView.getUint32.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_32S:
        return this.dataView.getInt32.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_32F:
        return this.dataView.getFloat32.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_64U:
        return this.dataView.getBigUint64.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_64S:
        return this.dataView.getBigInt64.bind(this.dataView);
      case BytesElementType.ELEMENT_TYPE_64F:
        return this.dataView.getFloat64.bind(this.dataView);
      default:
        return null;
    }
  }

  // Returns true if there is data at |idx|.
  hasData(idx: number): boolean {
    return idx < this.length();
  }

  // Returns the element(array of number) at |idx|.
  dataAt(idx: number): number[] {
    const v = [];
    const from = this.elementSize() * idx;
    const to = this.elementSize() * (idx + 1);
    for (let i = from; i < to; i += this.element1Size()) {
      v.push(this.readFunc!(i, !this.bigendian));
    }
    return v as number[];
  }

  // Returns the length of data. This is not equal to byteLength.
  length(): number {
    if (!this._length) this._length = this.dataView.byteLength / this.elementSize();
    return this._length;
  }

  // Returns the size of element. e.g) if type of bytes is BYTES_TYPE_8U_C3, then it returns 3.
  elementSize(): number {
    if (!this._elementSize) {
      this._elementSize = this.element1Size() * this.channelSize();
    }
    return this._elementSize;
  }

  // Returns the size of one element. e.g) if type of bytes is BYTES_TYPE_8U_C3, then it returns 1.
  element1Size(): number {
    if (!this._element1Size) this._element1Size = element1Size(this.elementType);
    return this._element1Size;
  }

  // Returns the number of channel.
  channelSize(): number {
    if (!this._channelSize) this._channelSize = channelSize(this.channelType);
    return this._channelSize;
  }
}
