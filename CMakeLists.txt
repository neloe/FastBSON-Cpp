project(bson)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")

set(bson_src
template_spec/binary.cpp
template_spec/chararrs.cpp
template_spec/floats.cpp
template_spec/jsscope.cpp
template_spec/strings.cpp
template_spec/voids.cpp
template_spec/bools.cpp 
template_spec/document.cpp
template_spec/ints.cpp
template_spec/pairs.cpp
template_spec/vectors.cpp
element.cpp
)

add_library(fastbson SHARED ${bson_src})

#add_executable(bson_runner main.cpp)

add_subdirectory(tests)