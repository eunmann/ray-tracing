
#include "Metal.hpp"

Metal::Metal(const Color &color, float fuzz) : m_albedo(color),
                                               m_fuzz(fuzz < 1.0f ? fuzz : 1.0f) {

}

auto Metal::scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool {
    auto reflected = ray.direction().unit_vector().reflect(hit_record.normal);
    scattered = {hit_record.point, reflected + this->m_fuzz * Vec3::random_in_unit_sphere(), ray.time()};
    attenuation = this->m_albedo;
    return (scattered.direction().dot(hit_record.normal) > 0);
}
