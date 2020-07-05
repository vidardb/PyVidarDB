#include "pyvidardb.hpp"
#include <iostream>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <stdexcept>

py_DB::py_DB() : db_ptr(nullptr) {}

py_DB::~py_DB() {
  if (db_ptr != nullptr) {
    delete db_ptr;
  }
}

void py_DB::Close() {
  if (db_ptr == nullptr) {
    throw std::invalid_argument("db has been closed");
  }
  delete db_ptr;
  db_ptr = nullptr;
}

Status py_DB::Open(const Options &options, const std::string &name) {
  if (db_ptr != nullptr) {
    throw std::invalid_argument("db has been opened");
  }
  Status st = DB::Open(options, name, &db_ptr);
  return st;
}

Status py_DB::Put(const std::string &key, const std::string &value) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument("db has been closed");
  }
  return db_ptr->Put(WriteOptions(), key, value);
}

std::string py_DB::Get(const std::string &key) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument("db has been closed");
  }
  std::string value;
  ReadOptions ro;
  db_ptr->Get(ro, key, &value);
  return value;
}

Status py_DB::Delete(const std::string &key) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument("db has been closed");
  }
  return db_ptr->Delete(WriteOptions(), db_ptr->DefaultColumnFamily(), key);
}

void init_db(py::module &);

void init_option(py::module &);

void init_slice(py::module &);

void init_status(py::module &);

PYBIND11_MODULE(pyvidardb, m) {
  m.doc() = "Python VidarDB API";
  init_db(m);
  init_option(m);
  init_slice(m);
  init_status(m);
}
