project(example-static)


# GES_LIBRARY
set(GES_LIBRARY_DIRECTORY ${CMAKE_SOURCE_DIR})
add_library(GES_LIBRARY STATIC IMPORTED)
set_target_properties(GES_LIBRARY PROPERTIES
    IMPORTED_LOCATION "${GES_LIBRARY_DIRECTORY}/lib/GES/libGES-static.a"
    INTERFACE_INCLUDE_DIRECTORIES "${GES_LIBRARY_DIRECTORY}/include"
)


# executable
file(GLOB SOURCES ../*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GES_LIBRARY)

