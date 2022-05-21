cmake_minimum_required(VERSION 3.21)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer WIN32 src/main.cpp src/Win32Window.cpp src/Win32Window.hpp src/Win32OffscreenBuffer.cpp src/Win32OffscreenBuffer.hpp)
