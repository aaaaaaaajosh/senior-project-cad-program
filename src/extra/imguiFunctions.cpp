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

void menuBar(GLFWwindow* window) {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {

            }

            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                glfwSetWindowShouldClose(window, 1);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void fileManager(std::string& path, vector<std::string> files) {
    ImGui::Begin("File Manager");
    for (int i = 1; i <= files.size(); i++) {
        std::string s = std::to_string(i) + ": " + files[i-1];
        if(ImGui::Button(s.c_str())) {
            path = "models/" + files[i-1];
        }
    }
    ImGui::End();
}

void options(Group& group, Shader& shader, Camera& camera) {
    ImGui::Begin("Options");

    shader.setVec3("material.ambient", group.ambient);
    shader.setVec3("material.diffuse", group.diffuse);
    shader.setVec3("material.specular", group.specular);
    shader.setFloat("material.shininess", group.shininess);

    shader.setVec3("light.ambient",  group.lightAmbient);
    shader.setVec3("light.diffuse",  group.lightDiffuse); // darken diffuse light a bit
    shader.setVec3("light.specular", group.lightSpecular);
    shader.setVec3("light.position", group.lightPosition);

    float width = ImGui::GetContentRegionAvail().x / 3.0f - 50;
    ImGui::Text("Object Settings");
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##01", &group.ambient[0], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##02", &group.ambient[1], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Ambient", &group.ambient[2], 0.005f, -2.5f, 5.0f);

    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##21", &group.specular[0], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##22", &group.specular[1], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Specular", &group.specular[2], 0.005f, -2.5f, 5.0f);

    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##11", &group.diffuse[0], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##12", &group.diffuse[1], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Diffuse", &group.diffuse[2], 0.005f, -2.5f, 5.0f);
    ImGui::DragFloat("Shininess", &group.shininess, 0.005f);

    ImGui::Text("Light Settings");
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##141", &group.lightPosition[0], 0.5f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##142", &group.lightPosition[1], 0.5f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Light Position", &group.lightPosition[2], 0.5f);

    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##51", &group.lightAmbient[0], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##52", &group.lightAmbient[1], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Light Ambient", &group.lightAmbient[2], 0.005f, -2.5f, 5.0f);

    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##31", &group.lightSpecular[0], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##32", &group.lightSpecular[1], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Light Specular", &group.lightSpecular[2], 0.005f, -2.5f, 5.0f);

    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##41", &group.lightDiffuse[0], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("##42", &group.lightDiffuse[1], 0.005f, -2.5f, 5.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(width);
    ImGui::DragFloat("Light Diffuse", &group.lightDiffuse[2], 0.005f, -2.5f, 5.0f);

    ImGui::Text("Camera Settings");
    ImGui::DragFloat("fov", &camera.fov, 0.1f);
    ImGui::DragFloat("speed", &camera.speed, 0.5f);

    ImGui::End();
}

void viewport(Model& model, Camera& camera) {

    ImGui::Begin("Viewport");
    ImGui::BeginChild("Render");
    ImVec2 size = ImGui::GetWindowSize();
    checkIO(camera);

    glBindFramebuffer(GL_FRAMEBUFFER, model.FBO);

    glViewport(0, 0, size.x, size.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glBindTexture(GL_TEXTURE_2D, model.dTEX);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, model.dTEX, 0);

    glBindTexture(GL_TEXTURE_2D, model.TEX);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, model.TEX, 0);

    model.draw(camera);

    ImGui::Image((ImTextureID)model.TEX, size, ImVec2(0, 1), ImVec2(1, 0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

void checkIO(Camera& camera) {

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - camera.lastFrame;
    camera.lastFrame = currentFrame;
    float cameraSpeed = camera.speed * deltaTime;

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

vector<std::string> getFiles() {
    DIR* dir = opendir("./models");
    if (dir == NULL) return {};

    struct dirent* entity;
    entity = readdir(dir);
    entity = readdir(dir);
    entity = readdir(dir);
    vector<std::string> result;
    while (entity) {
        result.emplace_back(entity->d_name);
        entity = readdir(dir);
    }

    closedir(dir);
    return result;
}
