# PyVidarDB

[![Build Status](https://dev.azure.com/vidardb/PyVidarDB/_apis/build/status/vidardb.PyVidarDB?branchName=master)](https://dev.azure.com/vidardb/PyVidarDB/_build/latest?definitionId=1&branchName=master)

A simple python wrapper for VidarDB. It is built on the earlier work
of [twmht/python-rocksdb](https://github.com/twmht/python-rocksdb/tree/pybind11).

## Use PyVidarDB

Tested with Python3.6 and Ubuntu 18.04.

```bash
sudo apt-get install git python3-pip build-essential cmake libsnappy-dev
git clone --recursive https://github.com/vidardb/PyVidarDB.git
pip install ./PyVidarDB
```

## Usage

See [simple_example.py](examples/simple_example.py) for the basic usage.
