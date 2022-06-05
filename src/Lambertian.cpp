
#include "Lambertian.hpp"
#include "SolidColor.hpp"

Lambertian::Lambertian(const Color &color) : Lambertian(std::make_shared<SolidColor>(color)) {

}

Lambertian::Lambertian(std::shared_ptr<Texture> texture) : m_albedo(texture) {

}

auto
Lambertian::scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool {
    auto scatter_direction = hit_record.normal + Vec3::random_unit_vector();

    // If the scatter direction is too small, it can lead to Infinities/NaNs later
    if (scatter_direction.is_near_zero()) {
        scatter_direction = hit_record.normal;
    }

    scattered = Ray(hit_record.point, scatter_direction, ray.time());
    attenuation = this->m_albedo->value(hit_record.u, hit_record.v, hit_record.point);
    return true;
}


