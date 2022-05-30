
#include "HittableList.hpp"

#include <utility>

auto HittableList::hit(const Ray &r, float t_min, float t_max, HitRecord &hit_record) const -> bool {
    HitRecord hit_record_temp;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object: this->m_objects) {
        if (object->hit(r, t_min, closest_so_far, hit_record_temp)) {
            hit_anything = true;
            closest_so_far = hit_record_temp.t;
            hit_record = hit_record_temp;
        }
    }

    return hit_anything;
}

auto HittableList::bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool {
    if (this->m_objects.empty()) {
        return false;
    }

    AxisAlignedBoundingBox temp_box;
    auto first_box = true;

    for (const auto &hittable: this->m_objects) {
        if (!hittable->bounding_box(time_start, time_end, std::forward<AxisAlignedBoundingBox>(temp_box))) {
            return false;
        }

        output_box = first_box ? temp_box : AxisAlignedBoundingBox::surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

auto HittableList::objects() const -> std::vector<std::shared_ptr<Hittable>> {
    return this->m_objects;
}

HittableList::HittableList() = default;
