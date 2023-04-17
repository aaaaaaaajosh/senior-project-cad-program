#pragma once
#include <vector>
#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::vector;

struct Vertex {
    float x, y, z;
    Vertex(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<int> indices;
    vector<int> lineIndices;
    unsigned int EBO, EBO2, VBO, VAO;
    Shader* shader;
    glm::vec3 color;


    Mesh();
    Mesh(Shader& InputShader);

    void draw();

    void init();

};
