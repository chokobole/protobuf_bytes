# Protobuf Bytes for nodeJS

## Contents
- [Protobuf Bytes for nodeJS](#protobuf-bytes-for-nodejs)
  - [Contents](#contents)
  - [Install](#install)
  - [Get protobuf](#get-protobuf)
  - [Examples](#examples)
  - [APIs](#apis)

## Install

To use protobuf_bytes, install package via npm install.

```bash
npm install protobuf_bytes
```

## Get protobuf

The protobuf file is located [here](https://github.com/chokobole/protobuf_bytes/blob/master/protobuf_bytes/bytes.proto).

## Examples

```js
const { Bytes } = require('protobuf_bytes');

function fillArrayBuffer(buffer, offset, step, func) {
  const dataView = new DataView(buffer);
  for (let i = offset; i < buffer.byteLength; i += step) {
    func(dataView, i);
  }
}

const buffer = new ArrayBuffer(12);
let i = 0;
fillArrayBuffer(buffer, 0, 1, (dataView, idx) => {
  dataView.setUint8(idx, i);
  i++;
});
const data = new Uint8Array(buffer);

const b = new Bytes({
  type: BytesType.BYTES_TYPE_8U_C1,
  data: data
});

for (let i = 0; i < b.length(); i++) {
  console.log(b.dataAt(i));
}
// [ 0 ]
// [ 1 ]
// [ 2 ]
// [ 3 ]
// [ 4 ]
// [ 5 ]
// [ 6 ]
// [ 7 ]
// [ 8 ]
// [ 9 ]
// [ 10 ]
// [ 11 ]

const b2 = new Bytes({
  type: BytesType.BYTES_TYPE_8U_C3,
  data: data
});

for (let i = 0; i < b2.length(); i++) {
  console.log(b2.dataAt(i));
}
// [ 0, 1, 2 ]
// [ 3, 4, 5 ]
// [ 6, 7, 8 ]
// [ 9, 10, 11 ]
```

## APIs

Please reads [docs/apis.md](https://github.com/chokobole/protobuf_bytes/blob/master/protobuf_bytes/js/docs/apis.md).
