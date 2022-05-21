
#include "Win32OffscreenBuffer.hpp"

const BITMAPINFO &Win32OffscreenBuffer::get_bitmap_info() const {
    return bitmap_info;
}

void *Win32OffscreenBuffer::get_memory() const {
    return memory;
}

int Win32OffscreenBuffer::get_width() const {
    return width;
}

int Win32OffscreenBuffer::get_height() const {
    return height;
}

int Win32OffscreenBuffer::get_pitch() const {
    return pitch;
}

int Win32OffscreenBuffer::get_bytes_per_pixel() const {
    return bytes_per_pixel;
}
