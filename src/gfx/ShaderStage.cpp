#include "CRT/gfx/ShaderStage.hpp"

#include <exception>

#include "glad/gl.h"

ShaderStage::~ShaderStage() {
    glDeleteShader(id);
}

ShaderStage ShaderStage::create(StageType stage, const std::string& source) {
    uint32_t id {};

    switch (stage) {
        case StageType::Vertex:
            id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case StageType::Fragment:
            id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }

    auto sourceCStr = source.c_str();

    glShaderSource(id, 1, &sourceCStr, nullptr);
    glCompileShader(id);

    int status {};

    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        throw std::exception();
    }

    return ShaderStage(id);
}
