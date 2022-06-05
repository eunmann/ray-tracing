
#include "Perlin.hpp"

#include "RNG.hpp"
#include <algorithm>
#include <numeric>

Perlin::Perlin() {

    this->m_random_floats.resize(Perlin::POINT_COUNT);
    this->m_perm_x.resize(Perlin::POINT_COUNT);
    this->m_perm_y.resize(Perlin::POINT_COUNT);
    this->m_perm_z.resize(Perlin::POINT_COUNT);

    std::transform(this->m_random_floats.begin(), this->m_random_floats.end(), this->m_random_floats.begin(),
                   [](float value) {
                       return RNG::random_float();
                   });

    Perlin::fill(this->m_perm_x);
    Perlin::fill(this->m_perm_y);
    Perlin::fill(this->m_perm_z);
}

auto Perlin::noise(const Point3 &point) const -> float {

    auto i = static_cast<int32_t>(4.0f * point.x()) & 255;
    auto j = static_cast<int32_t>(4.0f * point.y()) & 255;
    auto k = static_cast<int32_t>(4.0f * point.z()) & 255;

    return this->m_random_floats[this->m_perm_x[i] ^ this->m_perm_y[j] ^ this->m_perm_z[k]];
}

auto Perlin::fill(std::vector<int32_t> &vector) -> void {

    std::iota(vector.begin(), vector.end(), 0);

    for (std::size_t i = vector.size() - 1; i > 0; i--) {
        auto target = RNG::random_int(0, i);
        auto temp = vector[i];
        vector[i] = vector[target];
        vector[target] = temp;
    }
}
