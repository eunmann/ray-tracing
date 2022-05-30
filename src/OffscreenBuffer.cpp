
#include <malloc.h>
#include "OffscreenBuffer.hpp"
#include <cmath>

auto OffscreenBuffer::get_memory() const -> unsigned char * {
    return m_memory;
}

auto OffscreenBuffer::get_width() const -> int {
    return m_width;
}

auto OffscreenBuffer::get_height() const -> int {
    return m_height;
}

auto OffscreenBuffer::get_bytes_per_pixel() const -> int {
    return m_bytes_per_pixel;
}

void OffscreenBuffer::set_memory(unsigned char *memory) {
    this->m_memory = memory;
}

void OffscreenBuffer::set_width(int width) {
    this->m_width = width;
}

void OffscreenBuffer::set_height(int height) {
    this->m_height = height;
}

void OffscreenBuffer::set_bytes_per_pixel(int bytes_per_pixel) {
    this->m_bytes_per_pixel = bytes_per_pixel;
}

void OffscreenBuffer::reallocate_buffer(int width, int height) {
    this->set_width(width);
    this->set_height(height);
    if (this->m_memory != nullptr) {
        free(this->m_memory);
    }

    this->m_memory = static_cast<unsigned char *>(malloc(this->get_buffer_size()));
}

auto OffscreenBuffer::get_buffer_size() const -> int {
    return this->m_width * this->m_height * this->m_bytes_per_pixel;
}

OffscreenBuffer::OffscreenBuffer(unsigned char *memory, const int width, const int height, const int bytes_per_pixel)
        : m_memory(memory),
          m_width(width),
          m_height(height),
          m_bytes_per_pixel(bytes_per_pixel) {
    this->reallocate_buffer(width, height);
}

auto OffscreenBuffer::set_color(int row, int col, const Color &color, const int samples_per_pixel) -> void {
    auto row_offset = ((this->m_height - 1 - row) * (this->m_width * this->m_bytes_per_pixel));
    auto col_offset = col * this->m_bytes_per_pixel;
    auto *pixel = this->m_memory + row_offset + col_offset;

    auto clamp = [](float value, float min, float max) -> float {
        if (value <= min) return min;
        if (value >= max) return max;
        return value;
    };
    auto scale = [samples_per_pixel](float color) -> float {
        auto scale = 1.0f / static_cast<float>(samples_per_pixel);
        return std::sqrt(scale * color);
    };

    auto transform_color = [&scale, &clamp](float color) -> unsigned char {
        color = scale(color);
        color = clamp(color, 0.0f, 1.0f) * 255.0f;
        return static_cast<unsigned char>(color);
    };

    pixel[0] = transform_color(color.x());
    pixel[1] = transform_color(color.y());
    pixel[2] = transform_color(color.z());
}
