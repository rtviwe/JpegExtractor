add_executable(jpeg_extractor_test jpeg_extractor_test.cpp)
target_link_libraries(jpeg_extractor_test jpeg_extractor)
set_property(TARGET jpeg_extractor_test PROPERTY CXX_STANDARD 14)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/img1.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})