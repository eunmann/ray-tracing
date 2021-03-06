
#include "Sphere.hpp"
#include <cmath>
#include <numbers>

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
    Sphere::get_sphere_uv(outward_normal, hit_record.u, hit_record.v);
    hit_record.material = this->m_material;

    return true;
}

auto Sphere::bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool {

    output_box = {
            this->m_center - Vec3{this->m_radius, this->m_radius, this->m_radius},
            this->m_center + Vec3{this->m_radius, this->m_radius, this->m_radius}
    };
    return true;
}

auto Sphere::get_sphere_uv(const Point3 &point, float &u, float &v) -> void {
    constexpr float pi = std::numbers::pi;

    auto theta = acos(-point.y());
    auto phi = atan2(-point.z(), point.x()) + pi;

    u = phi / (2.0f * pi);
    v = theta / pi;
}
