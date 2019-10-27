cmake_minimum_required(VERSION 3.0.0)
project(ImageEditor VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
#create dir for storing libraries in case it gets deleted and configuration is not run again
add_custom_target(build-time-make-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src)
install(TARGETS dynamic_array DESTINATION ${PROJECT_SOURCE_DIR}/lib)

link_directories(Release/lib)

add_subdirectory(tests)

add_dependencies(dynamic_array_test dynamic_array)
add_dependencies(layer dynamic_array)
add_dependencies(layer_test layer)
