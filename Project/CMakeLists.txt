cmake_minimum_required(VERSION 3.0.0)
project(Simulator)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
    Compiler/include
    Machine/include
    Utils/include
    lib/source/include/concepts
    lib/source/include/tss
    lib/source/include/util
)

add_executable(main
    main.cpp
    Compiler/src/compiler.cpp
    Compiler/src/expression.cpp
    Compiler/src/program.cpp
    Machine/src/machine.cpp
    Machine/src/operation.cpp
    Machine/src/memory.cpp
    Machine/src/logger.cpp
    Utils/src/config.cpp
    Utils/src/util.cpp)
target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSimulationEngine.so)