
#include "CheckerTexture.hpp"

#include "SolidColor.hpp"
#include <cmath>

CheckerTexture::CheckerTexture() = default;

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) : m_even(even),
                                                                                              m_odd(odd) {

}

CheckerTexture::CheckerTexture(Color even, Color odd) : CheckerTexture(std::make_shared<SolidColor>(even),
                                                                       std::make_shared<SolidColor>(odd)) {

}

auto CheckerTexture::value(float u, float v, const Point3 &point) const -> Color {
    auto sines = std::sin(10.0f * point.x()) * std::sin(10.0f * point.y()) * std::sin(10.0f * point.z());
    if (sines < 0) {
        return this->m_odd->value(u, v, point);
    } else {
        return this->m_even->value(u, v, point);
    }
}
