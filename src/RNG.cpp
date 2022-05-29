
#include "RNG.hpp"

#include <random>

auto RNG::random_float() -> float {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

auto RNG::random_float(float min, float max) -> float {
    return min + (max - min) * RNG::random_float();
}
