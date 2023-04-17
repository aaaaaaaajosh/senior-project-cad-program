#include "Mesh.h"

void Mesh::draw() {
    init();
    shader->setVec3("aColor", glm::vec3(0.6f, 0.0f, 0.0f));
    glLineWidth(1.0f);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    shader->setVec3("aColor", glm::vec3(0, 0, 0));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
}

void Mesh::init() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); //maybe

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineIndices.size() * sizeof(int), lineIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
}

Mesh::Mesh() {}

Mesh::Mesh(Shader& InputShader) : shader(&InputShader) {}

