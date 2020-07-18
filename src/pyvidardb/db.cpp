#include "db.hpp"

#include <pybind11/pybind11.h>
#include <iostream>
#include <stdexcept>

namespace py = pybind11;

const std::string kDBHasBeenClosed("DB has been closed!");

const std::string kDBHasBeenOpened("DB has been opened!");

void init_db(py::module &m) {
  py::class_<py_DB>(m, "DB")
      .def(py::init<>())
      .def("open", &py_DB::Open,
           "Open the database, will create one if not exist.", py::arg("name"),
           py::arg("options") = Options())
      .def("put", &py_DB::Put,
           "Put a map from 'key' to 'value' into the database.")
      .def("get", &py_DB::Get,
           "Get the value of the provided key, will return None if there is no "
           "such key in the database.")
      .def("delete", &py_DB::Delete, "Remove the 'key' from the database.")
      .def("compact", &py_DB::Compact, "Compact the data manually.")
      .def("close", &py_DB::Close, "Close the database.");
}

py_DB::py_DB() : db_ptr(nullptr) {}

py_DB::~py_DB() { delete db_ptr; }

void py_DB::Close() {
  delete db_ptr;
  db_ptr = nullptr;
}

void py_DB::Open(const std::string &name, const Options &options) {
  if (db_ptr != nullptr) {
    throw std::invalid_argument(kDBHasBeenOpened);
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
