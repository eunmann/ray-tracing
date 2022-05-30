
#include "Lambertian.hpp"

Lambertian::Lambertian(const Color &color) :
        m_albedo(color) {

}

auto
Lambertian::scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool {
    auto scatter_direction = hit_record.normal + Vec3::random_unit_vector();

    // If the scatter direction is too small, it can lead to Infinities/NaNs later
    if (scatter_direction.is_near_zero()) {
        scatter_direction = hit_record.normal;
    }

    scattered = Ray(hit_record.point, scatter_direction, ray.time());
    attenuation = this->m_albedo;
    return true;
}
