cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

project(ip_filter
  LANGUAGES CXX
  VERSION 0.0.${PATCH_VERSION}
)
add_custom_target(copy_tsv)
add_custom_command(
        TARGET copy_tsv PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/ip_filter.tsv
                ${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv)

set(CMAKE_BUILD_TYPE Debug)


include_directories(${CMAKE_BINARY_DIR})

add_executable(ip_filter ip_filter.cpp)
install(TARGETS ip_filter DESTINATION bin)

# add_custom_command(
#     TARGET ${PROJECT_NAME} POST_BUILD 
#     COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/ip_filter.tsv" "${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv"
#     COMMENT "Copying ${copy_file_name} to build directory"
# )
install(FILES ip_filter.tsv DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
