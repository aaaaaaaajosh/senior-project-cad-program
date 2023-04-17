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
    glm::vec3 direction;
    float lastFrame = 0;
    float yaw = -90.0f;
    float pitch = 0.0f;
    double lastX = 0;
    double lastY = 0;
    bool firstMouse = true;
    float fov = 30;
    GLFWwindow* window;
    Shader* shader;
    int width = 800;
    int height = 800;

    Camera(GLFWwindow* Window, Shader& InputShader);

    void processInput();

    void update();

    void scroll_callback(double xoffset, double yoffset);

    void mouse_callback(double xpos, double ypos);

private:

    static void handle_callback_mouse(GLFWwindow* window, double x, double y) {
        Camera *instance = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        instance->mouse_callback(x, y);
    }
    static void handle_callback_scroll(GLFWwindow* window, double x, double y) {
        Camera *instance = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        instance->scroll_callback(x, y);
    }
};
