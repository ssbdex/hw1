#cmake file for ip_filter
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

function(append_warn_flags target)
    if (MSVC)
        target_compile_options( ${target} PRIVATE /W4)
    else ()
       target_compile_options( ${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif() 
endfunction()

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(ip_filter ip_filter.cpp)

configure_file(version.h.in  version.h)
target_include_directories(ip_filter PRIVATE 
    "${CMAKE_CURRENT_BINARY_DIR}" 
)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

append_warn_flags(ip_filter)

install(TARGETS ip_filter
RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ssbdex@yandex.ru)

include(CPack)

if(UNIX)
    enable_testing()
#    find_program(BIN_CAT "cat")
#    find_program(BIN_MD5SUM "md5sum")
    add_test(NAME General COMMAND sh -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/ip_filter.tsv | ${CMAKE_BINARY_DIR}/ip_filter| md5sum")
    set_tests_properties(General PROPERTIES PASS_REGULAR_EXPRESSION "24e7a7b2270daee89c64d3ca5fb3da1a  -")
  
    add_test(NAME EmptyStrings COMMAND sh -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty_strings.tsv | ${CMAKE_BINARY_DIR}/ip_filter | md5sum")
    set_tests_properties(EmptyStrings PROPERTIES PASS_REGULAR_EXPRESSION "24e7a7b2270daee89c64d3ca5fb3da1a  -")

    add_test(NAME ValidationCheck_1 COMMAND sh -c "${CMAKE_BINARY_DIR}/ip_filter < ${CMAKE_CURRENT_SOURCE_DIR}/tests/invalid_ip_line_1.tsv")
    set_tests_properties(ValidationCheck_1 PROPERTIES PASS_REGULAR_EXPRESSION "on line 1")

    add_test(NAME ValidationCheck_2 COMMAND sh -c "${CMAKE_BINARY_DIR}/ip_filter < ${CMAKE_CURRENT_SOURCE_DIR}/tests/invalid_ip_line_3.tsv")
    set_tests_properties(ValidationCheck_2 PROPERTIES PASS_REGULAR_EXPRESSION "on line 3")

    add_test(NAME ValidationCheck_3 COMMAND sh -c "${CMAKE_BINARY_DIR}/ip_filter < ${CMAKE_CURRENT_SOURCE_DIR}/tests/invalid_ip_line_14.tsv")
    set_tests_properties(ValidationCheck_3 PROPERTIES PASS_REGULAR_EXPRESSION "on line 14")


endif()