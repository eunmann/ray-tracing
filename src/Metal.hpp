
#pragma once

#include "Material.hpp"

class Metal : public Material {
public:
    explicit Metal(const Color &color, float fuzz);

    auto
    scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool override;

private:
    Color m_albedo;
    float m_fuzz;
};


