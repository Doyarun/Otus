cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

project(helloworld
  LANGUAGES CXX
  VERSION 0.0.${PATCH_VERSION}
)

set(CMAKE_BUILD_TYPE Debug)

configure_file(version.h.in version.h)
include_directories(${CMAKE_BINARY_DIR})

option(BUILD_TESTS "Build unittests" ON)

add_subdirectory(src)

if(BUILD_TESTS)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS helloworld_cli DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
