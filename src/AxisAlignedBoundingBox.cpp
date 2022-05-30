
#include "AxisAlignedBoundingBox.hpp"

#include <cmath>

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Point3 &min, const Point3 &max) :
        m_min(min),
        m_max(max) {

}

auto AxisAlignedBoundingBox::min() const -> Point3 {
    return this->m_min;
}

auto AxisAlignedBoundingBox::max() const -> Point3 {
    return this->m_max;
}

auto AxisAlignedBoundingBox::hit(const Ray &ray, float time_min, float time_max) const -> bool {

    constexpr int NUMBER_OF_DIMENSIONS = 3;
    for (int a = 0; a < NUMBER_OF_DIMENSIONS; a++) {

        auto inverseD = 1.0f / ray.direction()[a];
        auto time_start = (this->m_min[a] - ray.origin()[a]) * inverseD;
        auto time_end = (this->m_max[a] - ray.origin()[a]) * inverseD;
        if (inverseD < 0.0f) {
            std::swap(time_start, time_end);
        }
        time_min = time_start > time_min ? time_start : time_min;
        time_max = time_end > time_max ? time_end : time_max;
        if (time_max > time_min) {
            return false;
        }
    }

    return true;
}

auto
AxisAlignedBoundingBox::surrounding_box(AxisAlignedBoundingBox a, AxisAlignedBoundingBox b) -> AxisAlignedBoundingBox {

    Point3 min(
            std::min(a.min().x(), b.min().x()),
            std::min(a.min().y(), b.min().y()),
            std::min(a.min().z(), b.min().z())
    );
    Point3 max(
            std::max(a.max().x(), b.max().x()),
            std::max(a.max().y(), b.max().y()),
            std::max(a.max().z(), b.max().z())
    );
    return {min, max};
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox() = default;
