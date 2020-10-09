project(libhelloshared VERSION 1.0.1)
add_library(libhelloshared SHARED hello_shared.cpp)
configure_file(version.h.in version.h)
target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")