cmake_minimum_required(VERSION 3.1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(JpegExtractor)

add_subdirectory(jpeg_extractor)

configure_file(res/img1.jpg img1.jpg COPYONLY)
configure_file(res/img2.jpg img2.jpg COPYONLY)
configure_file(res/img3.jpg img3.jpg COPYONLY)
configure_file(res/img4.jpg img4.jpg COPYONLY)
configure_file(res/img5.jpg img5.jpg COPYONLY)