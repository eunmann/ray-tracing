
#include "Vec3.hpp"

#include <cmath>

auto Vec3::x() const -> float {
    return this->e[0];
}

auto Vec3::y() const -> float {
    return this->e[1];
}

auto Vec3::z() const -> float {
    return this->e[2];
}

Vec3::Vec3(float x, float y, float z) {
    e[0] = x;
    e[1] = y;
    e[2] = z;
}

auto Vec3::operator-() const -> Vec3 {
    return {-this->x(), -this->y(), -this->z()};
}

auto Vec3::operator[](int i) const -> float {
    return e[i];
}

auto Vec3::operator[](int i) -> float & {
    return e[i];
}

auto Vec3::x() -> float & {
    return e[0];
}

auto Vec3::y() -> float & {
    return e[1];
}

auto Vec3::z() -> float & {
    return e[2];
}

auto Vec3::operator+=(const Vec3 &vec) -> Vec3 & {
    this->x() += vec.x();
    this->y() += vec.y();
    this->z() += vec.z();
    return *this;
}

auto Vec3::operator*=(const float c) -> Vec3 & {
    this->x() *= c;
    this->y() *= c;
    this->z() *= c;
    return *this;
}

auto Vec3::operator/=(float c) -> Vec3 & {
    return *this *= (1.0f / c);
}

auto Vec3::length() const -> float {
    return std::sqrt(this->length_squared());
}

auto Vec3::length_squared() const -> float {
    return this->x() * this->x() +
           this->y() * this->y() +
           this->z() * this->z();
}

auto Vec3::dot(const Vec3 &b) const -> float {
    return this->x() * b.x() +
           this->y() * b.y() +
           this->z() * b.z();
}

auto Vec3::cross(const Vec3 &b) const -> Vec3 {
    return {
            this->y() * b.z() - this->z() * b.y(),
            this->z() * b.x() - this->x() * b.z(),
            this->x() * b.y() - this->y() * b.x()
    };
}

auto Vec3::unit_vector() const -> Vec3 {
    return *this / this->length();
}

auto Vec3::is_near_zero() const -> bool {
    const auto s = 1e-8;
    return (std::fabs(this->e[0]) < s) &&
           (std::fabs(this->e[1]) < s) &&
           (std::fabs(this->e[2]) < s);
}

auto Vec3::reflect(const Vec3 &normal) const -> Vec3 {
    return *this - 2 * this->dot(normal) * normal;
}

auto Vec3::refract(const Vec3 &normal, float etai_over_etat) const -> Vec3 {
    auto cos_theta = std::fmin((-(*this)).dot(normal), 1.0f);
    auto ray_out_perp = etai_over_etat * (*this + cos_theta * normal);
    auto ray_out_parallel = -std::sqrt(std::fabs(1.0f - ray_out_perp.length_squared())) * normal;
    return ray_out_perp + ray_out_parallel;
}

Vec3::Vec3() = default;
