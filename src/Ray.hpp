
#pragma once

#include "Vec3.hpp"

class Ray {
public:

    Ray(const Point3 &origin, const Vec3 &direction, float time);

    [[nodiscard]] auto origin() const -> Point3;

    [[nodiscard]] auto direction() const -> Vec3;

    [[nodiscard]] auto at(float time) const -> Vec3;

    [[nodiscard]] auto time() const -> float;

private:
    Point3 m_origin;
    Vec3 m_direction;
    float m_time;
};


