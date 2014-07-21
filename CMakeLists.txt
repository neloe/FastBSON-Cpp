project(bson)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")

add_executable(bson main.cpp)

install(TARGETS bson RUNTIME DESTINATION bin)
