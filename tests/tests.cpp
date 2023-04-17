#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "Mesh.h"

int main() {

    Mesh mesh;

    mesh.vertices.emplace_back(Vertex(0.5f,  0.5f, 0.0f));
    mesh.vertices.emplace_back(Vertex(0.5f, -0.5f, 0.0f));
    mesh.vertices.emplace_back(Vertex(-0.5f, -0.5f, 0.0f));
    mesh.vertices.emplace_back(Vertex(-0.5f,  0.5f, 0.0f));
    mesh.vertices.emplace_back(Vertex(0.5f,  0.5f, 1.0f));
    mesh.vertices.emplace_back(Vertex(0.5f, -0.5f, 1.0f));
    mesh.vertices.emplace_back(Vertex(-0.5f, -0.5f, 1.0f));
    mesh.vertices.emplace_back(Vertex(-0.5f,  0.5f, 1.0f));
    mesh.indices = {
            0, 1, 3,
            1, 2, 3,
            2, 3, 7,
            2, 6, 7,
            6, 4, 5,
            6, 4, 7,
            5, 1, 0,
            5, 4, 0,
            5, 1, 2,
            5, 6, 2,
            4, 0, 3,
            4, 7, 3
    };
    mesh.lineIndices = {
            0,1,
            1,2,
            2,3,
            3,0,
            0,4,
            1,5,
            2,6,
            3,7,
            4,5,
            5,6,
            6,7,
            7,4
    };

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(800, 800, "3d Render Test", nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

	glViewport(0, 0, 800, 800);

    Shader shader("vert.txt", "frag.txt");

    shader.use();

    mesh.shader = &shader;

    Camera camera(window, shader);

    while (!glfwWindowShouldClose(window)) {


		glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
        camera.update();

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}