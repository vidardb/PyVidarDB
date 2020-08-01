#include <pybind11/pybind11.h>
#include <vidardb/db.h>

using namespace vidardb;
namespace py = pybind11;

class py_Iterator {
 public:
  py_Iterator() {}
  py_Iterator(Iterator* iter, std::shared_ptr<Splitter> splitter);
  ~py_Iterator();
  void Next();
  bool Valid();
  py::bytes key();
  std::vector<py::bytes> value();

  Iterator* py_iter;
  std::shared_ptr<Splitter> py_splitter;
};
