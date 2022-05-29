
#pragma once

#include <memory>
#include <vector>

#include "Hittable.hpp"

class HittableList : public Hittable {
public:
    HittableList();

    explicit HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    auto hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record) const -> bool override;

private:
    std::vector<std::shared_ptr<Hittable>> objects;
};


