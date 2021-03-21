file(GLOB HEADERS include/GES/*.hpp)
file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME}_shared SHARED ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME}_shared PUBLIC ${GES_SOURCE_DIR}/include/GES ${CMAKE_CURRENT_BINARY_DIR})
add_library(${PROJECT_NAME}_static STATIC ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME}_static PUBLIC ${GES_SOURCE_DIR}/include/GES ${CMAKE_CURRENT_BINARY_DIR})

