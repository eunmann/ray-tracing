
#pragma once

#include "Ray.hpp"
#include <memory>

class Material;

struct HitRecord {
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Material> material;
    float t{};
    bool front_face{};

    inline auto set_face_normal(const Ray &ray, const Vec3 &outward_normal) -> void {
        front_face = ray.direction().dot(outward_normal) < 0.0f;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    [[nodiscard]] virtual auto hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool = 0;
};


