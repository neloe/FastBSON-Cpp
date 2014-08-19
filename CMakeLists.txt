project(bson)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated-register ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wno-deprecated-register -O0 --coverage ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)

find_package(BISON 3 REQUIRED)
find_package(FLEX)
BISON_TARGET(jsonParser json/json.yy ${CMAKE_CURRENT_BINARY_DIR}/json.tab.cpp)
FLEX_TARGET(jsonLexer json/json.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(jsonLexer jsonParser)

include_directories(json ${CMAKE_CURRENT_BINARY_DIR})

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
json/jsonloader.cpp
element.cpp
)
add_library(fastbson SHARED ${bson_src} ${BISON_jsonParser_OUTPUTS} ${FLEX_jsonLexer_OUTPUTS})

add_subdirectory(tests)

include(CodeCoverage)
setup_target_for_coverage(${PROJECT_NAME}_coverage bsontests coverage)
setup_target_for_coverage_cobertura(${PROJECT_NAME}_cobertura bsontests coverage --gtest_output=xml:coverage.junit.xml)