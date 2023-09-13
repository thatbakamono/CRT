#pragma once

#include <random>
#include <type_traits>

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

static thread_local std::random_device s_randomDevice {};
static thread_local std::mt19937 s_random(s_randomDevice());

class Random {
public:
    template<typename T>
    [[nodiscard]] static T next();

    template<typename T>
    [[nodiscard]] static T next(T min, T max);

    template<typename T1, typename T2>
    [[nodiscard]] static T1 next(T2 min, T2 max);

    template<Integral T>
    static T next() {
        return s_random();
    }

    template<Integral T>
    static T next(T min, T max) {
        std::uniform_int_distribution<T> distribution(min, max);

        return distribution(s_random);
    }

    template<FloatingPoint T>
    static T next() {
        return s_random();
    }

    template<FloatingPoint T>
    static T next(T min, T max) {
        std::uniform_real_distribution<T> distribution(min, max);

        return distribution(s_random);
    }

    template<>
    static glm::vec3 next(float min, float max) {
        return { next(min, max), next(min, max), next(min, max) };
    }
};
