cmake_minimum_required(VERSION 3.21)
project(RayTracer)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_STANDARD 20)

include_directories(dep/SDL/include)
link_directories(dep/SDL/lib/x64)

add_executable(RayTracer src/main.cpp src/OffscreenBuffer.cpp src/OffscreenBuffer.hpp src/Vec3.cpp src/Vec3.hpp src/Ray.cpp src/Ray.hpp src/Camera.cpp src/Camera.hpp src/Hittable.cpp src/Hittable.hpp src/Sphere.cpp src/Sphere.hpp src/HittableList.cpp src/HittableList.hpp src/FormatUtils.cpp src/FormatUtils.hpp src/Timer.cpp src/Timer.hpp src/RNG.cpp src/RNG.hpp src/Material.cpp src/Material.hpp src/Lambertian.cpp src/Lambertian.hpp src/Metal.cpp src/Metal.hpp src/Dielectric.cpp src/Dielectric.hpp src/UnitConversions.cpp src/UnitConversions.hpp)


find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2main SDL2)

add_custom_command(TARGET RayTracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/dep/SDL/lib/x64"
        $<TARGET_FILE_DIR:RayTracer>)