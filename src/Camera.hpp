
#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {

public:
    explicit Camera(Point3 look_from,
                    Point3 look_at,
                    Vec3 up_vector,
                    float vertical_field_of_view,
                    float aspect_ratio,
                    float aperture,
                    float focus_dist,
                    float time_start,
                    float time_end);

    [[nodiscard]] auto get_origin() const -> const Point3 &;

    [[nodiscard]] auto get_horizontal() const -> const Vec3 &;

    [[nodiscard]] auto get_vertical() const -> const Vec3 &;

    [[nodiscard]] auto get_lower_left_corner() const -> const Vec3 &;

    [[nodiscard]] auto get_ray(float s, float t) const -> Ray;

private:
    Point3 m_origin;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_lower_left_corner;
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;
    float m_lens_radius;
    // Shutter Open/Close times
    float m_time_start;
    float m_time_end;
};


