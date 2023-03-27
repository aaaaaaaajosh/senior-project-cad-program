
#Versions
cmake_minimum_required(VERSION 3.23)
project(cad)

set(CMAKE_CXX_STANDARD 14)

#Compile definitions
add_compile_definitions(GLEW_STATIC)

#Directories
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs/Win32)

#Compiling imgui to library
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/libs/Win32/IMGUI/*.cpp)
add_library(imgui STATIC ${SOURCES})

#Libraries
find_package(OpenGL REQUIRED)
link_libraries(imgui glew32s glfw3 OpenGL::GL)

#Subdirectory
add_subdirectory(src)
