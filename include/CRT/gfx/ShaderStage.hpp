#pragma once

#include <cstdint>
#include <string>

enum StageType {
    Vertex,
    Fragment,
};

class ShaderStage {
private:
    uint32_t id;
private:
    explicit ShaderStage(uint32_t id) : id(id) {}
public:
    ~ShaderStage();

    ShaderStage(const ShaderStage& other) = delete;
    ShaderStage(ShaderStage&& other) noexcept = delete;

    ShaderStage& operator =(const ShaderStage& other) = delete;
    ShaderStage& operator =(ShaderStage&& other) noexcept = delete;

    [[nodiscard]] static ShaderStage create(StageType stage, const std::string& source);

    [[nodiscard]] inline uint32_t getId() const {
        return id;
    }
};
