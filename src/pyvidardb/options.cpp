#include <pybind11/pybind11.h>
#include "pyvidardb.hpp"

namespace py = pybind11;

void init_option(py::module &m) {
  py::class_<DBOptions, std::unique_ptr<DBOptions>>(m, "DBOptions")
      .def(py::init<>())
      .def_readwrite("max_background_compactions",
                     &vidardb::DBOptions::max_background_compactions);

  py::class_<vidardb::ColumnFamilyOptions>(m, "ColumnFamilyOptions")
      .def(py::init<>())
      .def_readwrite("write_buffer_size",
                     &vidardb::ColumnFamilyOptions::write_buffer_size);

  py::class_<vidardb::Options, vidardb::DBOptions,
             vidardb::ColumnFamilyOptions>(m, "Options")
      .def(py::init<>());
}
