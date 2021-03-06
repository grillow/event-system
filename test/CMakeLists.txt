project(Test)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# GES_LIBRARY
set(GES_LIBRARY_DIRECTORY ${CMAKE_SOURCE_DIR})
add_library(GES_LIBRARY SHARED IMPORTED)
set_target_properties(GES_LIBRARY PROPERTIES
    IMPORTED_LOCATION "${GES_LIBRARY_DIRECTORY}/lib/GES/libGES-shared.so"
    INTERFACE_INCLUDE_DIRECTORIES "${GES_LIBRARY_DIRECTORY}/include"
)

# executable
file(GLOB SOURCES *.cpp src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GES_LIBRARY)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
target_link_libraries(${PROJECT_NAME} pthread)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

