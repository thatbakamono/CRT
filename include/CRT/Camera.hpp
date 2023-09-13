#pragma once

#include <glm/glm.hpp>

#include "CRT/math/Ray.hpp"

class Camera {
private:
    glm::vec3 origin {};

    glm::vec3 vertical {};
    glm::vec3 horizontal {};
    glm::vec3 lowerLeftCorner {};

    glm::vec3 u {};
    glm::vec3 v {};
    glm::vec3 w {};

    float lensRadius {};
public:
    Camera(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 up, float fieldOfView, float aspectRatio, float aperture, float focusDistance) {
        auto theta = glm::radians(fieldOfView);
        auto h = glm::tan(theta / 2.0f);
        auto viewportHeight = 2.0f * h;
        auto viewportWidth = aspectRatio * viewportHeight;

        w = glm::normalize(origin - lookAt);
        u = glm::normalize(glm::cross(up, w));
        v = glm::cross(w, u);

        this->origin = origin;
        horizontal = focusDistance * viewportWidth * u;
        vertical = focusDistance * viewportHeight * v;
        lowerLeftCorner = this->origin - (horizontal / 2.0f) - (vertical / 2.0f) - (focusDistance * w);
        lensRadius = aperture / 2.0f;
    }

    [[nodiscard]] Ray createRay(float s, float t) const {
        glm::vec3 point = lensRadius * randomPointInsideUnitDisk();
        glm::vec3 offset = u * point.x + v * point.y;

        return { origin + offset, lowerLeftCorner + (s * horizontal) + (t * vertical) - origin - offset };
    }
};
