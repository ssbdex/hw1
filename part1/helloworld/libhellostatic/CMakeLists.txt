# libhellostatic cmake file
project(libhellostatic VERSION 1.2)

configure_file(version.h.in "${CMAKE_CURRENT_SOURCE_DIR}/version.h")

add_library(libhellostatic STATIC hello_static.cpp)

append_warn_flags(libhellostatic)