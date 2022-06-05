
#pragma once

#include "Hittable.hpp"

class Sphere : public Hittable {
public:
    Sphere(Point3 center, float radius, std::shared_ptr<Material> material);

    auto hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool override;

    [[nodiscard]] auto
    bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool override;

private:

    static auto get_sphere_uv(const Point3 &point, float &y, float &v) -> void;

    Point3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};


