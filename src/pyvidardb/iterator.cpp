#include "iterator.hpp"
#include <pybind11/pybind11.h>
#include "pyvidardb.hpp"

namespace py = pybind11;

void init_iterator(py::module& m) {
  py::class_<py_Iterator>(m, "py_Iterator")
      .def(py::init<>())
      .def("seek", &py_Iterator::SeekToFirst)
      .def("valid", &py_Iterator::Valid)
      .def("next", &py_Iterator::Next)
      .def("key", &py_Iterator::key)
      .def("value", &py_Iterator::value);
}

py_Iterator::py_Iterator(Iterator* iter) {
  py_iter = iter;
}

py_Iterator::~py_Iterator() {/*printf("\n!!!\n");*/}

void py_Iterator::Next() { py_iter->Next(); }

bool py_Iterator::Valid() { return py_iter->Valid(); }

py::bytes py_Iterator::key() { return py::bytes(py_iter->key().ToString()); }

py::bytes py_Iterator::value() {
  return py::bytes(py_iter->value().ToString());
}

void py_Iterator::SeekToFirst() { py_iter->SeekToFirst(); }
