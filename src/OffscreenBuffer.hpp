
#pragma once

#include "Vec3.hpp"

class OffscreenBuffer {

public:
    OffscreenBuffer(unsigned char *memory, int width, int height, int bytes_per_pixel);

    [[nodiscard]] auto get_memory() const -> unsigned char *;

    [[nodiscard]] auto get_width() const -> int;

    [[nodiscard]] auto get_height() const -> int;

    [[nodiscard]] auto get_bytes_per_pixel() const -> int;

    auto set_memory(unsigned char *memory) -> void;

    auto set_width(int width) -> void;

    auto set_height(int height) -> void;

    auto set_bytes_per_pixel(int bytes_per_pixel) -> void;

    auto reallocate_buffer(int width, int height) -> void;

    [[nodiscard]] auto get_buffer_size() const -> int;

    auto set_color(int row, int col, const Color &color, int samples_per_pixel) -> void;

private:
    unsigned char *m_memory{};
    int m_width{};
    int m_height{};
    int m_bytes_per_pixel{};
};


