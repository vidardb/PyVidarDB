#pragma once

#include <pybind11/pybind11.h>
#include <vidardb/db.h>
#include <vidardb/options.h>
#include <vidardb/status.h>

using namespace vidardb;
namespace py = pybind11;

class py_DB {
 public:
  py_DB();
  void Open(const std::string &name, const Options &options);
  void Put(const std::string &key, const std::string &value);
  py::object Get(const std::string &key);
  void Delete(const std::string &key);
  void Close();
  ~py_DB();

 private:
  DB *db_ptr;
};

void report_error_if_necessary(Status status);
