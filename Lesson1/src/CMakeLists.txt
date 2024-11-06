
add_library(versionLib lib.cpp)

target_include_directories(versionLib PRIVATE "${CMAKE_BINARY_DIR}")

add_executable(helloworld_cli main.cpp)
target_link_libraries(helloworld_cli versionLib)
