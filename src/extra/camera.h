#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

class Camera {

public:
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 direction;
    float lastFrame = 0;
    float yaw = -90.0f;
    float pitch = 0.0f;
    double lastX = 0;
    double lastY = 0;
    bool firstMouse = true;
    float fov = 30;
    Shader* shader;
    int width = 1200;
    int height = 700;
    std::string active = "None";
    GLFWwindow* window;

    Camera(GLFWwindow* window, Shader& InputShader);

    void update();

    void scroll_callback(double xoffset, double yoffset);

    void mouse_callback(double xpos, double ypos);

    void mouse_button_callback(int button, int action);

private:

    static void handle_callback_mouse(GLFWwindow* window, double x, double y) {
        Camera *instance = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        instance->mouse_callback(x, y);
    }
    static void handle_callback_mouse_button(GLFWwindow* window,  int button, int action, int mods) {
        Camera *instance = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        instance->mouse_button_callback(button, action);
    }

    static void handle_callback_scroll(GLFWwindow* window, double x, double y) {
        Camera *instance = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        instance->scroll_callback(x, y);
    }
};
