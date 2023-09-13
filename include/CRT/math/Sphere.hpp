#pragma once

#include <glm/vec3.hpp>

#include "CRT/Material.hpp"

struct Sphere {
    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> material;
};
