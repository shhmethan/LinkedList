#define GL_SILENCE_DEPRECATION
#include "./imgui/imgui.h"
#include "./backend/imgui_impl_glfw.h"
#include "./backend/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include "linkedlist.h"

// ✅ Global linked list and label counter
LinkedList<std::string> ll;
int counter = 1;

void drawGUI() {
    ImGui::Begin("Visual Linked List");

    // 🔢 Index input box + Delete At Index button
    static int indexToDelete = 0;
    ImGui::Text("Enter an index to delete:");
    ImGui::InputInt("##IndexInput", &indexToDelete);
    ImGui::SameLine();
    if (ImGui::Button("Delete At Index")) {
        ll.deleteAtIndex(indexToDelete);
    }

    ImGui::Spacing(); ImGui::Spacing();

    // 🔘 Linked list operation buttons
    if (ImGui::Button("Append Node")) {
        std::string label = "X" + std::to_string(counter++);
        ll.append(label);
    }

    if (ImGui::Button("Prepend Node")) {
        std::string label = "X" + std::to_string(counter++);
        ll.addFirst(label);
    }

    ImGui::SameLine();
    if (ImGui::Button("Delete Last")) {
        ll.deleteLast();
    }

    ImGui::SameLine();
    if (ImGui::Button("Delete First")) {
        ll.deleteFirst();
    }

    ImGui::SameLine();
    if (ImGui::Button("Exit")) {
        exit(0);
    }

    ImGui::Separator();
    ImGui::Text("Visual List:");
    ImGui::Spacing();

    // 🎨 Draw nodes visually using ImDrawList
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 cursor = ImGui::GetCursorScreenPos();

    float node_radius = 30.0f;
    float spacing = 100.0f;
    float x = cursor.x + node_radius;
    float y = cursor.y + node_radius;

    int index = 0;
    ll.forEach([&](const std::string& data, bool isLast) {
        ImVec2 center(x + index * spacing, y);

        // Blue node
        draw_list->AddCircleFilled(center, node_radius, IM_COL32(100, 150, 250, 255));
        draw_list->AddCircle(center, node_radius, IM_COL32(255, 255, 255, 255), 32, 2.0f);

        // Text inside node
        ImVec2 text_size = ImGui::CalcTextSize(data.c_str());
        ImVec2 text_pos(center.x - text_size.x / 2, center.y - text_size.y / 2);
        draw_list->AddText(text_pos, IM_COL32(255, 255, 255, 255), data.c_str());

        // Arrow to next
        if (!isLast) {
            ImVec2 p1(center.x + node_radius, center.y);
            ImVec2 p2(center.x + spacing - node_radius, center.y);
            draw_list->AddLine(p1, p2, IM_COL32(200, 200, 200, 255), 2.0f);
            draw_list->AddTriangleFilled(
                    ImVec2(p2.x - 6, p2.y - 4),
                    ImVec2(p2.x, p2.y),
                    ImVec2(p2.x - 6, p2.y + 4),
                    IM_COL32(200, 200, 200, 255)
            );
        }

        index++;
    });

    // Push ImGui layout down to avoid overlap
    ImGui::Dummy(ImVec2(index * spacing + 50, node_radius * 2 + 20));
    ImGui::End();
}

int main() {
    if (!glfwInit()) return 1;

    // OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Linked List GUI", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        drawGUI();

        // Render to screen
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}