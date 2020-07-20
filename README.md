# PyVidarDB

[![Build Status](https://dev.azure.com/vidardb/PyVidarDB/_apis/build/status/vidardb.PyVidarDB?branchName=master)](https://dev.azure.com/vidardb/PyVidarDB/_build/latest?definitionId=1&branchName=master)
![Supported Python Version](https://img.shields.io/badge/python-%3E%3D%20v3.5-blue)


A simple python wrapper for [VidarDB](https://github.com/vidardb/vidardb-engine).

## Use PyVidarDB

PyVidarDB currently supports Python3.5, Python3.6, Python3.7, and Python3.8.
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

# Get the value of the provided key, will return None
# if there is no such key in the database.
value = db.get(b"key1")
assert value == b"value1"

# 'key2' does not exist in the database. So we will get None here.
value = db.get(b"key2")
assert value is None

# Remove 'key1' from the database.
db.delete(b"key1")

# Close the database.
db.close()
```

For `put()`, `get()`, and `delete()`, the passed key and the value's type must
be `bytes`. The return type of `get()` is also `bytes`. If the provided key does
not exist in the database, `None` will be returned.

More examples can be found at here: https://github.com/vidardb/PyVidarDB/tree/master/examples 

See our [wiki](https://github.com/vidardb/PyVidarDB/wiki) page for more information.
