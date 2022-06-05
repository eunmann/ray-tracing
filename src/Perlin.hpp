
#pragma once

#include <vector>
#include <cinttypes>
#include "Vec3.hpp"

class Perlin {

public:
    Perlin();

    [[nodiscard]] auto noise(const Point3 &point) const -> float;

    [[nodiscard]] auto turbulence(const Point3 &point, int depth = 7) const -> float;

private:
    static auto fill(std::vector<int32_t> &vector) -> void;

    [[maybe_unused]] static auto trilinear_interpolation(Vec3 c[2][2][2], float u, float v, float w) -> float;

private:
    static constexpr auto POINT_COUNT = 256;
    std::vector<Vec3> m_random_vecs;
    std::vector<int32_t> m_perm_x;
    std::vector<int32_t> m_perm_y;
    std::vector<int32_t> m_perm_z;
};


