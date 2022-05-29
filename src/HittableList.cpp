
#include "HittableList.hpp"

auto HittableList::hit(const Ray &r, float t_min, float t_max, HitRecord &hit_record) const -> bool {
    HitRecord hit_record_temp;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object: objects) {
        if (object->hit(r, t_min, closest_so_far, hit_record_temp)) {
            hit_anything = true;
            closest_so_far = hit_record_temp.t;
            hit_record = hit_record_temp;
        }
    }

    return hit_anything;
}

HittableList::HittableList() = default;
