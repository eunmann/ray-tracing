
#pragma once

#include "Vec3.hpp"

class Ray {
public:

    Ray(const Point3 &origin, const Vec3 &direction);

    [[nodiscard]] auto origin() const -> Point3;

    [[nodiscard]] auto direction() const -> Vec3;

    auto at(float time) const {
        return this->m_origin + time * this->m_direction;
    }

private:
    Point3 m_origin;
    Vec3 m_direction;
};


