# PyVidarDB

[![Build Status](https://dev.azure.com/vidardb/PyVidarDB/_apis/build/status/vidardb.PyVidarDB?branchName=master)](https://dev.azure.com/vidardb/PyVidarDB/_build/latest?definitionId=1&branchName=master)

A simple python wrapper for VidarDB. It is built on the earlier work
of [twmht/python-rocksdb](https://github.com/twmht/python-rocksdb/tree/pybind11).

## Use PyVidarDB

PyVidarDB currently supports Python3.5, Python3.6, Python3.7, and Python3.8.

For Ubuntu users:

```bash
sudo apt-get install git python3-pip build-essential cmake libsnappy-dev
git clone --recursive https://github.com/vidardb/PyVidarDB.git
pip install ./PyVidarDB
```

## Usage

```python
import pyvidardb

db = pyvidardb.DB()

opts = pyvidardb.Options()

# Open the database, will create one if not exist.
db.open("/path/to/db", opts)

# Put a map from 'key1' to 'value1' into the database.
db.put("key1", "value1")

# Get the value of the provided key, will return None if there is no such key in the database.
value = db.get("key1")
assert value == "value1"

key_not_exist = db.get("key2")
assert key_not_exist is None

# Remove 'key1' from the database.
db.delete("key1")

# Close the database.
db.close()
```
