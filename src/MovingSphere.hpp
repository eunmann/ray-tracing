
#pragma once

#include "Hittable.hpp"

class MovingSphere : public Hittable {
public:
    MovingSphere(Point3 center_start, Point3 center_end, float time_start, float time_end, float radius,
                 std::shared_ptr<Material> material);

    auto hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool override;

    [[nodiscard]] virtual auto
    bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool override;

    [[nodiscard]] auto center(float time) const -> Point3;

private:
    Point3 m_center_start;
    Point3 m_center_end;
    float m_time_start, m_time_end;
    float m_radius;
    std::shared_ptr<Material> m_material;
};


