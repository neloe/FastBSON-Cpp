cmake_minimum_required (VERSION 2.8)
project(mtproxy_unit_tests)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#enable c++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

#add gtest
add_subdirectory(gtest-1.7.0)

if (TARGET gtest_main)
include_directories(${gtest_SOURCE_DIR}/include)
endif()

#the actual source directory
include_directories(..)

#add files with new test here
set (test_sources
test_encoding.cpp
test_decoding.cpp
test_json.cpp
test_elm.cpp
test_strrep.cpp
test_exception_text.cpp
)

add_executable(bsontests ${test_sources})
target_link_libraries(bsontests fastbson gtest_main)

#add_custom_command(TARGET tests 
#                   POST_BUILD
#                   COMMAND ./tests)