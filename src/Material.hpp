
#pragma once

#include "Ray.hpp"
#include "Hittable.hpp"

class Material {
public:
    virtual auto
    scatter(const Ray &ray, const HitRecord &hit_record, Color &attenuation, Ray &scattered) const -> bool = 0;
};


