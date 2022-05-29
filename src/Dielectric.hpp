
#pragma once

#include "Material.hpp"

class Dielectric : public Material {
public:
    explicit Dielectric(float index_of_refraction);

    auto
    scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool override;

private:
    static auto reflectance(float cosine, float ref_index) -> float;

private:
    float m_index_of_refraction;
};


