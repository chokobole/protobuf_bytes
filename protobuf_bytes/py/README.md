# Protobuf Bytes for python

## Contents
- [Protobuf Bytes for python](#protobuf-bytes-for-python)
  - [Contents](#contents)
  - [Install](#install)
  - [Get protobuf](#get-protobuf)
  - [Examples](#examples)
  - [APIs](#apis)

## Install

To use protobuf_bytes, install package via pip install.

```bash
pip install protobuf_bytes
```

Or install from source.

```bash
python setup.py install
```

## Get protobuf

The protobuf file is located [here](/protobuf_bytes/bytes.proto).

## Examples

```python
from bytes_pb2 import BytesMessage
from protobuf_bytes import Bytes, BytesType

m = BytesMessage()
m.type = BytesType.BYTES_TYPE_8U_C1
m.bigendian = False
m.data = bytes(range(12))
b = Bytes(m)

for i in range(b.length()):
    print(b.data_at(i))
// [0]
// [1]
// [2]
// [3]
// [4]
// [5]
// [6]
// [7]
// [8]
// [9]
// [10]
// [11]

m.type = BytesType.BYTES_TYPE_8U_C3
b = Bytes(m)
for i in range(b.length()):
    print(b.data_at(i))
// [0, 1, 2]
// [3, 4, 5]
// [6, 7, 8]
// [9, 10, 11]
```

## APIs

Please reads [docs/apis.md](docs/apis.md).
