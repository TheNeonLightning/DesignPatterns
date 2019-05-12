cmake_minimum_required(VERSION 3.13)
project(untitled8)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES untitled8 main.cpp) #для использования unit-test'ов main.cpp -> test.cpp
add_executable(test ${SOURCE_FILES})
target_link_libraries(test gtest gtest_main)