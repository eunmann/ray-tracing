
#include "ImageTexture.hpp"

#include "STB.h"
#include "MathUtils.hpp"

ImageTexture::ImageTexture(std::string filename) {

    auto channels_in_file = 3;
    this->m_data = stbi_load(filename.c_str(), &this->m_width, &this->m_height, &channels_in_file,
                             ImageTexture::BYTES_PER_PIXEL);

    if (this->m_data == nullptr) {
        printf("Could not load texture image file %s\n", filename.c_str());
        this->m_width = this->m_height = 0;
    }

    this->m_bytes_per_scanline = ImageTexture::BYTES_PER_PIXEL * this->m_width;

}

ImageTexture::~ImageTexture() {
    if (this->m_data != nullptr) {
        stbi_image_free(this->m_data);
        this->m_data = nullptr;
    }
}

auto ImageTexture::value(float u, float v, const Point3 &point) const -> Color {
    // If we have no texture data, then return solid cyan as a debugging aid.
    if (this->m_data == nullptr) {
        return {0.0f, 1.0f, 1.0f};
    }

    // Clamp input texture coordinates to [0,1] x [1,0]
    u = MathUtils::clamp(u, 0.0f, 1.0f);
    v = 1.0f - MathUtils::clamp(v, 0.0f, 1.0f);  // Flip V to image coordinates

    auto i = static_cast<int>(u * this->m_width);
    auto j = static_cast<int>(v * this->m_height);

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= this->m_width) i = this->m_width - 1.0f;
    if (j >= this->m_height) j = this->m_height - 1.0f;

    const auto color_scale = 1.0f / 255.0f;
    auto pixel = this->m_data + j * this->m_bytes_per_scanline + i * ImageTexture::BYTES_PER_PIXEL;

    return {color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]};
}
