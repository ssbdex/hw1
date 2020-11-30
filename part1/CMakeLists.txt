# helloworld general cmake file
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(append_warn_flags target)
    if (MSVC)
        target_compile_options( ${target} PRIVATE /W4)
    else ()
       target_compile_options( ${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif() 
endfunction()


add_subdirectory(libhellostatic)
add_subdirectory(libhelloshared)


project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
add_subdirectory(source)
add_executable(helloworld "${SOURCE_LIST}")
configure_file(source/version.h.in  version.h)
target_include_directories(helloworld PRIVATE 
    "${CMAKE_CURRENT_BINARY_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}" 
)
target_link_libraries(helloworld PRIVATE libhellostatic libhelloshared)

append_warn_flags(helloworld)
# set_target_properties(helloworld PROPERTIES
#     CXX_STANDARD 14
#     CXX_STANDARD_REQUIRED ON 
# )




add_subdirectory(test)

install(TARGETS helloworld
RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ssbdex@yandes.ru)

include(CPack)