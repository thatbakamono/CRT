#pragma once

#include <execution>
#include <optional>
#include <ranges>
#include <vector>

#include <glm/glm.hpp>

#include "CRT/Camera.hpp"
#include "CRT/Color.hpp"
#include "CRT/Random.hpp"
#include "CRT/World.hpp"
#include "CRT/math/Math.hpp"
#include "CRT/math/Ray.hpp"

[[nodiscard]] static glm::vec4 background(const Ray& ray) {
    auto unitDirection = glm::normalize(ray.direction());
    auto t = 0.5f * (unitDirection.y + 1.0f);
    auto color = lerp(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.7f, 1.0f), t);

    return { color, 1.0f };
}

class RayTracer {
private:
    uint32_t width;
    uint32_t height;

    Camera camera;

    uint32_t samplesPerPixel = 100;
    int32_t maxRecursionDepth = 50;

    std::vector<Rgba> pixels;
public:
    RayTracer(uint32_t width, uint32_t height, Camera camera) : width(width), height(height), camera(camera) {
        pixels.reserve(width * height);
    }

    [[nodiscard]] std::vector<Rgba>& rayTrace(World& world) {
        pixels.clear();
        pixels.resize(width * height);

        if (width > height) {
            auto range = std::views::iota(0u, height);

            std::for_each(std::execution::par, range.begin(), range.end(), [this, world] (auto y) {
                for (uint32_t x = 0; x < width; x++) {
                    pixels[y * width + x] = this->sample(world, x, y);
                }
            });
        } else {
            auto range = std::views::iota(0u, width);

            std::for_each(std::execution::par, range.begin(), range.end(), [this, world] (auto x) {
                for (uint32_t y = 0; y < height; y++) {
                    pixels[y * width + x] = this->sample(world, x, y);
                }
            });
        }

        return pixels;
    }
private:
    [[nodiscard]] Rgba sample(const World& world, uint32_t x, uint32_t y) const {
        glm::vec3 color(0.0f, 0.0f, 0.0f);

        for (uint32_t sample = 0; sample < samplesPerPixel; sample++) {
            auto u = (static_cast<float>(x) + Random::next(0.0f, 1.0f)) / (static_cast<float>(width) - 1.0f);
            auto v = (static_cast<float>(y) + Random::next(0.0f, 1.0f)) / (static_cast<float>(height) - 1.0f);

            Ray ray = camera.createRay(u, v);

            color += trace(world, ray, maxRecursionDepth);
        }

        color /= samplesPerPixel;
        color = glm::sqrt(color);

        return Rgba(color.x, color.y, color.z, 1.0f);
    }

    [[nodiscard]] glm::vec3 trace(const World& world, const Ray& ray, int32_t currentDepth) const {
        std::optional<Hit> hit = this->cast(world, ray, 0.001f, std::numeric_limits<float>::infinity());

        if (currentDepth <= 0)
            return { 0.0f, 0.0f, 0.0f };

        if (hit.has_value()) {
            Scatter scatter = hit->material->scatter(hit->position, ray.direction(), hit->normal, hit->frontFace);

            if (scatter.hmmm) {
                return scatter.attenuation * trace(world, Ray(scatter.position, scatter.direction), currentDepth - 1);
            } else {
                return { 0.0f, 0.0f, 0.0f };
            }
        } else {
            return background(ray);
        }
    }

    [[nodiscard]] std::optional<Hit> cast(const World& world, const Ray& ray, float tMin, float tMax) const {
        std::optional<Hit> hit {};

        for (const auto& sphere : world.spheres) {
            auto currentHit = ray.cast(sphere, tMin, tMax);

            if (currentHit.has_value()) {
                tMax = currentHit->t;
                hit = currentHit;
            }
        }

        return hit;
    }
};
