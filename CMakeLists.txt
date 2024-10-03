cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0074 NEW)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})


# Find Boost
set(Boost_DEBUG ON)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Check if Boost was found
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

target_link_libraries(test_version ${Boost_LIBRARIES} helloworld)

set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(helloworld_cli PRIVATE helloworld)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

include(CPack)  # Ensure this is called only once

if (WIN32)
    set(CPACK_GENERATOR NSIS)
    set(CPACK_PACKAGE_NAME "HelloWorld-${CMAKE_PROJECT_VERSION}-windows")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name")
    set(CPACK_PACKAGE_FILE_NAME "helloworld-${CMAKE_PROJECT_VERSION}-Linux")
endif()

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_NAME "helloworld")

include(CPack)

set(CPACK_PACKAGE_CONTACT example@example.com)

enable_testing()

add_test(test_version test_version)