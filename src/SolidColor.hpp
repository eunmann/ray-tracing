
#pragma once

#include "Texture.hpp"

class SolidColor : public Texture {
public:
    SolidColor();

    explicit SolidColor(Color color);

    SolidColor(float red, float green, float blue);

    [[nodiscard]] auto value(float u, float v, const Point3 &point) const -> Color override;

private:
    Color m_color;
};


