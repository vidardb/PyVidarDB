cmake_minimum_required(VERSION 2.8.12)
project(pyvidardb)

SET(SOURCE_DIR "src/pyvidardb")
include_directories(${SOURCE_DIR})
include_directories(dependencies/pybind11)
add_subdirectory(dependencies/pybind11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")

include_directories(dependencies/vidardb)
include_directories(dependencies/vidardb/include)
add_subdirectory(dependencies/vidardb)

pybind11_add_module(pyvidardb ${SOURCE_DIR}/pyvidardb.cpp ${SOURCE_DIR}/db.cpp ${SOURCE_DIR}/options.cpp)
target_link_libraries(pyvidardb PRIVATE vidardb)
