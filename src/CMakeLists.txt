include_directories(${include_dest})
file(GLOB HEADERS ${include_dest}/*.hpp)
file(GLOB SOURCES ${source_dest}/*.cpp)

add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})

