# CMakeList.txt : CMake project for Vulkan-UI, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Vulkan-UI "Vulkan-UI.cpp" "Vulkan-UI.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Vulkan-UI PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
