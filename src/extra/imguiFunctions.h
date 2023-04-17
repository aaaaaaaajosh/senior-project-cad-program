#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "Mesh.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

ImGuiIO& startImGui(GLFWwindow* window);

void imguiGo(ImGuiIO& io);

void imguiRender(GLFWwindow* window, ImGuiIO& io);

void programEnd(GLFWwindow* window);

void menuBar();

void fileManager();

void features();

void parts();

void viewport(GLFWwindow*& window, Mesh& mesh, Camera& camera);

void variables();

ImGuiIO& programStart(GLFWwindow*& window);

void checkIO(GLFWwindow* window, Camera& camera);