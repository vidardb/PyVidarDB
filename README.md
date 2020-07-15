# PyVidarDB

[![Build Status](https://dev.azure.com/vidardb/PyVidarDB/_apis/build/status/vidardb.PyVidarDB?branchName=master)](https://dev.azure.com/vidardb/PyVidarDB/_build/latest?definitionId=1&branchName=master)

A simple python wrapper for VidarDB. It is built on the earlier work
of [twmht/python-rocksdb](https://github.com/twmht/python-rocksdb/tree/pybind11).

## Use PyVidarDB

PyVidarDB currently supports Python3.5, Python3.6, Python3.7, and Python3.8.

For Ubuntu users:

```bash
sudo apt-get install git python3-pip build-essential cmake
git clone --recursive https://github.com/vidardb/PyVidarDB.git
pip3 install ./PyVidarDB
```

For MacOS users:

```bash
sudo brew install git python3 cmake
git clone --recursive https://github.com/vidardb/PyVidarDB
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
db.put("key1", "value1")

# Get the value of the provided key (the return type is bytes),
# will return None if there is no such key in the database.
value = db.get("key1")
assert value == b"value1"

# 'key2' does not exist in the database. So we will get None here.
value = db.get("key2")
assert value is None

# Remove 'key1' from the database.
db.delete("key1")

# Close the database.
db.close()
```

More examples can be found at here: https://github.com/vidardb/PyVidarDB/tree/master/examples 

See our [wiki](https://github.com/vidardb/PyVidarDB/wiki) page for more information.
