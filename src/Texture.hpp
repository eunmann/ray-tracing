
#pragma once

#include "Vec3.hpp"

class Texture {
public:
    [[nodiscard]] virtual auto value(float u, float v, const Point3 &point) const -> Color = 0;
};


