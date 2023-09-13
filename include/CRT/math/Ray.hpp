#pragma once

#include <optional>
#include <memory>

#include <glm/vec3.hpp>

#include "CRT/Material.hpp"

struct Hit {
    glm::vec3 position;
    glm::vec3 normal;
    float t;
    bool frontFace;
    std::shared_ptr<Material> material;
};

class Ray {
private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
public:
    Ray(glm::vec3 origin, glm::vec3 direction) : m_origin(origin), m_direction(direction) {}

    [[nodiscard]] glm::vec3 origin() const {
        return m_origin;
    }

    [[nodiscard]] glm::vec3 direction() const {
        return m_direction;
    }

    [[nodiscard]] glm::vec3 at(float t) const {
        return m_origin + t * m_direction;
    }

    template<typename T>
    [[nodiscard]] std::optional<Hit> cast(const T& object, float tMin, float tMax) const;
};
