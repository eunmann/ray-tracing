#include <SDL.h>
#include <cstdio>

#include "OffscreenBuffer.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Timer.hpp"
#include <memory>
#include "RNG.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dielectric.hpp"
#include "MovingSphere.hpp"

constexpr auto aspect_ratio = 16.0f / 9.0f;
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

auto ray_Color(const Ray &ray, const Hittable &world, const int depth) -> Color {

    if (depth <= 0) {
        return {0.0f, 0.0f, 0.0f};
    }

    HitRecord hit_record;
    // t=0.001 to ignore hits very near 0 to remove shadow acne
    if (world.hit(ray, 0.001f, infinity, hit_record)) {
        Ray scattered{{},
                      {},
                      ray.time()};
        Color attenuation;
        if (hit_record.material->scatter(ray, hit_record, attenuation, scattered)) {
            return attenuation * ray_Color(scattered, world, depth - 1);
        } else {
            return {};
        }
    }
    auto unit_direction = ray.direction().unit_vector();
    auto time = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - time) * Color(1.0f, 1.0f, 1.0f) + time * Color(0.5f, 0.7f, 1.0f);

}

auto render(OffscreenBuffer &offscreen_buffer, const Hittable &world, const Camera &camera) -> void {

    Timer timer{"Render"};
    auto width = offscreen_buffer.get_width();
    auto height = offscreen_buffer.get_height();
    constexpr auto samples_per_pixel = 1000;
    constexpr auto max_depth = 50;

#pragma omp parallel for num_threads(24)
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            auto color = Color{};

            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (float(col) + RNG::random_float()) / (static_cast<float>(width) - 1.0f);
                auto v = (float(row) + RNG::random_float()) / (static_cast<float>(height) - 1.0f);

                Ray ray = camera.get_ray(u, v);
                color += ray_Color(ray, world, max_depth);
            }

            offscreen_buffer.set_color(row, col, color, samples_per_pixel);
        }
    }
    timer.end();
    timer.print();
}

auto
render_to_screen(uint32_t windowId, OffscreenBuffer &offscreen_buffer, const Hittable &world, const Camera &camera) {
    SDL_Window *window = SDL_GetWindowFromID(windowId);
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             offscreen_buffer.get_width(),
                                             offscreen_buffer.get_height());

    if (texture == nullptr) {
        printf("Failed to allocate texture\n");
    }

    render(offscreen_buffer, world, camera);

    auto pitch = offscreen_buffer.get_width() * offscreen_buffer.get_bytes_per_pixel();
    if (SDL_UpdateTexture(texture,
                          nullptr,
                          offscreen_buffer.get_memory(),
                          pitch)) {
        printf("Failed to update texture\n");
    }

    SDL_RenderCopy(renderer,
                   texture,
                   nullptr,
                   nullptr);
    SDL_RenderPresent(renderer);

    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

auto handle_event(SDL_Event *Event, OffscreenBuffer &offscreen_buffer, const Hittable &world, Camera &camera) -> bool {
    auto shouldRun = true;

    switch (Event->type) {
        case SDL_QUIT: {
            printf("SDL_QUIT\n");
            shouldRun = false;
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            printf("SDL_MOUSEBUTTONDOWN\n");
            //camera.set_origin(camera.origin() + Vec3{0.1f, 0.1f, 0.1f});
            //render_to_screen(Event->window.windowID, offscreen_buffer, world, camera);
            break;
        }

        case SDL_WINDOWEVENT: {
            switch (Event->window.event) {
                case SDL_WINDOWEVENT_RESIZED: {
                    auto window_width = Event->window.data1;
                    auto window_height = Event->window.data2;
                    printf("SDL_WINDOWEVENT_RESIZED %dx%d\n", window_width, window_height);
                    offscreen_buffer.reallocate_buffer(window_width, window_height);
                    break;
                }

                case SDL_WINDOWEVENT_EXPOSED: {
                    printf("SDL_WINDOWEVENT_EXPOSED\n");

                    static auto shouldRender = true;
                    if (shouldRender) {
                        shouldRender = false;
                        render_to_screen(Event->window.windowID, offscreen_buffer, world, camera);
                    }
                    break;
                }
            }
            break;
        }

    }
    return shouldRun;
}

