
#pragma once

#include "Texture.hpp"
#include "Perlin.hpp"

class NoiseTexture : public Texture {

public:
    NoiseTexture();

    explicit NoiseTexture(float scale);

    [[nodiscard]] auto value(float u, float v, const Point3 &point) const -> Color override;

private:
    Perlin m_noise;
    float m_scale{};
};


