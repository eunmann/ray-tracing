
#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(Point3 center, float radius, std::shared_ptr<Material> material) : m_center(center),
                                                                                  m_radius(radius),
                                                                                  m_material(material) {

}

auto Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool {

    auto oc = ray.origin() - this->m_center;
    auto a = ray.direction().length_squared();
    auto half_b = oc.dot(ray.direction());
    auto c = oc.length_squared() - this->m_radius * this->m_radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    hit_record.t = root;
    hit_record.point = ray.at(hit_record.t);
    auto outward_normal = (hit_record.point - this->m_center) / this->m_radius;
    hit_record.set_face_normal(ray, outward_normal);
    hit_record.material = this->m_material;

    return true;
}
