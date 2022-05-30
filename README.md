# Ray Tracer

The purpose of this project is to learn and explore ray tracing. The code is based
on [Ray Tracing in One Weekend - The Book Series](https://raytracing.github.io/). After going through the entire series,
the plan is to follow up with optimizations to render faster and add features. For example, implementing better ray
tracing algorithms, scaling compute power (e.g. CPU multi-threading, GPU), code optimizations, adding in different
lighting, more geometry, etc.

# Implementation

The implementation is similar to what the series describes, except some personal flavor added in, and the
below-mentioned differences.

## SDL

Instead of using
the [PPM Image Format](https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/theppmimageformat)
as a render destination, this project uses [SDL](https://www.libsdl.org/) to open a window and render to the window. It
does not use any features other than opening a window and creating a texture to copy the rendered image into, then
rendering the texture in the window. The purpose of having a window is to be able to move the camera around to explore
the scene, rather than being confined into a just an image.

# TODO

Finish the rest of the second book, and then go through the third book.