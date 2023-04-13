
#Versions
cmake_minimum_required(VERSION 3.23)
project(cad)

set(CMAKE_CXX_STANDARD 14)

#Compile definitions
add_compile_definitions(GLEW_STATIC)

#Directories
include_directories(${PROJECT_SOURCE_DIR}/include)
if(MSVC)
link_directories(${PROJECT_SOURCE_DIR}/libs/Win32)
endif()

add_subdirectory(submodules)

#Libraries
find_package(OpenGL REQUIRED)
link_libraries(imgui glfw3 OpenGL::GL)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_executable(cad src/main.cpp src/glad.c)
set_target_properties(cad PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_target(copy_files ALL DEPENDS ${CMAKE_BINARY_DIR}/bin/cad)
add_dependencies(copy_files cad)
