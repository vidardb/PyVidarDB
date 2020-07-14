#include "pyvidardb.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

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
