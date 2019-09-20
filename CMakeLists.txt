cmake_minimum_required(VERSION 3.13)
project(arbimath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -march=native")

find_package(GTest)

add_subdirectory(lib)
add_subdirectory(test)
