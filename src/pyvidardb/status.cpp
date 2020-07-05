#include "pyvidardb.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_status(py::module &m) {
  py::class_<vidardb::Status> status(m, "Status");

  status.def(py::init<>())
      .def("ok", &Status::ok)
      .def("is_not_found", &Status::IsNotFound)
      .def("is_corruption", &Status::IsCorruption)
      .def("is_not_supported", &Status::IsNotSupported)
      .def("is_invalid_argument", &Status::IsInvalidArgument)
      .def("is_io_error", &Status::IsIOError)
      .def("is_in_complete", &Status::IsIncomplete)
      .def("is_shutdown_in_progress", &Status::IsShutdownInProgress)
      .def("is_time_out", &Status::IsTimedOut)
      .def("is_aborted", &Status::IsAborted)
      .def("is_busy", &Status::IsBusy)
      .def("is_expired", &Status::IsExpired)
      .def("is_try_again", &Status::IsTryAgain)
      .def("to_string", &Status::ToString);
}
