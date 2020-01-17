cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

add_library(Proj3 proj3.cpp proj3.h)
add_executable(sortTest proj3_test.cpp)

target_link_libraries(sortTest Proj3)