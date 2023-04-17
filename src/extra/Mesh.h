#pragma once
#include <vector>
#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <IMGUI/imgui.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using std::vector;

struct Vertex {
    float x, y, z;
    Vertex(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    Vertex() {}
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<int> indices;
    vector<int> edgeIndices;
    unsigned int EBO, EBO2, VBO, VAO, FBO, TEX, dTEX;
    Shader* shader;
    glm::vec3 color;


    Mesh();
    Mesh(vector<Vertex> Vertices, vector<int> Indices, Shader& InputShader);
    Mesh(Shader& InputShader);

    void draw(ImVec2 size);

    void init();

    void destroy();

};
