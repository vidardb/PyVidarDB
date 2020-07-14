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
pip install ./PyVidarDB
```

## Usage

```python
import pyvidardb

db = pyvidardb.DB()

# opts are optional. This step can be skipped.
opts = pyvidardb.Options()
# Set the write buffer size to 1G. The default size in VidarDB is 512M.
# This step can also be skipped.
opts.write_buffer_size = 1024 * 1024 * 1024

# Open the database, will create one if not exist.
# If you want to run VidarDB with the default options, simply write:
# db.open("./hello_world")
db.open("./hello_world", opts)

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
