add_executable(jpeg_extractor_test jpeg_extractor_test.cpp)
target_link_libraries(jpeg_extractor_test jpeg_extractor)
set_property(TARGET jpeg_extractor_test PROPERTY CXX_STANDARD 14)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/img1.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/img2.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/img3.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/img4.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/answers4.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)