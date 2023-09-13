#include "CRT/math/Ray.hpp"
#include "CRT/math/Sphere.hpp"
#include "CRT/math/Math.hpp"

#include <glm/glm.hpp>

template<>
[[nodiscard]] std::optional<Hit> Ray::cast(const Sphere& sphere, float tMin, float tMax) const {
    glm::vec3 oc = m_origin - sphere.center;

    auto a = square(glm::length(m_direction));
    auto halfB = glm::dot(oc, m_direction);
    auto c = square(glm::length(oc)) - square(sphere.radius);

    // Δ == 0 -> one solution
    // Δ >  0 -> two solutions
    // Δ <  0 -> no **real** solutions
    auto discriminant = square(halfB) - a * c;

    if (discriminant < 0.0f)
        return std::nullopt;

    auto discriminantRoot = glm::sqrt(discriminant);

    // (-b ± √Δ) / 2a
    float t1 = (-halfB - discriminantRoot) / a;
    float t2 = (-halfB + discriminantRoot) / a;

    float t {};

    if (inBounds(t1, tMin, tMax)) {
        t = t1;
    } else if (inBounds(t2, tMin, tMax)) {
        t = t2;
    } else {
        return std::nullopt;
    }

    auto normal = (this->at(t) - sphere.center) / sphere.radius;

    bool frontFace {};

    if (glm::dot(m_direction, normal) < 0.0f) {
        frontFace = true;
    } else {
        frontFace = false;
        normal = -normal;
    }

    return std::make_optional<Hit>(this->at(t), normal, t, frontFace, sphere.material);
}
