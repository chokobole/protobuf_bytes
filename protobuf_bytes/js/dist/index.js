"use strict";
// Copyright (c) 2019 The ProtobufBytes Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
Object.defineProperty(exports, "__esModule", { value: true });
var BytesElementType;
(function (BytesElementType) {
    BytesElementType[BytesElementType["ELEMENT_TYPE_CUSTOM"] = 0] = "ELEMENT_TYPE_CUSTOM";
    BytesElementType[BytesElementType["ELEMENT_TYPE_8U"] = 1] = "ELEMENT_TYPE_8U";
    BytesElementType[BytesElementType["ELEMENT_TYPE_8S"] = 2] = "ELEMENT_TYPE_8S";
    BytesElementType[BytesElementType["ELEMENT_TYPE_16U"] = 3] = "ELEMENT_TYPE_16U";
    BytesElementType[BytesElementType["ELEMENT_TYPE_16S"] = 4] = "ELEMENT_TYPE_16S";
    BytesElementType[BytesElementType["ELEMENT_TYPE_32U"] = 5] = "ELEMENT_TYPE_32U";
    BytesElementType[BytesElementType["ELEMENT_TYPE_32S"] = 6] = "ELEMENT_TYPE_32S";
    BytesElementType[BytesElementType["ELEMENT_TYPE_64U"] = 7] = "ELEMENT_TYPE_64U";
    BytesElementType[BytesElementType["ELEMENT_TYPE_64S"] = 8] = "ELEMENT_TYPE_64S";
    BytesElementType[BytesElementType["ELEMENT_TYPE_32F"] = 9] = "ELEMENT_TYPE_32F";
    BytesElementType[BytesElementType["ELEMENT_TYPE_64F"] = 10] = "ELEMENT_TYPE_64F";
})(BytesElementType = exports.BytesElementType || (exports.BytesElementType = {}));
var BytesChannelType;
(function (BytesChannelType) {
    BytesChannelType[BytesChannelType["CHANNEL_TYPE_CUSTOM"] = 0] = "CHANNEL_TYPE_CUSTOM";
    BytesChannelType[BytesChannelType["CHANNEL_TYPE_C1"] = 1] = "CHANNEL_TYPE_C1";
    BytesChannelType[BytesChannelType["CHANNEL_TYPE_C2"] = 2] = "CHANNEL_TYPE_C2";
    BytesChannelType[BytesChannelType["CHANNEL_TYPE_C3"] = 3] = "CHANNEL_TYPE_C3";
    BytesChannelType[BytesChannelType["CHANNEL_TYPE_C4"] = 4] = "CHANNEL_TYPE_C4";
})(BytesChannelType = exports.BytesChannelType || (exports.BytesChannelType = {}));
function getDataView(data) {
    const { buffer, byteOffset, byteLength } = data;
    return new DataView(buffer, byteOffset, byteLength);
}
function element1Size(elementType) {
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
            throw new Error('Unknown element size');
    }
}
exports.element1Size = element1Size;
function channelSize(channelType) {
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
            throw new Error('Unknown channel size');
    }
}
exports.channelSize = channelSize;
function getElementAndChannelType(type) {
    return { elementType: (type >> 16) & 0xffff, channelType: type & 0xffff };
}
exports.getElementAndChannelType = getElementAndChannelType;
function makeType(elementType, channelType) {
    return ((elementType & 0xffff) << 16) | (channelType & 0xffff);
}
exports.makeType = makeType;
var BytesType;
(function (BytesType) {
    BytesType[BytesType["BYTES_TYPE_8U_C1"] = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_8U_C1";
    BytesType[BytesType["BYTES_TYPE_8U_C2"] = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_8U_C2";
    BytesType[BytesType["BYTES_TYPE_8U_C3"] = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_8U_C3";
    BytesType[BytesType["BYTES_TYPE_8U_C4"] = makeType(BytesElementType.ELEMENT_TYPE_8U, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_8U_C4";
    BytesType[BytesType["BYTES_TYPE_8S_C1"] = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_8S_C1";
    BytesType[BytesType["BYTES_TYPE_8S_C2"] = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_8S_C2";
    BytesType[BytesType["BYTES_TYPE_8S_C3"] = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_8S_C3";
    BytesType[BytesType["BYTES_TYPE_8S_C4"] = makeType(BytesElementType.ELEMENT_TYPE_8S, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_8S_C4";
    BytesType[BytesType["BYTES_TYPE_16U_C1"] = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_16U_C1";
    BytesType[BytesType["BYTES_TYPE_16U_C2"] = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_16U_C2";
    BytesType[BytesType["BYTES_TYPE_16U_C3"] = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_16U_C3";
    BytesType[BytesType["BYTES_TYPE_16U_C4"] = makeType(BytesElementType.ELEMENT_TYPE_16U, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_16U_C4";
    BytesType[BytesType["BYTES_TYPE_16S_C1"] = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_16S_C1";
    BytesType[BytesType["BYTES_TYPE_16S_C2"] = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_16S_C2";
    BytesType[BytesType["BYTES_TYPE_16S_C3"] = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_16S_C3";
    BytesType[BytesType["BYTES_TYPE_16S_C4"] = makeType(BytesElementType.ELEMENT_TYPE_16S, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_16S_C4";
    BytesType[BytesType["BYTES_TYPE_32U_C1"] = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_32U_C1";
    BytesType[BytesType["BYTES_TYPE_32U_C2"] = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_32U_C2";
    BytesType[BytesType["BYTES_TYPE_32U_C3"] = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_32U_C3";
    BytesType[BytesType["BYTES_TYPE_32U_C4"] = makeType(BytesElementType.ELEMENT_TYPE_32U, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_32U_C4";
    BytesType[BytesType["BYTES_TYPE_32S_C1"] = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_32S_C1";
    BytesType[BytesType["BYTES_TYPE_32S_C2"] = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_32S_C2";
    BytesType[BytesType["BYTES_TYPE_32S_C3"] = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_32S_C3";
    BytesType[BytesType["BYTES_TYPE_32S_C4"] = makeType(BytesElementType.ELEMENT_TYPE_32S, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_32S_C4";
    BytesType[BytesType["BYTES_TYPE_32F_C1"] = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_32F_C1";
    BytesType[BytesType["BYTES_TYPE_32F_C2"] = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_32F_C2";
    BytesType[BytesType["BYTES_TYPE_32F_C3"] = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_32F_C3";
    BytesType[BytesType["BYTES_TYPE_32F_C4"] = makeType(BytesElementType.ELEMENT_TYPE_32F, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_32F_C4";
    BytesType[BytesType["BYTES_TYPE_64U_C1"] = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_64U_C1";
    BytesType[BytesType["BYTES_TYPE_64U_C2"] = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_64U_C2";
    BytesType[BytesType["BYTES_TYPE_64U_C3"] = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_64U_C3";
    BytesType[BytesType["BYTES_TYPE_64U_C4"] = makeType(BytesElementType.ELEMENT_TYPE_64U, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_64U_C4";
    BytesType[BytesType["BYTES_TYPE_64S_C1"] = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_64S_C1";
    BytesType[BytesType["BYTES_TYPE_64S_C2"] = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_64S_C2";
    BytesType[BytesType["BYTES_TYPE_64S_C3"] = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_64S_C3";
    BytesType[BytesType["BYTES_TYPE_64S_C4"] = makeType(BytesElementType.ELEMENT_TYPE_64S, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_64S_C4";
    BytesType[BytesType["BYTES_TYPE_64F_C1"] = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C1)] = "BYTES_TYPE_64F_C1";
    BytesType[BytesType["BYTES_TYPE_64F_C2"] = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C2)] = "BYTES_TYPE_64F_C2";
    BytesType[BytesType["BYTES_TYPE_64F_C3"] = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C3)] = "BYTES_TYPE_64F_C3";
    BytesType[BytesType["BYTES_TYPE_64F_C4"] = makeType(BytesElementType.ELEMENT_TYPE_64F, BytesChannelType.CHANNEL_TYPE_C4)] = "BYTES_TYPE_64F_C4";
})(BytesType = exports.BytesType || (exports.BytesType = {}));
class Bytes {
    constructor({ type, data }) {
        this.length_ = 0;
        this.elementSize_ = 0;
        this.element1Size_ = 0;
        this.channelSize_ = 0;
        const { elementType, channelType } = getElementAndChannelType(type);
        this.elementType = elementType;
        this.channelType = channelType;
        this.dataView = getDataView(data);
        this.readFunc = this._bindReadFunc();
    }
    _bindReadFunc() {
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
    hasData(idx) {
        return idx < this.length();
    }
    nextData(idx) {
        const v = [];
        const from = this.elementSize() * idx;
        const to = this.elementSize() * (idx + 1);
        for (let i = from; i < to; i += this.element1Size()) {
            v.push(this.readFunc(i, true));
        }
        return v;
    }
    length() {
        if (!this.length_)
            this.length_ = this.dataView.byteLength / this.elementSize();
        return this.length_;
    }
    elementSize() {
        if (!this.elementSize_) {
            this.elementSize_ = this.element1Size() * this.channelSize();
        }
        return this.elementSize_;
    }
    element1Size() {
        if (!this.element1Size_)
            this.element1Size_ = element1Size(this.elementType);
        return this.element1Size_;
    }
    channelSize() {
        if (!this.channelSize_)
            this.channelSize_ = channelSize(this.channelType);
        return this.channelSize_;
    }
}
exports.Bytes = Bytes;
