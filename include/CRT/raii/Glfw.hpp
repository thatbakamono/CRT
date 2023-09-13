#pragma once

#include <cassert>
#include <exception>

#include "GLFW/glfw3.h"

enum OpenGlProfile {
    Core,
};

struct Glfw {
    Glfw() {
        if (glfwInit() != GLFW_TRUE) {
            throw std::exception("GLFW initialization failed");
        }
    }

    ~Glfw() {
        glfwTerminate();
    }

    void useOpenGl(OpenGlProfile profile, int32_t major, int32_t minor) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

        switch (profile)
        {
            case OpenGlProfile::Core:
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                break;
            default:
                assert(false);
                break;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    }

    void enableVSync() {
        glfwSwapInterval(1);
    }

    void pollEvents() {
        glfwPollEvents();
    }
};
