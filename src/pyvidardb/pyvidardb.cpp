#include "pyvidardb.hpp"
#include <iostream>
#include <stdexcept>

const std::string kDBHasBeenClosed("DB has been closed!");

py_DB::py_DB() : db_ptr(nullptr) {}

py_DB::~py_DB() { delete db_ptr; }

void py_DB::Close() {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  delete db_ptr;
  db_ptr = nullptr;
}

void py_DB::Open(const std::string &name, const Options &options) {
  if (db_ptr != nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  Status st = DB::Open(options, name, &db_ptr);
  report_error_if_necessary(st);
}

void py_DB::Put(const py::bytes &key, const py::bytes &value) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  std::string key_str(key);
  std::string value_str(value);
  Status st = db_ptr->Put(WriteOptions(), key_str, value_str);
  report_error_if_necessary(st);
}

py::object py_DB::Get(const py::bytes &key) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  std::string key_str(key);
  std::string value;
  ReadOptions ro;
  Status st = db_ptr->Get(ro, key_str, &value);
  if (st.IsNotFound()) {
    return py::none();
  } else {
    report_error_if_necessary(st);
  }
  return py::bytes(value);
}

void py_DB::Delete(const py::bytes &key) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  std::string key_str(key);
  Status st =
      db_ptr->Delete(WriteOptions(), db_ptr->DefaultColumnFamily(), key_str);
  report_error_if_necessary(st);
}

void py_DB::Compact() {
  Status st = db_ptr->CompactRange(CompactRangeOptions(), nullptr, nullptr);
  report_error_if_necessary(st);
}

void report_error_if_necessary(Status status) {
  if (!status.ok()) {
    throw std::runtime_error(status.ToString());
  }
}

PYBIND11_MODULE(pyvidardb, m) {
  m.doc() = "Python VidarDB API";
  init_option(m);
  init_db(m);
}
