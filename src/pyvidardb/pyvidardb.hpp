#pragma once

#include <pybind11/pybind11.h>
#include <vidardb/db.h>
#include <vidardb/options.h>
#include <vidardb/slice.h>
#include <vidardb/status.h>

using namespace vidardb;
namespace py = pybind11;

class py_DB {
public:
  py_DB();
  Status Open(const Options &options, const std::string &name);
  Status Put(const std::string &key, const std::string &value);
  std::string Get(const std::string &key);
  Status Delete(const std::string &key);
  void Close();
  ~py_DB();

private:
  DB *db_ptr;
};
