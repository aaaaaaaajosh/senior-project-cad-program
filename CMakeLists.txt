cmake_minimum_required(VERSION 3.23)
project(cad)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(GLEW_STATIC)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs/Win32)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/libs/Win32/IMGUI/*.cpp)
add_library(imgui STATIC ${SOURCES})

find_package(OpenGL REQUIRED)
link_libraries(imgui glew32s glfw3 OpenGL::GL)

add_subdirectory(src)
