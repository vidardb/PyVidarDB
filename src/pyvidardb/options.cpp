#include "pyvidardb.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_option(py::module &m) {
  py::class_<DBOptions, std::unique_ptr<DBOptions>>(m, "DBOptions")
      .def(py::init<>())
      .def("IncreaseParallelism", &vidardb::DBOptions::IncreaseParallelism,
           py::arg("total_threads") = 16,
           py::return_value_policy::reference_internal)
      .def_readwrite("create_if_missing",
                     &vidardb::DBOptions::create_if_missing)
      .def_readwrite("error_if_exists", &vidardb::DBOptions::error_if_exists);

  py::class_<vidardb::ColumnFamilyOptions>(m, "ColumnFamilyOptions")
      .def(py::init<>())
      .def("OptimizeLevelStyleCompaction",
           &vidardb::ColumnFamilyOptions::OptimizeLevelStyleCompaction,
           py::arg("memtable_memory_budget") = 512L * 1024L * 1024L,
           py::return_value_policy::reference_internal);

  py::class_<vidardb::Options, vidardb::DBOptions,
             vidardb::ColumnFamilyOptions>(m, "Options")
      .def(py::init<>());

  py::class_<vidardb::WriteOptions>(m, "WriteOptions").def(py::init<>());

  py::class_<vidardb::ReadOptions>(m, "ReadOptions").def(py::init<>());
}
