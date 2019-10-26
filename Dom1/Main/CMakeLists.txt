cmake_minimum_required(VERSION 3.0.0)
project(Domaci1 VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)

include_directories($(CMAKE_CURRENT_SOURCE_DIR))

add_executable(Domaci1 Main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
