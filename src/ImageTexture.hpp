
#pragma once

#include "Texture.hpp"

#include <string>

class ImageTexture : public Texture {
public:

    static constexpr int BYTES_PER_PIXEL = 3;

    explicit ImageTexture(std::string filename);

    ~ImageTexture();

    [[nodiscard]] auto value(float u, float v, const Point3 &point) const -> Color override;

private:
    unsigned char *m_data{};
    int m_width{};
    int m_height{};
    int m_bytes_per_scanline{};
};


