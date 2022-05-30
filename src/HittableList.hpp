
#pragma once

#include <memory>
#include <vector>

#include "Hittable.hpp"

class HittableList : public Hittable {
public:
    HittableList();

    explicit HittableList(std::shared_ptr<Hittable> hittable) { add(hittable); }

    void clear() { this->m_objects.clear(); }

    void add(std::shared_ptr<Hittable> hittable) { this->m_objects.push_back(hittable); }

    auto hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool override;

    [[nodiscard]] auto
    bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool override;

    [[nodiscard]] auto objects() const -> std::vector<std::shared_ptr<Hittable>>;

private:
    std::vector<std::shared_ptr<Hittable>> m_objects;
};


