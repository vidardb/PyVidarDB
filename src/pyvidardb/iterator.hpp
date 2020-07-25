#include <pybind11/pybind11.h>
#include <vidardb/iterator.h>

using namespace vidardb;
namespace py = pybind11;

class py_Iterator {
 public:
  py_Iterator(Iterator* iter);
  ~py_Iterator();
  void Next();
  bool Valid();
  void SeekToFirst();
  py::bytes key();
  py::bytes value();

 private:
  std::unique_ptr<Iterator> py_iter;
};
