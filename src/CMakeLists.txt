include_directories(${include_dest})
include_directories(${source_dest}/include)
file(GLOB HEADERS ${include_dest}/*.hpp ${source_dest}/include/*hpp)
file(GLOB SOURCES ${source_dest}/*.cpp)

add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})

