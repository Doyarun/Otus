
add_library(versionLib lib.cpp)

target_include_directories(versionLib PRIVATE "${CMAKE_BINARY_DIR}")

add_executable(HelloWorld_cli main.cpp)
target_link_libraries(HelloWorld_cli versionLib)
