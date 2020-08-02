#include "iterator.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void init_iterator(py::module& m) {
  py::class_<py_Iterator>(m, "py_Iterator")
      .def(py::init<>())
      .def("valid", &py_Iterator::Valid)
      .def("next", &py_Iterator::Next)
      .def("key", &py_Iterator::key)
      .def("value", &py_Iterator::value);
}

py_Iterator::py_Iterator(Iterator* iter, std::shared_ptr<Splitter> splitter) {
  py_iter = iter;
  py_splitter = splitter;
  py_iter->SeekToFirst();
}

py_Iterator::~py_Iterator() {}

void py_Iterator::Next() { py_iter->Next(); }

bool py_Iterator::Valid() { return py_iter->Valid(); }

py::bytes py_Iterator::key() { return py::bytes(py_iter->key().ToString()); }

std::vector<py::bytes> py_Iterator::value() {
  std::vector<Slice> vals(py_splitter->Split(py_iter->value()));
  std::vector<std::string> str_vals;
  for (auto val : vals) {
    str_vals.push_back(val.ToString());
  }
  std::vector<py::bytes> bytes_vals(str_vals.begin(), str_vals.end());
  return bytes_vals;
}
