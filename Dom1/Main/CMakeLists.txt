cmake_minimum_required(VERSION 3.0.0)
project(Domaci1 VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories($(CMAKE_CURRENT_SOURCE_DIR))
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ImageEditor/)

add_executable(Domaci1 Main.cpp)

# target_link_libraries(Domaci1 ${CMAKE_CURRENT_SOURCE_DIR}/../ImageEditor/Release/lib/libdynamic_array.so)
# target_link_libraries(Domaci1 ${CMAKE_CURRENT_SOURCE_DIR}/../ImageEditor/Release/lib/liblayer.so)
target_link_libraries(Domaci1 ${CMAKE_CURRENT_SOURCE_DIR}/../ImageEditor/Release/lib/libImageEditor.so)
target_link_libraries(Domaci1 ${CMAKE_CURRENT_SOURCE_DIR}/test.o)