
#pragma once

class RNG {
public:
    auto static random_float() -> float;

    auto static random_float(float min, float max) -> float;

    auto static random_int() -> int;

    auto static random_int(int min, int max) -> int;

};


