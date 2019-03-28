cmake_minimum_required(VERSION 2.8)

project(Task2)

execute_process(COMMAND python3 preparing.py WORKING_DIRECTORY A)

set(SOURCES_MAIN C/main.cpp)

include_directories("${PROJECT_SOURCE_DIR}")
 
add_executable(Task2 ${SOURCES_MAIN})

add_subdirectory(B)

target_link_libraries(Task2 library)
