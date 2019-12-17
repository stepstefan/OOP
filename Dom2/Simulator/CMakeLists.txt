
cmake_minimum_required(VERSION 3.0.0)
project(Domaci1 VERSION 0.1.0)
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories($(CMAKE_CURRENT_SOURCE_DIR))
include_directories($(CMAKE_CURRENT_COURCE_DIR)/include/)
add_executable(test.out src/element.cpp src/logical_circuit.cpp src/generator.cpp src/circuit.cpp src/reader.cpp src/writer.cpp src/simulator.cpp src/test.cpp)

add_library(Simulator src/element.cpp ./src/logical_circuit.cpp src/generator.cpp src/circuit.cpp src/reader.cpp src/writer.cpp src/simulator.cpp)