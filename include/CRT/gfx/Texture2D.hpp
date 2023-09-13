#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "CRT/Color.hpp"

class Texture2D {
private:
    uint32_t m_id;
    uint32_t m_width;
    uint32_t m_height;
private:
    Texture2D(uint32_t id, uint32_t width, uint32_t height) : m_id(id), m_width(width), m_height(height) {}
public:
    Texture2D(const Texture2D& other) = delete;
    Texture2D(Texture2D&& other) noexcept = delete;

    ~Texture2D();

    Texture2D& operator =(const Texture2D& other) = delete;
    Texture2D& operator =(Texture2D&& other) noexcept = delete;

    [[nodiscard]] static std::unique_ptr<Texture2D> create(uint32_t width, uint32_t height);

    void set(std::vector<Rgba>& pixels);

    void bind();
    void bind(int slot);

    [[nodiscard]] uint32_t id() const {
        return m_id;
    }

    [[nodiscard]] uint32_t width() const {
        return m_width;
    }

    [[nodiscard]] uint32_t height() const {
        return m_height;
    }
};
