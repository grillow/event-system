cmake_minimum_required(VERSION 3.19)
project(GES VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")

set(tool_dest "${CMAKE_SOURCE_DIR}/bin")
set(include_dest "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}")
set(source_dest "${CMAKE_SOURCE_DIR}/src")
set(main_lib_dest "${CMAKE_SOURCE_DIR}/lib/${PROJECT_NAME}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")


add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(test)

