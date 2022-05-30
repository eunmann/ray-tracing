
#include "MovingSphere.hpp"

#include <cmath>

MovingSphere::MovingSphere(Point3 center_start, Point3 center_end, float time_start, float time_end, float radius,
                           std::shared_ptr<Material> material) :
        m_center_start(center_start),
        m_center_end(center_end),
        m_time_start(time_start),
        m_time_end(time_end),
        m_radius(radius),
        m_material(material) {

}

auto MovingSphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool {
    auto oc = ray.origin() - this->center(ray.time());
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
    auto outward_normal = (hit_record.point - this->center(ray.time())) / this->m_radius;
    hit_record.set_face_normal(ray, outward_normal);
    hit_record.material = this->m_material;

    return true;
}

auto MovingSphere::center(float time) const -> Point3 {
    return this->m_center_start + ((time - this->m_time_start) / (this->m_time_end - this->m_time_start)) *
                                  (this->m_center_end - this->m_center_start);
}

auto MovingSphere::bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool {
    auto box_start = AxisAlignedBoundingBox{
            this->center(time_start) - Vec3{this->m_radius, this->m_radius, this->m_radius},
            this->center(time_start) + Vec3{this->m_radius, this->m_radius, this->m_radius}
    };

    auto box_end = AxisAlignedBoundingBox{
            this->center(time_end) - Vec3{this->m_radius, this->m_radius, this->m_radius},
            this->center(time_end) + Vec3{this->m_radius, this->m_radius, this->m_radius}
    };

    output_box = AxisAlignedBoundingBox::surrounding_box(box_start, box_end);
    return true;
}
