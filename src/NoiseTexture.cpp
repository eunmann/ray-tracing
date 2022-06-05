
#include "NoiseTexture.hpp"

#include <cmath>

NoiseTexture::NoiseTexture() = default;

auto NoiseTexture::value(float u, float v, const Point3 &point) const -> Color {
    //return Color{1.0f, 1.0f, 1.0f} * this->m_noise.turbulence(this->m_scale * point);
    return Color{1.0f, 1.0f, 1.0f} * 0.5f *
           (1.0f + std::sin(this->m_scale * point.z() + 10.0f * this->m_noise.turbulence(point)));
}

NoiseTexture::NoiseTexture(float scale) : m_scale(scale) {

}


