#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "extra/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "extra/camera.h"
#include "extra/Mesh.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "extra/imguiFunctions.h"

int  main() {

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
    GLFWwindow* window = glfwCreateWindow(1200, 700, "CAD Program", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    //glViewport(0, 0, 1200, 700);

    Shader shader("vert.txt", "frag.txt");

    shader.use();

    mesh.shader = &shader;

    Camera camera(window, shader);

    mesh.init();

    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        // Start the Dear ImGui frame
        imguiGo(io);

        menuBar();

        fileManager();

        features();

        parts();

        viewport(window, mesh, camera);

        // Rendering
        imguiRender(window, io);


    }

    mesh.destroy();

    programEnd(window);

    return 0;
}