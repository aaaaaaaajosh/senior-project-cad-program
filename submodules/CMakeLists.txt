

#Compiling imgui to library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/IMGUI)
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/IMGUI/*.cpp; ${CMAKE_CURRENT_SOURCE_DIR}/IMGUI/backends/imgui_impl_glfw.cpp; ${CMAKE_CURRENT_SOURCE_DIR}/IMGUI/backends/imgui_impl_opengl3.cpp)
add_library(imgui STATIC ${SOURCES})

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(assimp)

