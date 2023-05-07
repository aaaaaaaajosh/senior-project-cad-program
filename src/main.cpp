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

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {

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

    Camera camera(window, shader);

    std::string path = "models/model.stl";
    std::string lastPath = path;

    Model model(shader, path);

    model.init();

    Group group;

    vector<std::string> files = getFiles();

    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        // Start the Dear ImGui frame
        imguiGo(io);

        menuBar(window, files);

        fileManager(path, files);

        options(group, shader, camera);

        viewport(model, camera);

        // Rendering
        imguiRender(window, io);

        if (path != lastPath) {
            model.destroy();
            model.loadModel(path);
            model.init();
            lastPath = path;
        }

    }

    model.destroy();

    programEnd(window);

    return 0;
}