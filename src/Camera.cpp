
#include "Camera.hpp"

#include "UnitConversions.hpp"
#include <cmath>

Camera::Camera(Point3 look_from, Point3 look_at, Vec3 up_vector, float vertical_field_of_view, float aspect_ratio,
               float aperture,
               float focus_dist,
               float time_start,
               float time_end) {

    auto theta = UnitConversions::degrees_to_radians(vertical_field_of_view);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2.0f * h;
    auto viewport_width = aspect_ratio * viewport_height;

    this->m_w = (look_from - look_at).unit_vector();
    this->m_u = up_vector.cross(this->m_w).unit_vector();
    this->m_v = this->m_w.cross(this->m_u);

    this->m_origin = look_from;
    this->m_horizontal = focus_dist * viewport_width * this->m_u;
    this->m_vertical = focus_dist * viewport_height * this->m_v;
    this->m_lower_left_corner =
            this->m_origin -
            this->m_horizontal / 2.0f -
            this->m_vertical / 2.0f -
            focus_dist * this->m_w;

    this->m_lens_radius = aperture / 2.0f;
    this->m_time_start = time_start;
    this->m_time_end = time_end;
}

auto Camera::origin() const -> const Point3 & {
    return m_origin;
}

auto Camera::horizontal() const -> const Vec3 & {
    return m_horizontal;
}

auto Camera::vertical() const -> const Vec3 & {
    return m_vertical;
}

auto Camera::lower_left_corner() const -> const Vec3 & {
    return m_lower_left_corner;
}

auto Camera::get_ray(float s, float t) const -> Ray {

    auto ray_direction = this->m_lens_radius * Vec3::random_in_unit_disk();
    auto offset = this->m_u * ray_direction.x() + this->m_v * ray_direction.y();

    return {this->m_origin + offset,
            this->lower_left_corner() + s * this->horizontal() + t * this->vertical() -
            this->origin() - offset,
            RNG::random_float(this->m_time_start, this->m_time_end)};
}

auto Camera::set_origin(const Point3 &origin) -> void {
    this->m_origin = origin;
}
