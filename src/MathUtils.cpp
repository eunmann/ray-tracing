
#include "MathUtils.hpp"

auto MathUtils::clamp(float value, float min, float max) -> float {
    if (value <= min) return min;
    if (value >= max) return max;
    return value;
}
