
#include "Ray.hpp"

Ray::Ray(const Point3 &origin, const Vec3 &direction, float time) : m_origin(origin), m_direction(direction),
                                                                    m_time(time) {

}

auto Ray::origin() const -> Point3 {
    return this->m_origin;
}

auto Ray::direction() const -> Vec3 {
    return this->m_direction;
}

auto Ray::at(float time) const -> Vec3 {
    return this->m_origin + time * this->m_direction;
}

auto Ray::time() const -> float {
    return this->m_time;
}
