add_library(dynamic_array SHARED dynamic_array.cpp)
add_library(layer SHARED layer.cpp dynamic_array.cpp)
add_library(ImageEditor SHARED ImageEditor.cpp layer.cpp dynamic_array.cpp)
