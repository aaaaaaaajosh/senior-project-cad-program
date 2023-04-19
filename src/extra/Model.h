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
#include "Mesh.h"
#include "Shader.h"

class Model {

public:

    Model() {}

    Model(Shader& InputShader, std::string path)
    {
        shader = &InputShader;
        loadModel(path);
    }
    void draw(Camera camera);
    void init();
    void destroy();
    Shader* shader;
    unsigned int FBO, TEX, dTEX;
    vector<Mesh> meshes;
    void loadModel(std::string path);

private:
    std::string directory;

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

};