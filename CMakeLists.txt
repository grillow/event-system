cmake_minimum_required(VERSION 3.19)
project(GES VERSION 1.0.0)

set(tool_dest "bin")
set(include_dest "include/${PROJECT_NAME}")
set(source_dest "src")
set(main_lib_dest "lib/${PROJECT_NAME}")

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)

