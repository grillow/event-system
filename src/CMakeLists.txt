include_directories(${INCLUDE_DIRECTORY})
include_directories(${SOURCE_DIRECTORY}/include)
file(GLOB HEADERS ${INCLUDE_DIRECTORY}/*.hpp ${SOURCE_DIRECTORY}/include/*.hpp)
file(GLOB SOURCES ${SOURCE_DIRECTORY}/*.cpp)

add_library(${PROJECT_NAME}-shared SHARED ${SOURCES})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES})

install(TARGETS ${PROJECT_NAME}-shared
    LIBRARY DESTINATION ${LIB_BIN_DIRECTORY})

install(TARGETS ${PROJECT_NAME}-static
    ARCHIVE DESTINATION ${LIB_BIN_DIRECTORY})

