export declare enum BytesElementType {
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
    ELEMENT_TYPE_64F = 10
}
export declare enum BytesChannelType {
    CHANNEL_TYPE_CUSTOM = 0,
    CHANNEL_TYPE_C1 = 1,
    CHANNEL_TYPE_C2 = 2,
    CHANNEL_TYPE_C3 = 3,
    CHANNEL_TYPE_C4 = 4
}
export declare function element1Size(elementType: BytesElementType): number;
export declare function channelSize(channelType: BytesChannelType): number;
export declare function getElementAndChannelType(type: number): {
    elementType: number;
    channelType: number;
};
export declare function makeType(elementType: number, channelType: number): number;
export declare enum BytesType {
    BYTES_TYPE_8U_C1,
    BYTES_TYPE_8U_C2,
    BYTES_TYPE_8U_C3,
    BYTES_TYPE_8U_C4,
    BYTES_TYPE_8S_C1,
    BYTES_TYPE_8S_C2,
    BYTES_TYPE_8S_C3,
    BYTES_TYPE_8S_C4,
    BYTES_TYPE_16U_C1,
    BYTES_TYPE_16U_C2,
    BYTES_TYPE_16U_C3,
    BYTES_TYPE_16U_C4,
    BYTES_TYPE_16S_C1,
    BYTES_TYPE_16S_C2,
    BYTES_TYPE_16S_C3,
    BYTES_TYPE_16S_C4,
    BYTES_TYPE_32U_C1,
    BYTES_TYPE_32U_C2,
    BYTES_TYPE_32U_C3,
    BYTES_TYPE_32U_C4,
    BYTES_TYPE_32S_C1,
    BYTES_TYPE_32S_C2,
    BYTES_TYPE_32S_C3,
    BYTES_TYPE_32S_C4,
    BYTES_TYPE_32F_C1,
    BYTES_TYPE_32F_C2,
    BYTES_TYPE_32F_C3,
    BYTES_TYPE_32F_C4,
    BYTES_TYPE_64U_C1,
    BYTES_TYPE_64U_C2,
    BYTES_TYPE_64U_C3,
    BYTES_TYPE_64U_C4,
    BYTES_TYPE_64S_C1,
    BYTES_TYPE_64S_C2,
    BYTES_TYPE_64S_C3,
    BYTES_TYPE_64S_C4,
    BYTES_TYPE_64F_C1,
    BYTES_TYPE_64F_C2,
    BYTES_TYPE_64F_C3,
    BYTES_TYPE_64F_C4
}
export interface BytesMessage {
    type: number;
    data: Uint8Array;
}
export declare class Bytes {
    elementType: BytesElementType;
    channelType: BytesChannelType;
    dataView: DataView;
    private readFunc;
    private _length;
    private _elementSize;
    private _element1Size;
    private _channelSize;
    constructor({ type, data }: BytesMessage);
    _bindReadFunc(): ((byteOffset: number, littenEndian?: boolean | undefined) => number) | ((byteOffset: number, littleEndian?: boolean | undefined) => bigint) | null;
    hasData(idx: number): boolean;
    dataAt(idx: number): number[];
    length(): number;
    elementSize(): number;
    element1Size(): number;
    channelSize(): number;
}
