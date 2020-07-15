#include "pyvidardb.hpp"

PYBIND11_MODULE(pyvidardb, m) {
  m.doc() = "Python VidarDB API";
  init_option(m);
  init_db(m);
}
