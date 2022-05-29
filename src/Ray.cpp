
#include "Ray.hpp"

Ray::Ray(const Point3 &origin, const Vec3 &direction) : m_origin(origin), m_direction(direction) {

}

auto Ray::origin() const -> Point3 {
    return this->m_origin;
}

auto Ray::direction() const -> Vec3 {
    return this->m_direction;
}
