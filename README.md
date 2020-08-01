# PyVidarDB

[![Build Status](https://dev.azure.com/vidardb/PyVidarDB/_apis/build/status/vidardb.PyVidarDB?branchName=master)](https://dev.azure.com/vidardb/PyVidarDB/_build/latest?definitionId=1&branchName=master)
![PyPI - Python Version](https://img.shields.io/pypi/pyversions/pyvidardb)
[![PyPI version](https://badge.fury.io/py/PyVidarDB.svg)](https://badge.fury.io/py/PyVidarDB)

A simple python wrapper for [VidarDB](https://github.com/vidardb/vidardb-engine).

## Use PyVidarDB

PyVidarDB guarantees to support `Python >= 3.5`.
There is no need to have VidarDB installed in advance, PyVidarDB will install it automatically for you.

### Dependencies

For Linux users (Ubuntu as an example):

```bash
sudo apt-get update
sudo apt-get install git python3-pip build-essential cmake
```

For MacOS users (Please install [Homebrew](https://brew.sh/) at first):

```bash
sudo brew install git python3 cmake
```

For Windows users:

The compiler should support C++11 (at least Visual Studio 2015 update 3).

### PyVidarDB Installation

From PyPI:

```bash
pip3 install PyVidarDB
```

From Github:

```bash
git clone --recursive https://github.com/vidardb/PyVidarDB.git
pip3 install ./PyVidarDB
```

## Basic Usage

Here is the basic usage for PyVidarDB:

```python
import pyvidardb

db = pyvidardb.DB()

# Open the database, will create one if not exist.
db.open("./hello_world")

# Put a map from 'key1' to 'value1' into the database.
db.put(b"key1", b"value1")

# Get the value(s) of the provided key, will return None
# if there is no such key in the database.
value = db.get(b"key1")
assert value == [b"value1"]

# 'key2' does not exist in the database. So we will get None here.
value = db.get(b"key2")
assert value is None

# Remove 'key1' from the database.
db.delete(b"key1")

# Put a map from 'key2' to multiple values into the database.
db.put(b"key2", [b"value1", b"value2", b"value3"])

# Get the value(s) of the provided key.
value = db.get(b"key2")
assert value == [b"value1", b"value2", b"value3"]

# Remove 'key2' from the database.
db.delete(b"key2")

# Close the database.
db.close()
```

PyVidarDB supports storing one key with multiple values. For example,
`db.put(b"key", [b"value1", b"value2", b"value3"])` will put a map
from `key` to `[b"value1", b"value2", b"value3"]` into the database.
To store one key with one value, simply call `db.put(b"key", b"value")`
or `db.put(b"key", [b"value"])`. For `db.put()`, the passed key's type
must be `bytes`, while the values' type can be `bytes` or a list of `bytes`. 

For `db.get(key: bytes)` and `db.delete(key: bytes)`, the passed arguments'
types must be `bytes`. The return type of `db.get(key: bytes)` is a list of
`bytes` which contains all the values of that key. If the provided key does
not exist in the database, `None` will be returned.

More examples can be found at here: https://github.com/vidardb/PyVidarDB/tree/master/examples 

See our [wiki](https://github.com/vidardb/PyVidarDB/wiki) page for more information.
