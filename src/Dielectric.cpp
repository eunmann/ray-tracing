
#include <cmath>
#include "Dielectric.hpp"
#include "RNG.hpp"

Dielectric::Dielectric(float index_of_refraction) : m_index_of_refraction(index_of_refraction) {

}

auto
Dielectric::scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool {
    attenuation = {1.0f, 1.0f, 1.0f};
    auto refraction_ratio = hit_record.front_face ? (1.0f / this->m_index_of_refraction)
                                                  : this->m_index_of_refraction;

    auto unit_direction = ray.direction().unit_vector();
    float cos_theta = std::fmin((-unit_direction).dot(hit_record.normal), 1.0f);
    float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > RNG::random_float())
        direction = unit_direction.reflect(hit_record.normal);
    else
        direction = unit_direction.refract(hit_record.normal, refraction_ratio);

    scattered = {hit_record.point, direction, ray.time()};
    return true;
}

auto Dielectric::reflectance(float cosine, float ref_index) -> float {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1.0f - ref_index) / (1.0f + ref_index);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
}
