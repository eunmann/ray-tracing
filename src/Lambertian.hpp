
#pragma once

#include "Material.hpp"

class Lambertian : public Material {
public:
    explicit Lambertian(const Color &color);

    auto
    scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool override;

private:
    Color m_albedo;
};


