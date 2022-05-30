
#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"

class AxisAlignedBoundingBox {
public:
    AxisAlignedBoundingBox();

    AxisAlignedBoundingBox(const Point3 &min, const Point3 &max);

    [[nodiscard]] auto min() const -> Point3;

    [[nodiscard]] auto max() const -> Point3;

    [[nodiscard]] auto hit(const Ray &ray, float time_min, float time_max) const -> bool;

    auto static surrounding_box(AxisAlignedBoundingBox a, AxisAlignedBoundingBox b) -> AxisAlignedBoundingBox;

private:
    Point3 m_min;
    Point3 m_max;
};


