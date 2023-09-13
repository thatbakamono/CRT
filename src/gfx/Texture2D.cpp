#include "CRT/gfx/Texture2D.hpp"

#include "glad/gl.h"

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_id);
}

std::unique_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
    uint32_t id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(width), static_cast<int>(height), 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    return std::unique_ptr<Texture2D>(new Texture2D(id, width, height));
}

void Texture2D::set(std::vector<Rgba>& pixels) {
    if ((m_width * m_height) != pixels.size()) {
        throw std::exception();
    }

    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(m_width), static_cast<int>(m_height), 0, GL_RGBA, GL_FLOAT, pixels.data());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::bind(int slot) {
    glBindTexture(GL_TEXTURE_2D, m_id);
    glActiveTexture(GL_TEXTURE0 + slot);
}
