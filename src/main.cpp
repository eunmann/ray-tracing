#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <cinttypes>
#include "Win32Window.hpp"
#include "Win32OffscreenBuffer.hpp"

static constexpr int BYTES_PER_PIXEL = 4;

void render(int xOffset, int yOffset){
    int pitch = bitmapWidth * BYTES_PER_PIXEL;
    auto* row = (uint8_t *)bitmapMemory;
    for(int r = 0; r < bitmapHeight; r++){
        auto* pixel = (uint8_t *)row;
        for(int c = 0; c < bitmapWidth; c++){

            // BLUE
            *pixel = xOffset;
            pixel++;

            // GREEN
            *pixel = 255;
            pixel++;

            // REDs
            *pixel = 0;
            pixel++;

            // ALPHA
            *pixel = 0;
            pixel++;
        }
        row += pitch;
    }
}


void updateWindow(HDC deviceContext, int width, int height) {

    StretchDIBits(deviceContext,
                  0, 0, width, height,
                  0, 0, width, height,
                  bitmapMemory, &bitmapinfo,
                  DIB_RGB_COLORS,SRCCOPY);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    Win32Window window(hInstance, hPrevInstance, nCmdShow);
    Win32OffscreenBuffer offscreenBuffer{};

    // Run the message loop.

    MSG message = {};
    auto running = true;
    int xOffset = 0;
    int yOffset = 0;
    while (running) {

        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0) {

            if (message.message == WM_QUIT) {
                running = false;
            }

            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        render(xOffset++, 0);
        HDC deviceContext = GetDC(handleWindow);
        RECT clientRect;
        GetClientRect(handleWindow, &clientRect);
        int windowWidth = clientRect.right - clientRect.left;
        int windowHeight = clientRect.bottom - clientRect.top;
        updateWindow(deviceContext, clientRect, 0, 0, windowWidth, windowHeight);
        ReleaseDC(handleWindow, deviceContext);
    }

    return 0;
}