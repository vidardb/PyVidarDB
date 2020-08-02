#include <pybind11/pybind11.h>
#include <vidardb/db.h>
#include <iterator.hpp>

using namespace vidardb;
namespace py = pybind11;

class py_DB {
 public:
  py_DB();
  void Open(const std::string& name, const Options& options);
  void Put(const py::bytes& key, const py::bytes& value);
  void Put(const py::bytes& key, const std::vector<py::bytes>& values);
  py::object Get(const py::bytes& key);
  void Delete(const py::bytes& key);
  void Compact();
  void Close();
  py_Iterator NewIterator();
  ~py_DB();

 private:
  DB* db_ptr;
  std::vector<py_Iterator> iters;
  Options opts;
};

void report_error_if_necessary(Status status);
