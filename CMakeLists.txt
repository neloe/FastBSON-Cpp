project(bson)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")

add_executable(bson main.cpp)

add_subdirectory(tests)