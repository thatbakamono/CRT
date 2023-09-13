#pragma once

#include <glm/glm.hpp>

#include "CRT/math/Math.hpp"

struct Scatter {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 attenuation;
    bool hmmm;
};

class Material {
public:
    [[nodiscard]] virtual Scatter scatter(glm::vec3 position, glm::vec3 direction, glm::vec3 normal, bool isFrontFace) const = 0;
};

class Lambertian : public Material {
private:
    glm::vec3 albedo;
public:
    explicit Lambertian(glm::vec3 albedo) : albedo(albedo) {}

    [[nodiscard]] Scatter scatter(glm::vec3 position, glm::vec3 direction, glm::vec3 normal, bool isFrontFace) const override {
        auto scatterDirection = normal + randomUnitVector();

        if (glm::abs(scatterDirection.x) < 1e-8f && glm::abs(scatterDirection.y) < 1e-8f && glm::abs(scatterDirection.z) < 1e-8f) {
            scatterDirection = normal;
        }

        return {
                .position = position,
                .direction = scatterDirection,
                .attenuation = albedo,
                .hmmm = true,
        };
    }
};

class Metal : public Material {
private:
    glm::vec3 albedo;
    float fuzziness;
public:
    Metal(glm::vec3 albedo, float fuzziness) : albedo(albedo), fuzziness(fuzziness) {}

    [[nodiscard]] Scatter scatter(glm::vec3 position, glm::vec3 direction, glm::vec3 normal, bool isFrontFace) const override {
        glm::vec3 reflectedDirection = reflect(glm::normalize(direction), normal) + fuzziness * randomPointInsideUnitSphere();

        return {
                .position = position,
                .direction = reflectedDirection,
                .attenuation =  albedo,
                .hmmm = glm::dot(reflectedDirection, normal) > 0.0f,
        };
    }
};

class Dielectric : public Material {
private:
    float refractionIndex;
public:
    explicit Dielectric(float refractionIndex) : refractionIndex(refractionIndex) {}

    [[nodiscard]] Scatter scatter(glm::vec3 rayPosition, glm::vec3 rayDirection, glm::vec3 surfaceNormal, bool isFrontFace) const override {
        float refractionRatio = isFrontFace ? (1.0f / refractionIndex) : refractionIndex;

        glm::vec3 unitDirection = glm::normalize(rayDirection);

        float cosTheta = glm::min(glm::dot(-unitDirection, surfaceNormal), 1.0f);
        float sinTheta = glm::sqrt(1.0f - square(cosTheta));

        bool cantRefract = refractionRatio * sinTheta > 1.0f;

        glm::vec3 direction;

        if (cantRefract || reflectance(cosTheta) > Random::next(0.0f, 1.0f))
            direction = reflect(unitDirection, surfaceNormal);
        else
            direction = refract(unitDirection, surfaceNormal, refractionRatio);

        return {
            .position = rayPosition,
            .direction = direction,
            .attenuation = glm::vec3(1.0f, 1.0f, 1.0f),
            .hmmm = true,
        };
    }
private:
    [[nodiscard]] float reflectance(float cosine) const {
        auto r0 = square((1.0f - refractionIndex) / (1.0f + refractionIndex));

        return r0 + (1.0f - r0) * glm::pow((1.0f - cosine), 5.0f);
    }
};
