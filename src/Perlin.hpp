
#pragma once

#include <vector>
#include <cinttypes>
#include "Vec3.hpp"

class Perlin {

public:
    Perlin();

    [[nodiscard]] auto noise(const Point3 &point) const -> float;

private:
    static auto fill(std::vector<int32_t> &vector) -> void;

private:
    static constexpr auto POINT_COUNT = 256;
    std::vector<float> m_random_floats;
    std::vector<int32_t> m_perm_x;
    std::vector<int32_t> m_perm_y;
    std::vector<int32_t> m_perm_z;
};


