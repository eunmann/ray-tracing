
#pragma once

#include <Windows.h>

class Win32OffscreenBuffer {

public:
    const BITMAPINFO &get_bitmap_info() const;

    void *get_memory() const;

    int get_width() const;

    int get_height() const;

    int get_pitch() const;

    int get_bytes_per_pixel() const;

private:
    BITMAPINFO bitmap_info;
    void* memory;
    int width;
    int height;
    int pitch;
    int bytes_per_pixel;
};


