cmake_minimum_required(VERSION 3.30)
project(Threaded)

set(CMAKE_CXX_STANDARD 23)

add_executable(Threaded main.cpp
        src/ThreadPool.cpp
        src/ThreadPool.hpp)

## Add ArgoDraft library

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# Set cmake output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(ArgoDraft STATIC IMPORTED)
#if (WIN32)
#    set_property(TARGET ArgoDraft PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/ArgoDraft.lib)
#endif ()
#
#if (UNIX)
set_property(TARGET ArgoDraft PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libArgoDraft.a)
#endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# wsock32 and ws2_32 are required for Windows networking
#if(WIN32)
#    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
#endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ArgoDraft)

## End of ArgoDraft library