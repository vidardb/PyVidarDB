#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_db(py::module&);

void init_option(py::module&);

void init_iterator(py::module&);
