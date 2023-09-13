#pragma once

#include <memory>
#include <string>

#include "GLFW/glfw3.h"

class Window {
private:
    std::unique_ptr<GLFWwindow, decltype(glfwDestroyWindow)*> inner;
public:
    Window(uint32_t width, uint32_t height, const std::string& title) : inner(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), glfwDestroyWindow) {}

    [[nodiscard]] bool isOpen() {
        return !glfwWindowShouldClose(inner.get());
    }

    [[nodiscard]] GLFWwindow* getInner() const noexcept {
        return inner.get();
    }

    void makeContextCurrent() {
        glfwMakeContextCurrent(inner.get());
    }

    void swapBuffers() {
        glfwSwapBuffers(inner.get());
    }
};
