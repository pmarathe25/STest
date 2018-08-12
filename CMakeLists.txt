cmake_minimum_required(VERSION 3.10)
include(../utils.cmake)

project(STest)
# Add install target for interface.
add_install_header(include/interfaces/STest)
# Add test executable
add_executable(test0 test/test.cpp)
target_link_libraries(test0 -flto)
enable_testing()
add_test(NAME test COMMAND ${CMAKE_BINARY_DIR}/test0)
