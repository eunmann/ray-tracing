
#include "Perlin.hpp"

#include "RNG.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

Perlin::Perlin() {

    this->m_random_vecs.resize(Perlin::POINT_COUNT);
    this->m_perm_x.resize(Perlin::POINT_COUNT);
    this->m_perm_y.resize(Perlin::POINT_COUNT);
    this->m_perm_z.resize(Perlin::POINT_COUNT);

    std::transform(this->m_random_vecs.begin(), this->m_random_vecs.end(), this->m_random_vecs.begin(),
                   [](Vec3 value) {
                       return Vec3::random(-1.0f, 1.0f).unit_vector();
                   });

    Perlin::fill(this->m_perm_x);
    Perlin::fill(this->m_perm_y);
    Perlin::fill(this->m_perm_z);
}

auto Perlin::noise(const Point3 &point) const -> float {

    auto u = point.x() - std::floor(point.x());
    auto v = point.y() - std::floor(point.y());
    auto w = point.z() - std::floor(point.z());

    // Hermitian Smoothing
    u = u * u * (3.0f - 2.0f * u);
    v = v * v * (3.0f - 2.0f * v);
    w = w * w * (3.0f - 2.0f * w);

    auto i = static_cast<int32_t>(std::floor(point.x()));
    auto j = static_cast<int32_t>(std::floor(point.y()));
    auto k = static_cast<int32_t>(std::floor(point.z()));

    Vec3 c[2][2][2];

    for (int di = 0; di < 2; di++) {
        for (int dj = 0; dj < 2; dj++) {
            for (int dk = 0; dk < 2; dk++) {
                c[di][dj][dk] = this->m_random_vecs[
                        this->m_perm_x[(i + di) & 255] ^
                        this->m_perm_y[(j + dj) & 255] ^
                        this->m_perm_z[(k + dk) & 255]
                ];
            }
        }
    }

    return Perlin::trilinear_interpolation(c, u, v, w);
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

auto Perlin::trilinear_interpolation(Vec3 (*c)[2][2], float u, float v, float w) -> float {

    auto uu = u * u * (3.0f - 2.0f * u);
    auto vv = v * v * (3.0f - 2.0f * v);
    auto ww = w * w * (3.0f - 2.0f * w);
    auto accum = 0.0f;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                Vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1.0f - i) * (1.0f - uu)) *
                         (j * vv + (1.0f - j) * (1.0f - vv)) *
                         (k * ww + (1.0f - k) * (1.0f - ww)) *
                         c[i][j][k].dot(weight_v);
            }
        }
    }

    return accum;
}

auto Perlin::turbulence(const Point3 &point, int depth) const -> float {
    auto accum = 0.0f;
    auto temp_p = point;
    auto weight = 1.0f;

    for (int i = 0; i < depth; i++) {
        accum += weight * this->noise(temp_p);
        weight *= 0.5f;
        temp_p *= 2.0f;
    }

    return std::fabs(accum);
}
