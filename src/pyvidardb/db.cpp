#include "db.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdexcept>

namespace py = pybind11;

const std::string kDBHasBeenClosed("DB has been closed!");

const std::string kDBHasBeenOpened("DB has been opened!");

void init_db(py::module& m) {
  py::class_<py_DB>(m, "DB")
      .def(py::init<>())
      .def("open", &py_DB::Open,
           "Open the database, will create one if not exist.", py::arg("name"),
           py::arg("options") = Options())
      .def("put",
           (void (py_DB::*)(const py::bytes&, const py::bytes&)) & py_DB::Put,
           "Put a map from key to value into the database.")
      .def("put",
           (void (py_DB::*)(const py::bytes&, const std::vector<py::bytes>&)) &
               py_DB::Put,
           "Put a map from key to multiple values into the database.")
      .def("get", &py_DB::Get,
           "Get the value of the provided key, will return None if there is no "
           "such key in the database.")
      .def("delete", &py_DB::Delete, "Remove the key from the database.")
      .def("compact", &py_DB::Compact, "Compact the data manually.")
      .def("iter", &py_DB::NewIterator, "Return an iterator from the database.")
      .def("close", &py_DB::Close, "Close the database.");
}

py_DB::py_DB() : db_ptr(nullptr) {}

py_DB::~py_DB() {
  if (db_ptr) {
    for (auto i : iters) {
      delete i.py_iter;
      i.py_iter = nullptr;
    }
  }
  delete db_ptr;
}

void py_DB::Close() {
  for (auto i : iters) {
    delete i.py_iter;
    i.py_iter = nullptr;
  }
  delete db_ptr;
  db_ptr = nullptr;
}

py_Iterator py_DB::NewIterator() {
  ReadOptions ro;
  iters.push_back(py_Iterator(db_ptr->NewIterator(ro), opts.splitter));
  return iters.back();
}

void py_DB::Open(const std::string& name, const Options& options) {
  if (db_ptr != nullptr) {
    throw std::invalid_argument(kDBHasBeenOpened);
  }
  opts = options;
  opts.splitter.reset(NewEncodingSplitter());
  Status st = DB::Open(opts, name, &db_ptr);
  report_error_if_necessary(st);
}

void py_DB::Put(const py::bytes& key, const py::bytes& value) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  std::string key_str(key);
  std::vector<std::string> str_val{std::string(value)};
  std::vector<Slice> slice_val(str_val.begin(), str_val.end());
  Status st =
      db_ptr->Put(WriteOptions(), key_str, opts.splitter->Stitch(slice_val));
  report_error_if_necessary(st);
}

void py_DB::Put(const py::bytes& key, const std::vector<py::bytes>& values) {
  if (db_ptr == nullptr) {
    throw std::invalid_argument(kDBHasBeenClosed);
  }
  std::string key_str(key);
  std::vector<std::string> str_vals;
  for (auto value : values) {
    str_vals.push_back(std::string(value));
  }
  std::vector<Slice> slice_vals(str_vals.begin(), str_vals.end());
  Status st =
      db_ptr->Put(WriteOptions(), key_str, opts.splitter->Stitch(slice_vals));
  report_error_if_necessary(st);
}

py::object py_DB::Get(const py::bytes& key) {
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
  std::vector<Slice> vals(opts.splitter->Split(value));
  std::vector<std::string> str_vals;
  for (auto val : vals) {
    str_vals.push_back(val.ToString());
  }
  std::vector<py::bytes> bytes_vals(str_vals.begin(), str_vals.end());
  return py::cast(bytes_vals);
}

void py_DB::Delete(const py::bytes& key) {
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
