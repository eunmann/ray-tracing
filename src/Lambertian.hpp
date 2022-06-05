
#pragma once

#include "Material.hpp"
#include "Texture.hpp"

class Lambertian : public Material {
public:
    explicit Lambertian(const Color &color);

    Lambertian(std::shared_ptr<Texture> texture);

    auto
    scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool override;

private:
    std::shared_ptr<Texture> m_albedo;
};


