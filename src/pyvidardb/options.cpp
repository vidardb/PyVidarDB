#include <pybind11/pybind11.h>
#include <vidardb/options.h>
#include "pyvidardb.hpp"

using namespace vidardb;
namespace py = pybind11;

void init_option(py::module &m) {
  py::class_<DBOptions, std::unique_ptr<DBOptions>>(m, "DBOptions")
      .def(py::init<>())
      .def_readwrite("max_background_parallelism",
                     &DBOptions::max_background_compactions);

  py::class_<ColumnFamilyOptions>(m, "ColumnFamilyOptions")
      .def(py::init<>())
      .def_readwrite("ram_size", &ColumnFamilyOptions::write_buffer_size);

  py::class_<Options, DBOptions, ColumnFamilyOptions>(m, "Options")
      .def(py::init<>());
}
