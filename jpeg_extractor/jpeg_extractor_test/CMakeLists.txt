add_executable(jpeg_extractor_test jpeg_extractor_test.cpp img1.jpg img2.jpg img3.jpg img4.jpg img5.jpg)
target_link_libraries(jpeg_extractor_test jpeg_extractor)
set(RESOURCE_FILES img1.jpg img2.jpg img3.jpg img4.jpg img5.jpg)
set_property(TARGET jpeg_extractor_test PROPERTY CXX_STANDARD 14)