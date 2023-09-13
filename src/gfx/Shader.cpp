#include "CRT/gfx/Shader.hpp"

#include <exception>

#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

Shader::~Shader() {
    glDeleteProgram(id);
}

std::unique_ptr<Shader> Shader::create(ShaderStage vertexStage, ShaderStage fragmentStage) {
    auto id = glCreateProgram();

    glAttachShader(id, vertexStage.getId());
    glAttachShader(id, fragmentStage.getId());

    glLinkProgram(id);

    int status {};

    glGetProgramiv(id, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        int capacity {};

        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &capacity);

        std::string message;

        message.resize(capacity);

        glGetProgramInfoLog(id, capacity, nullptr, message.data());

        throw std::exception(message.c_str());
    }

    glDetachShader(id, fragmentStage.getId());
    glDetachShader(id, vertexStage.getId());

    return std::unique_ptr<Shader>(new Shader(id));
}

void Shader::bind() {
    glUseProgram(id);
}

void Shader::setUniform(const std::string& name, int32_t value) {
    auto location = glGetUniformLocation(id, name.c_str());

    if (location == -1) {
        throw std::exception("Unknown attribute!");
    }

    glUniform1i(location, value);
}

void Shader::setUniform(const std::string &name, glm::mat4 value) {
    auto location = glGetUniformLocation(id, name.c_str());

    if (location == -1) {
        throw std::exception("Unknown attribute!");
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
