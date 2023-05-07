
#Versions
cmake_minimum_required(VERSION 3.23)
project(cad)

set(CMAKE_CXX_STANDARD 14)

#Directories
include_directories(${PROJECT_SOURCE_DIR}/include)
if(MSVC)
link_directories(${PROJECT_SOURCE_DIR}/libs/Win32)
endif()
add_subdirectory(submodules)

#Libraries
find_package(OpenGL REQUIRED)
link_libraries(assimp imgui glfw3 OpenGL::GL)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp; ${PROJECT_SOURCE_DIR}/src/extra/*.cpp; ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(cad WIN32 ${SOURCES})

set_target_properties(cad PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_target(copy_files ALL DEPENDS ${CMAKE_BINARY_DIR}/bin/cad)
add_dependencies(copy_files cad)

configure_file(${CMAKE_SOURCE_DIR}/src/extra/frag.txt ${CMAKE_BINARY_DIR}/bin/frag.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/extra/vert.txt ${CMAKE_BINARY_DIR}/bin/vert.txt COPYONLY)

file(COPY ${PROJECT_SOURCE_DIR}/src/models DESTINATION ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(cad nfd)