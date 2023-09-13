#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "CRT/Window.hpp"

struct ImGuiImpl {
    ImGuiImpl(Window& window) {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window.getInner(), true);
        ImGui_ImplOpenGL3_Init();
    }

    ~ImGuiImpl() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void end() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};
