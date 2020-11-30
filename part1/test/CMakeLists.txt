# CMake file for tests

add_executable(test_version test_version.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set_target_properties(test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    libhellostatic
)

enable_testing()
add_test(test_libhellostatic test_version)