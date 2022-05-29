
#pragma once

#include "Hittable.hpp"

class Sphere : public Hittable {
public:
    Sphere(Point3 center, float radius, std::shared_ptr<Material> material);

    auto hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool override;

private:
    Point3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};


