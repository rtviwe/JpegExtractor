add_library(jpeg_extractor component.cpp component.hpp jpeg_extractor.cpp jpeg_extractor.hpp quantization_table.hpp quantization_table.cpp)
set_property(TARGET jpeg_extractor PROPERTY CXX_STANDARD 14)