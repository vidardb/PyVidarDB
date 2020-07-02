#pragma once

#include <pybind11/pybind11.h>
#include <vidardb/cache.h>
#include <vidardb/db.h>
#include <vidardb/iterator.h>
#include <vidardb/options.h>
#include <vidardb/slice.h>
#include <vidardb/snapshot.h>
#include <vidardb/status.h>
#include <vidardb/table.h>
#include <vidardb/write_batch.h>

using namespace vidardb;
namespace py = pybind11;

class Blob {
public:
  Status status;
  std::string data;
  py::bytes get_data() { return py::bytes(data); }
};

class py_DB {
public:
  py_DB();
  Status Open(const Options &options, const std::string &name);
  Status Put(const WriteOptions &options, const std::string &key,
             const std::string &value);
  std::unique_ptr<Blob> Get(ReadOptions &options, const std::string &key);
  Status Delete(const WriteOptions &options, const std::string &key);
  void Close();
  ~py_DB();

private:
  DB *db_ptr;
};
