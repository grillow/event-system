cmake_minimum_required(VERSION 3.19)
project(GES VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")

set(tool_dest "bin")
set(include_dest "include/${PROJECT_NAME}")
set(source_dest "src")
set(main_lib_dest "lib/${PROJECT_NAME}")

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)

