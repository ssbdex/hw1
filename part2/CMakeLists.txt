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