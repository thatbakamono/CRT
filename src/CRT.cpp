#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "CRT/RayTracer.hpp"
#include "CRT/Window.hpp"
#include "CRT/World.hpp"
#include "CRT/gfx/Texture2D.hpp"
#include "CRT/raii/Glfw.hpp"
#include "CRT/raii/ImGui.hpp"

constexpr float PI = 3.14159265359;

int main() {
    Glfw glfw;

    glfw.useOpenGl(OpenGlProfile::Core, 4, 6);

    Window window(1920, 1080, "CRT");

    window.makeContextCurrent();

    glfw.enableVSync();

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        throw std::exception("Failed to load OpenGL function pointers");
    }

    ImGuiImpl imGui(window);

    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    auto texture = Texture2D::create(1600, 900);

    auto aspectRatio = static_cast<float>(texture->width()) / static_cast<float>(texture->height());

    World world;

    {
        world.spheres.emplace_back(
                glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f,
                std::make_unique<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f))
        );

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                glm::vec3 center(a + 0.9 * Random::next(0.0f, 1.0f), 0.2, b + 0.9 * Random::next(0.0f, 1.0f));

                if (glm::length(center - glm::vec3(4.0f, 0.2f, 0.0f)) > 0.9) {
                    auto materialType = Random::next(0.0f, 1.0f);

                    std::shared_ptr<Material> material;

                    if (materialType < 0.8) {
                        glm::vec3 albedo = Random::next<glm::vec3>(0.0f, 1.0f) * Random::next<glm::vec3>(0.0f, 1.0f);

                        material = std::make_shared<Lambertian>(albedo);
                    } else if (materialType < 0.95) {
                        glm::vec3 albedo = Random::next<glm::vec3>(0.5f, 1.0f);
                        auto fuzziness = Random::next(0.0f, 0.5f);

                        material = std::make_shared<Metal>(albedo, fuzziness);
                    } else {
                        material = std::make_shared<Dielectric>(1.5f);
                    }

                    world.spheres.emplace_back(center, 0.2f, material);
                }
            }
        }

        world.spheres.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Dielectric>(1.5f));
        world.spheres.emplace_back(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f)));
        world.spheres.emplace_back(glm::vec3(4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f));
    }

    glm::vec3 origin(13.0f, 2.0f, 3.0f);
    glm::vec3 lookAt(0.0f, 0.0f, 0.0f);

    auto focusDistance = 10.0f;
    auto aperture = 0.1f;

    Camera camera(
            origin,
            lookAt,
            glm::vec3(0.0f, 1.0f, 0.0f),
            20.0f,
            aspectRatio,
            aperture,
            focusDistance
    );

    RayTracer rayTracer(texture->width(), texture->height(), camera);

    texture->set(rayTracer.rayTrace(world));

    while (window.isOpen()) {
        glfw.pollEvents();

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        imGui.begin();

        {
            ImGui::Begin("Viewport");

            ImGui::Image(reinterpret_cast<void*>(static_cast<uint64_t>(texture->id())), ImVec2(1600.0f, 900.0f), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }

        imGui.end();

        window.swapBuffers();
    }

    return 0;
}
