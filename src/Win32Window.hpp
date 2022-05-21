
#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <cstdio>

struct Win32WindowDimension {
    int width;
    int height;
};

class Win32Window {
public:
    Win32Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, int nCmdShow){

        // Register the window class.
        const wchar_t CLASS_NAME[] = L"Sample Window Class";

        WNDCLASS windowClass = {};

        windowClass.lpfnWndProc = this->WindowProc;
        windowClass.hInstance = hInstance;
        windowClass.lpszClassName = CLASS_NAME;

        RegisterClass(&windowClass);

        // Create the window.

        this->handleWindow = CreateWindowEx(
                0,                              // Optional window styles.
                CLASS_NAME,                     // Window class
                L"Ray Tracing",    // Window text
                WS_OVERLAPPEDWINDOW,            // Window style

                // Size and position
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                nullptr,       // Parent window
                nullptr,       // Menu
                hInstance,  // Instance handle
                nullptr        // Additional application data
        );

        if (this->handleWindow == nullptr) {
            printf("Unable to create Window\n");
        }

        ShowWindow(handleWindow, nCmdShow);
    }

    LRESULT CALLBACK WindowProc(HWND handleWindowLocal, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {

            case WM_SIZE: {
                Win32WindowDimension windowDimension = this->getWindowDimension();
                resizeDIBSection(windowDimension.width, windowDimension.height);
                return 0;
            }
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(handleWindowLocal, &ps);
                int x = ps.rcPaint.left;
                int y = ps.rcPaint.top;

                Win32WindowDimension windowDimension = this->getWindowDimension();
                updateWindow(hdc, windowDimension.width, windowDimension.height);
                EndPaint(handleWindowLocal, &ps);
                return 0;
            }
        }
        return DefWindowProc(handleWindowLocal, uMsg, wParam, lParam);
    }

    void resizeDIBSection(int width, int height) {
        bitmapinfo.bmiHeader.biSize = sizeof(bitmapinfo.bmiHeader);
        bitmapinfo.bmiHeader.biWidth = width;
        bitmapinfo.bmiHeader.biHeight = -height;
        bitmapinfo.bmiHeader.biPlanes = 1;
        bitmapinfo.bmiHeader.biBitCount = 32;
        bitmapinfo.bmiHeader.biCompression = BI_RGB;

        if (bitmapMemory) {
            VirtualFree(bitmapMemory, 0, MEM_RELEASE);
        }

        bitmapWidth = width;
        bitmapHeight = height;

        const int memorySize = BYTES_PER_PIXEL * width * height;
        bitmapMemory = VirtualAlloc(nullptr, memorySize, MEM_COMMIT, PAGE_READWRITE);
    }

    Win32WindowDimension getWindowDimension(){
        RECT clientRect;
        GetClientRect(handleWindow, &clientRect);
        int windowWidth = clientRect.right - clientRect.left;
        int windowHeight = clientRect.bottom - clientRect.top;
        return {windowWidth, windowHeight};
    }

private:
    HWND handleWindow;
    BITMAPINFO bitmapinfo;
    void *bitmapMemory;
    int bitmapWidth;
    int bitmapHeight;
};


