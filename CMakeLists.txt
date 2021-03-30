cmake_minimum_required(VERSION 3.19)
project(GES VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")

set(TOOL_DIRECTORY        "${CMAKE_SOURCE_DIR}/bin")
set(EXAMPLE_BIN_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(TEST_BIN_DIRECTORY    "${CMAKE_SOURCE_DIR}/bin")
set(INCLUDE_DIRECTORY     "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}")
set(SOURCE_DIRECTORY      "${CMAKE_SOURCE_DIR}/src")
set(LIB_BIN_DIRECTORY     "${CMAKE_SOURCE_DIR}/lib/${PROJECT_NAME}")


add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(test)

