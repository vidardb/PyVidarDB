#include <pybind11/pybind11.h>
#include <vidardb/db.h>
#include <vidardb/status.h>
#include <iterator.hpp>

using namespace vidardb;
namespace py = pybind11;

class py_DB {
 public:
  py_DB();
  void Open(const std::string &name, const Options &options);
  void Put(const py::bytes &key, const py::bytes &value);
  py::object Get(const py::bytes &key);
  void Delete(const py::bytes &key);
  void Compact();
  void Close();
  std::unique_ptr<py_Iterator> NewIterator();
  ~py_DB();

 private:
  DB *db_ptr;
};

void report_error_if_necessary(Status status);
