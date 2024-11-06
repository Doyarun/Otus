add_executable(test_version test_version.cpp)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIR}"
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    lib
)

add_test(test_version test_version)
