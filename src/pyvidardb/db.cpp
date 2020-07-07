#include "pyvidardb.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_db(py::module &m) {
  py::class_<py_DB>(m, "DB")
      .def(py::init<>())
      .def("open", &py_DB::Open,
           "Open the database, will create one if not exist.")
      .def("put", &py_DB::Put,
           "Put a map from 'key' to 'value' into the database.")
      .def("get", &py_DB::Get,
           "Get the value of the provided key, will return None if there is no "
           "such key in the database.")
      .def("delete", &py_DB::Delete, "Remove the 'key' from the database.")
      .def("close", &py_DB::Close, "Close the database.");
}
