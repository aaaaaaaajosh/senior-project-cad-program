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
#include "Model.h"
#include <dirent/dirent.h>
#include <sstream>
#include <nfd/nfd.h>

struct Group {

    glm::vec3 ambient = glm::vec3(-2.5f, 0.5f, 0.31f);
    glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float shininess = 32.0f;

    glm::vec3 lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition = glm::vec3(50, 50, 50);
};

ImGuiIO& startImGui(GLFWwindow* window);

void imguiGo(ImGuiIO& io);

void imguiRender(GLFWwindow* window, ImGuiIO& io);

void programEnd(GLFWwindow* window);

void menuBar(GLFWwindow *window, vector<std::string>& files);

void fileManager(std::string& path, vector<std::string> files);

void options(Group& group, Shader& shader, Camera& camera);

void viewport(Model& model, Camera& camera);

void variables();

vector<std::string> getFiles();

ImGuiIO& programStart(GLFWwindow*& window);

void checkIO(Camera& camera);