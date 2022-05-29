
#pragma once

#include "RNG.hpp"

class Vec3 {

public:

    Vec3();

    Vec3(float x, float y, float z);

    [[nodiscard]] auto x() const -> float;

    [[nodiscard]] auto y() const -> float;

    [[nodiscard]] auto z() const -> float;

    [[nodiscard]] auto x() -> float &;

    [[nodiscard]] auto y() -> float &;

    [[nodiscard]] auto z() -> float &;

    auto operator-() const -> Vec3;

    auto operator[](int i) const -> float;

    auto operator[](int i) -> float &;

    auto operator+=(const Vec3 &vec) -> Vec3 &;

    auto operator*=(float c) -> Vec3 &;

    auto operator/=(float c) -> Vec3 &;

    [[nodiscard]] auto length() const -> float;

    [[nodiscard]] auto length_squared() const -> float;

    [[nodiscard]] auto dot(const Vec3 &b) const -> float;

    [[nodiscard]] auto cross(const Vec3 &b) const -> Vec3;

    [[nodiscard]] auto unit_vector() const -> Vec3;

    inline auto static random() -> Vec3 {
        return {
                RNG::random_float(),
                RNG::random_float(),
                RNG::random_float()
        };
    }

    inline auto static random(float min, float max) -> Vec3 {
        return {
                RNG::random_float(min, max),
                RNG::random_float(min, max),
                RNG::random_float(min, max)
        };
    }

    inline auto static random_in_unit_sphere() -> Vec3 {
        Vec3 vec;
        do {
            vec = Vec3::random(-1.0f, 1.0f);
        } while (vec.length_squared() >= 1);

        return vec;
    }

    inline auto static random_unit_vector() -> Vec3 {
        return random_in_unit_sphere().unit_vector();
    }

    [[nodiscard]] auto is_near_zero() const -> bool;

    [[nodiscard]] auto reflect(const Vec3 &normal) const -> Vec3;

    [[nodiscard]] auto refract(const Vec3 &normal, float etai_over_etat) const -> Vec3;

    inline auto static random_in_unit_disk() -> Vec3 {
        Vec3 vec;
        do {
            vec = Vec3{RNG::random_float(-1.0f, 1.0f), RNG::random_float(-1.0f, 1.0f), 0.0f};
        } while (vec.length_squared() >= 1.0f);
        return vec;
    }

private:
    float e[3]{0.0f, 0.0f, 0.0f};
};

inline auto operator+(const Vec3 &a, const Vec3 &b) -> Vec3 {
    return {
            a.x() + b.x(),
            a.y() + b.y(),
            a.z() + b.z()
    };
}

inline auto operator-(const Vec3 &a, const Vec3 &b) -> Vec3 {
    return {
            a.x() - b.x(),
            a.y() - b.y(),
            a.z() - b.z()
    };
}

inline auto operator*(const Vec3 &a, const Vec3 &b) -> Vec3 {
    return {
            a.x() * b.x(),
            a.y() * b.y(),
            a.z() * b.z()
    };
}

inline auto operator*(const Vec3 &a, const float c) -> Vec3 {
    return {
            a.x() * c,
            a.y() * c,
            a.z() * c
    };
}

inline auto operator*(const float c, const Vec3 &a) -> Vec3 {
    return a * c;
}

inline auto operator/(const Vec3 &a, const float c) -> Vec3 {
    return {
            a.x() / c,
            a.y() / c,
            a.z() / c
    };
}

using Point3 = Vec3;
using Color = Vec3;

