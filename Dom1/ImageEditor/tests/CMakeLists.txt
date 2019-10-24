include_directories($(ImageEditor_SOURCE_DIR)/include)

add_executable(dynamic_array_test.out dynamic_array_test.cpp)
target_link_libraries(dynamic_array_test.out ${PROJECT_SOURCE_DIR}/Release/src/liblibrary.so)