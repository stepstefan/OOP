
cmake_minimum_required(VERSION 3.0.0)
project(Domaci1 VERSION 0.1.0)
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories($(CMAKE_CURRENT_SOURCE_DIR))
add_executable(test.out element.cpp logical_circuit.cpp generator.cpp circuit.cpp test.cpp)