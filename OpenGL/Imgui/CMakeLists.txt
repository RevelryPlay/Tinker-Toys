cmake_minimum_required(VERSION 3.30)
project(
        OpenGLImgui
        VERSION 0.0.1
        DESCRIPTION "OpenGL Basics with ImGUI"
        LANGUAGES CXX C
)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

add_executable(OpenGLImgui main.cpp src/imguiRenderer.cpp)

# Set cmake output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

## Add ArgoDraft library
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
add_library(ArgoDraft STATIC IMPORTED)

# Windows does not currently work with the .lib file, I was able to get it to work with the .a file
# I will leave the .lib file commented out for now until I can get it to work
# Build the ArgoDraft library in CLion and copy the .a file to the lib directory to link it for the moment in Windows
#if (WIN32)
#    set_property(TARGET ArgoDraft PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/ArgoDraft.lib)
#elseif (UNIX)
    set_property(TARGET ArgoDraft PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libArgoDraft.a)
#endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ArgoDraft)
## End of ArgoDraft library

## Add OpenGL libraries
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(Stb REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

find_package(imgui CONFIG REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
## End of OpenGL libraries
