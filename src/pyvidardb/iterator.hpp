#include <pybind11/pybind11.h>
#include <vidardb/db.h>
#include <vidardb/iterator.h>
using namespace vidardb;

namespace py = pybind11;

class py_Iterator {
 public:
  py_Iterator() {}
  py_Iterator(Iterator* iter);
  ~py_Iterator();
  void Next();
  bool Valid();
  py::bytes key();
  py::bytes value();

  Iterator* py_iter;
};
