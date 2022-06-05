
#pragma once

#include "Texture.hpp"
#include <memory>

class CheckerTexture : public Texture {

public:
    CheckerTexture();

    CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);

    CheckerTexture(Color even, Color odd);

    auto value(float u, float v, const Point3 &point) const -> Color override;

    auto odd() -> std::shared_ptr<Texture>;

    auto even() -> std::shared_ptr<Texture>;

private:
    std::shared_ptr<Texture> m_odd;
    std::shared_ptr<Texture> m_even;

};


