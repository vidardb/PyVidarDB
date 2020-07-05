#include "pyvidardb.hpp"
#include <iostream>
#include <stdexcept>

const std::string kDBHasBeenClosed("DB has been closed!");

py_DB::py_DB() : db_ptr(nullptr) {}

py_DB::~py_DB() {
  if (db_ptr != nullptr) {
    delete db_ptr;
  }
}

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

void py_DB::Put(const std::string &key, const std::string &value) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  Status st = db_ptr->Put(WriteOptions(), key, value);
  report_error_if_necessary(st);
}

py::object py_DB::Get(const std::string &key) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  std::string value;
  ReadOptions ro;
  Status st = db_ptr->Get(ro, key, &value);
  if (st.IsNotFound()) {
    return py::none();
  } else {
    report_error_if_necessary(st);
  }
  return py::str(value);
}

void py_DB::Delete(const std::string &key) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  Status st =
      db_ptr->Delete(WriteOptions(), db_ptr->DefaultColumnFamily(), key);
  report_error_if_necessary(st);
}

void report_error_if_necessary(Status status) {
  if (!status.ok()) {
    throw std::runtime_error(status.ToString());
  }
}

void init_db(py::module &);

void init_option(py::module &);

PYBIND11_MODULE(pyvidardb, m) {
  m.doc() = "Python VidarDB API";
  init_db(m);
  init_option(m);
}
