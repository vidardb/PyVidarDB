#include "pyvidardb.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_db(py::module &m) {
  py::class_<py_DB>(m, "DB")
      .def(py::init<>())
      .def("open",
           (Status(py_DB::*)(const Options &options, const std::string &name)) &
               py_DB::Open)
      .def("put", (Status(py_DB::*)(const WriteOptions &, const std::string &,
                                    const std::string &)) &
                      py_DB::Put)
      .def("get", (std::unique_ptr<Blob>(py_DB::*)(ReadOptions & options,
                                                   const std::string &)) &
                      py_DB::Get)
      .def("delete", (Status(py_DB::*)(const WriteOptions &options,
                                       const std::string &key)) &
                         py_DB::Delete)
      .def("close", &py_DB::Close);
}