auto random_scene() -> HittableList {
    HittableList world;

    auto ground_Material = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(Point3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_Material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RNG::random_float();
            Point3 center(a + 0.9f * RNG::random_float(), 0.2f, b + 0.9f * RNG::random_float());

            if ((center - Point3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center_end = center + Vec3{0.0f, RNG::random_float(0.0f, 0.5f), 0.0f};
                    world.add(make_shared<MovingSphere>(center, center_end, 0.0f, 1.0f, 0.2f, sphere_material));

                } else if (choose_mat < 0.95f) {
                    // Metal
                    auto albedo = Color::random(0.5f, 1.0f);
                    auto fuzz = RNG::random_float(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5f);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    auto Material1 = std::make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(Point3(0.0f, 1.0f, 0.0f), 1.0f, Material1));

    auto Material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(Point3(-4.0f, 1.0f, 0.0f), 1.0f, Material2));

    auto Material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(Point3(4.0f, 1.0f, 0.0f), 1.0f, Material3));

    return world;
}

// 4.0

auto main(int argc, char **argv) -> int {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL failed to initialize\n");
        return 1;
    }

    constexpr auto window_width = 1920;
    constexpr auto window_height = static_cast<int>(window_width / aspect_ratio);
    auto *window = SDL_CreateWindow("Ray Tracer",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    window_width,
                                    window_height,
                                    SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        printf("Failed to create window\n");
        return 1;
    }

    constexpr auto AUTO_DETECT_DRIVER = -1;
    constexpr auto RENDER_FLAGS = 0;
    auto *renderer = SDL_CreateRenderer(window, AUTO_DETECT_DRIVER, RENDER_FLAGS);
    if (renderer == nullptr) {
        printf("Failed to create renderer\n");
        return 1;
    }

    constexpr int bytes_per_pixel = 4;
    OffscreenBuffer offscreen_buffer{
            nullptr,
            window_width,
            window_height,
            bytes_per_pixel
    };

    Point3 look_from(13.0f, 2.0f, 3.0f);
    Point3 look_at(0.0f, 0.0f, 0.0f);
    Vec3 up_vector(0.0f, 1.0f, 0.0f);
    auto dist_to_focus = 10.0f;
    auto aperture = 0.1f;
    Camera camera{look_from, look_at, up_vector, 20.0f, aspect_ratio, aperture, dist_to_focus, 0.0f, 1.0f};

//    auto Material_ground = std::make_shared<Lambertian>(Color{0.8f, 0.8f, 0.0f});
//    auto Material_center = std::make_shared<Lambertian>(Color{0.1f, 0.2f, 0.5f});
//    auto Material_left = std::make_shared<Dielectric>(1.5f);
//    auto Material_right = std::make_shared<Metal>(Color{0.8f, 0.6f, 0.2f}, 0.0f);

    HittableList world = random_scene();
//    HittableList world;
//    world.add(make_shared<Sphere>(Point3{0.0f, -100.5f, -1.0f}, 100.0f, Material_ground));
//    world.add(make_shared<Sphere>(Point3{0.0f, 0.0f, -1.0f}, 0.5f, Material_center));
//    world.add(make_shared<Sphere>(Point3{-1.0f, 0.0f, -1.0f}, 0.5f, Material_left));
//    world.add(make_shared<Sphere>(Point3{-1.0f, 0.0f, -1.0f}, -0.45f, Material_left));
//    world.add(make_shared<Sphere>(Point3{1.0f, 0.0f, -1.0f}, 0.5f, Material_right));

    auto shouldRun = true;
    while (shouldRun) {
        SDL_Event Event;
        SDL_WaitEvent(&Event);
        shouldRun = handle_event(&Event, offscreen_buffer, world, camera);
    }

    SDL_Quit();
    return 0;
}