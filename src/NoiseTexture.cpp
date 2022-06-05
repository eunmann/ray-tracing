
#include "NoiseTexture.hpp"

NoiseTexture::NoiseTexture() = default;

auto NoiseTexture::value(float u, float v, const Point3 &point) const -> Color {
    return Color{1.0f, 1.0f, 1.0f} * this->m_noise.noise(point);
}


