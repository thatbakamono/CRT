#pragma once

#include <cstdint>
#include <memory>

#include <glm/glm.hpp>

#include "ShaderStage.hpp"

class Shader {
private:
    uint32_t id;
private:
    explicit Shader(uint32_t id) : id(id) {}
public:
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept = delete;

    ~Shader();

    Shader& operator =(const Shader& other) = delete;
    Shader& operator =(Shader&& other) noexcept = delete;

    [[nodiscard]] static std::unique_ptr<Shader> create(ShaderStage vertexStage, ShaderStage fragmentStage);

    void setUniform(const std::string& name, int32_t value);
    void setUniform(const std::string& name, glm::mat4 value);

    void bind();
};
