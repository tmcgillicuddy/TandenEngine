cmake_minimum_required(VERSION 3.12)
project(TandenEngine)

set(CMAKE_CXX_STANDARD 17)

# Only necessary under Windows
include_directories("$ENV{VULKAN_SDK}/include")

# Disable glfw Documentation, Tests and Examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Add imgui library
include_directories("Libraries/imgui")
set(IMGUI_DIR "Libraries/imgui")
set(IMGUI_SOURCES ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_widgets.cpp)

#Add glfw headers
include_directories("Libraries/GLFW/include")

#Get all the source and header files from the main source code dir
file(GLOB_RECURSE TANDEN_SOURCE "Source/*.h" "Source/*.cpp")

#Put all the source file dirs into their proper place
add_executable(TandenEngine ${TANDEN_SOURCE} ${IMGUI_SOURCES})

#GLFW Build through CMake (Loads and links Vulkan as well)
add_subdirectory("Libraries/GLFW")

#Include Math lib headers
include_directories("Source/Core/Math")

#Link GLFW
target_link_libraries(TandenEngine glfw)

#Locate the Vulkan SDKs
find_package(Vulkan REQUIRED)

#Link the SDK using GLFW's macros
target_link_libraries(TandenEngine ${VULKAN_LIBRARY})

#Link tinyobj library
include_directories(Libraries/tinyobjloader)
add_subdirectory(Libraries/tinyobjloader)
target_link_libraries(TandenEngine tinyobjloader)

#Export Important content files
file(COPY  ${CMAKE_SOURCE_DIR}/ContentFiles
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ )