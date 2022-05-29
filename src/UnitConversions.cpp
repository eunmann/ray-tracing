
#include "UnitConversions.hpp"

float UnitConversions::PI = 3.14f;

auto UnitConversions::degrees_to_radians(float degrees) -> float {
    return degrees * UnitConversions::PI / 180.0f;
}
