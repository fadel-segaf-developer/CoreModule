#pragma once

#ifndef GLFW_MANAGER_H
#define GLFW_MANAGER_H

#include "IWindowManager.h"
#include <GLFW/glfw3.h>  // Include GLFW for window management
#include <imgui.h>  // Include ImGui
#include <backends/imgui_impl_glfw.h>  // GLFW bindings for ImGui
#include <backends/imgui_impl_opengl3.h>  // OpenGL bindings for ImGui

class GLFWManager : public IWindowManager {
public:
    GLFWManager() = default;
    ~GLFWManager() {
        // ImGui Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Destroy GLFW window
        if (window_) {
            glfwDestroyWindow(window_);
            window_ = nullptr;
        }

        // Terminate GLFW
        glfwTerminate();
    }

    bool Init(int width, int height, const char* windowTitle) override {
        // Initialize GLFW
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
            return false;
        }

        // Create a windowed mode window and its OpenGL context
        window_ = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
        if (!window_) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
            return false;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);  // Enable v-sync

        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window_, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        // Setup ImGui style
        ImGui::StyleColorsDark();

        return true;
    }

    void PollEvents() override {
        // Poll events (keyboard, mouse, etc.)
        glfwPollEvents();
    }

    void SwapBuffers() override {
        // Swap the buffers (render the window content)
        glfwSwapBuffers(window_);
    }

    bool ShouldClose() override {
        return glfwWindowShouldClose(window_);
    }

    void NewFrame() override
    {
        // Poll events and handle window logic
        PollEvents();

        // Start a new frame for ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void Render() override
    {
        // Render the ImGui demo window
        ImGui::ShowDemoWindow();

        // Render ImGui content
        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);  // Clear the screen with a color
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the buffers to display the content
        SwapBuffers();
    }

private:
    GLFWwindow* window_ = nullptr;
};

#endif  // GLFW_MANAGER_H
