#include "imguiFunctions.h"

ImGuiIO& startImGui(GLFWwindow* window) {
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

    return io;
}

void imguiGo(ImGuiIO& io) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    bool p_open = true;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);



    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
}

void imguiRender(GLFWwindow* window, ImGuiIO& io) {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
}

void programEnd(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void menuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::MenuItem("fish_hat.c");
                ImGui::MenuItem("fish_hat.inl");
                ImGui::MenuItem("fish_hat.h");
                if (ImGui::BeginMenu("More.."))
                {
                    ImGui::MenuItem("Hello");
                    ImGui::MenuItem("Sailor");
                    if (ImGui::BeginMenu("Recurse.."))
                    {
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Alt+F4")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void fileManager() {
    ImGui::Begin("File Manager");
    static bool selected;
    ImGui::Selectable("File1.step", &selected, ImGuiSelectableFlags_AllowDoubleClick);
    ImGui::End();
}

void features() {
    ImGui::Begin("Features");
    static bool selecting;
    ImGui::Selectable("Sketch 1", &selecting, ImGuiSelectableFlags_AllowDoubleClick);
    ImGui::End();
}

void parts() {
    ImGui::Begin("Parts");
    static bool selects;
    ImGui::Selectable("Part 1", &selects, ImGuiSelectableFlags_AllowDoubleClick);
    ImGui::End();
}

void viewport(GLFWwindow*& window, Mesh& mesh, Camera& camera) {
    ImGui::Begin("Viewport");
    ImGui::BeginChild("Render");
    ImVec2 size = ImGui::GetWindowSize();
    checkIO(window, camera);

    mesh.draw(size);

    camera.width = size.x;
    camera.height = size.y;
    camera.update();

    ImGui::EndChild();
    ImGui::End();
}

void variables() {
    ImGui::Begin("Variables");
    // Note: we are using a fixed-sized buffer for simplicity here. See ImGuiInputTextFlags_CallbackResize
    // and the code in misc/cpp/imgui_stdlib.h for how to setup InputText() for dynamically resizing strings.
    static char text[1024 * 16] = "variable window";
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
    ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 160), flags);
    ImGui::End();
}

ImGuiIO& programStart(GLFWwindow*& window) {
    glfwInit();
    window = glfwCreateWindow(1200, 700, "CAD Program", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    ImGuiIO& io = startImGui(window);
    gladLoadGL();
    return io;
}

void checkIO(GLFWwindow* window, Camera& camera) {

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - camera.lastFrame;
    camera.lastFrame = currentFrame;
    float cameraSpeed = 2.5f * deltaTime;

    if (ImGui::IsMouseDown(1)) {
        camera.active = "Look";
        if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) camera.active = "Move";
    }
    else {
        camera.active = "None";
    }

    camera.mouse_callback(ImGui::GetMousePos().x, ImGui::GetMousePos().y);

    if (ImGui::IsKeyDown(ImGuiKey_W))
        camera.cameraPos += cameraSpeed * camera.cameraFront;
    if (ImGui::IsKeyDown(ImGuiKey_S))
        camera.cameraPos -= cameraSpeed * camera.cameraFront;
    if (ImGui::IsKeyDown(ImGuiKey_A))
        camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
    if (ImGui::IsKeyDown(ImGuiKey_D))
        camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
    if (ImGui::IsKeyDown(ImGuiKey_Space))
        camera.cameraPos += cameraSpeed * camera.cameraUp;
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
        camera.cameraPos -= cameraSpeed * camera.cameraUp;
}