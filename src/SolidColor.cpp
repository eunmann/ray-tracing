
#include "SolidColor.hpp"

SolidColor::SolidColor() = default;

SolidColor::SolidColor(Color color) : m_color(color) {

}

SolidColor::SolidColor(float red, float green, float blue) : m_color(red, green, blue) {

}

auto SolidColor::value(float u, float v, const Point3 &point) const -> Color {
    return this->m_color;
}


