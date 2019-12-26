import 'mocha';
import { assert } from 'chai';
import { Bytes, BytesType } from '../src';

function fillArrayBuffer(
  buffer: ArrayBuffer,
  offset: number,
  step: number,
  func: (dataView: DataView, idx: number) => void
): void {
  const dataView = new DataView(buffer);
  for (let i = offset; i < buffer.byteLength; i += step) {
    func(dataView, i);
  }
}

let data: Uint8Array | undefined;

describe('Simple', () => {
  before(() => {
    const buffer = new ArrayBuffer(12);
    let i = 0;
    fillArrayBuffer(buffer, 0, 1, (dataView, idx) => {
      dataView.setUint8(idx, i);
      i++;
    });
    data = new Uint8Array(buffer);
  });

  it('channelSize(), element1Size(), elementSize()', () => {
    let bytes = new Bytes({ type: BytesType.BYTES_TYPE_8U_C1, data: data! });

    assert.equal(bytes.channelSize(), 1);
    assert.equal(bytes.element1Size(), 1);
    assert.equal(bytes.elementSize(), 1);

    bytes = new Bytes({ type: BytesType.BYTES_TYPE_8U_C3, data: data! });

    assert.equal(bytes.channelSize(), 3);
    assert.equal(bytes.element1Size(), 1);
    assert.equal(bytes.elementSize(), 3);

    bytes = new Bytes({ type: BytesType.BYTES_TYPE_16U_C3, data: data! });

    assert.equal(bytes.channelSize(), 3);
    assert.equal(bytes.element1Size(), 2);
    assert.equal(bytes.elementSize(), 6);
  });

  it('dataAt() bigEndian', () => {
    let bytes = new Bytes({ type: BytesType.BYTES_TYPE_8U_C1, data: data! });

    assert.deepEqual(bytes.dataAt(0), [0]);

    bytes = new Bytes({ type: BytesType.BYTES_TYPE_8U_C3, data: data! });

    assert.deepEqual(bytes.dataAt(0), [0, 1, 2]);

    bytes = new Bytes({ type: BytesType.BYTES_TYPE_16U_C3, data: data! });

    function makeUint16(high: number, low: number): number {
      return ((high & 0xff) << 8) | (low & 0xff);
    }

    assert.deepEqual(bytes.dataAt(0), [makeUint16(1, 0), makeUint16(3, 2), makeUint16(5, 4)]);
  });
});
