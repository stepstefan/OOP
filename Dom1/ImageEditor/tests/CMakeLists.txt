add_executable(dynamic_array_test dynamic_array_test.cpp)

target_link_libraries(dynamic_array_test ${PROJECT_BINARY_DIR}/lib/libdynamic_array.so)

add_executable(layer_test layer_test.cpp)

target_link_libraries(layer_test ${PROJECT_BINARY_DIR}/lib/liblayer.so)
