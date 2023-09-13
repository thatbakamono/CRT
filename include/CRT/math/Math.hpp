#pragma once

#include <glm/glm.hpp>

#include "CRT/Random.hpp"

template<typename T>
[[nodiscard]] static T lerp(T start, T end, float time) {
    return ((1.0f - time) * start) + (time * end);
}

template<typename T>
[[nodiscard]] static T square(T value) {
    return value * value;
}

[[nodiscard]] static glm::vec3 reflect(glm::vec3 value, glm::vec3 normal) {
    return value - 2.0f * glm::dot(value, normal) * normal;
}

[[nodiscard]] static glm::vec3 refract(const glm::vec3& uv, const glm::vec3& normal, float etaOverEtaPrim) {
    auto cosTheta = glm::min(glm::dot(-uv, normal), 1.0f);

    glm::vec3 perpendicular = etaOverEtaPrim * (uv + (cosTheta * normal));
    glm::vec3 parallel = -glm::sqrt(glm::abs(1.0f - square(glm::length(perpendicular)))) * normal;

    return perpendicular + parallel;
}

template<typename T>
[[nodiscard]] static bool inBounds(T value, T min, T max) {
    return value >= min && value <= max;
}

[[nodiscard]] static glm::vec3 randomPointInsideUnitSphere() {
    while (true) {
        auto point = Random::next<glm::vec3>(0.0f, 1.0f);

        if (square(glm::length(point)) < 1.0f)
            return point;
    }
}

[[nodiscard]] static glm::vec3 randomPointInsideUnitDisk() {
    while (true) {
        auto point = glm::vec3(Random::next(-1.0f, 1.0f), Random::next(-1.0f, 1.0f), 0.0f);

        if (square(glm::length(point)) < 1.0f)
            return point;
    }
}

[[nodiscard]] static glm::vec3 randomUnitVector() {
    return glm::normalize(randomPointInsideUnitSphere());
}
