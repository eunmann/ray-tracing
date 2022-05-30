
#include "BoundingVolumeHierarchy.hpp"

#include <algorithm>
#include <utility>

BoundingVolumeHierarchy::BoundingVolumeHierarchy() = default;

BoundingVolumeHierarchy::BoundingVolumeHierarchy(const HittableList &hittable_list, float time_start, float time_end)
        : BoundingVolumeHierarchy(hittable_list.objects(), 0, hittable_list.objects().size(), time_start, time_end) {

}

inline auto box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) -> bool {
    AxisAlignedBoundingBox box_a;
    AxisAlignedBoundingBox box_b;

    if (!a->bounding_box(0, 0, std::forward<AxisAlignedBoundingBox>(box_a)) ||
        !b->bounding_box(0, 0, std::forward<AxisAlignedBoundingBox>(box_b)))
        printf("No bounding box in bvh_node constructor.\n");

    return box_a.min()[axis] < box_b.min()[axis];
}

auto box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) -> bool {
    return box_compare(a, b, 0);
}

auto box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) -> bool {
    return box_compare(a, b, 1);
}

auto box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) -> bool {
    return box_compare(a, b, 2);
}

BoundingVolumeHierarchy::BoundingVolumeHierarchy(const std::vector<std::shared_ptr<Hittable>> &src_objects,
                                                 std::size_t start, std::size_t end, float time_start, float time_end) {
    auto objects = src_objects;

    auto axis = RNG::random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
                                  : (axis == 1) ? box_y_compare
                                                : box_z_compare;
    auto object_span = end - start;

    if (object_span == 1) {
        this->m_left = this->m_right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            this->m_left = objects[start];
            this->m_right = objects[start + 1];
        } else {
            this->m_left = objects[start + 1];
            this->m_right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        this->m_left = std::make_shared<BoundingVolumeHierarchy>(objects, start, mid, time_start, time_end);
        this->m_right = std::make_shared<BoundingVolumeHierarchy>(objects, mid, end, time_start, time_end);
    }

    AxisAlignedBoundingBox box_left;
    AxisAlignedBoundingBox box_right;

    if (!this->m_left->bounding_box(time_start, time_end, std::forward<AxisAlignedBoundingBox>(box_left)) ||
        !this->m_right->bounding_box(time_start, time_end, std::forward<AxisAlignedBoundingBox>(box_right))) {
        printf("No bounding box in BoundingVolumeHierarchy constructor.\n");
    }

    this->m_box = AxisAlignedBoundingBox::surrounding_box(box_left, box_right);
}

auto BoundingVolumeHierarchy::hit(const Ray &ray, float time_min, float time_max, HitRecord &hit_record) const -> bool {
    if (!this->m_box.hit(ray, time_min, time_max)) {
        return false;
    }

    auto hit_left = this->m_left->hit(ray, time_min, time_max, hit_record);
    auto hit_right = this->m_right->hit(ray, time_min, hit_left ? hit_record.t : time_max, hit_record);

    return hit_left || hit_right;
}

auto BoundingVolumeHierarchy::bounding_box(float time_start, float time_end,
                                           AxisAlignedBoundingBox &&output_box) const -> bool {
    return false;
}

auto BoundingVolumeHierarchy::left() const -> std::shared_ptr<Hittable> {
    return this->m_left;
}

auto BoundingVolumeHierarchy::right() const -> std::shared_ptr<Hittable> {
    return this->m_right;
}

auto BoundingVolumeHierarchy::box() const -> AxisAlignedBoundingBox {
    return this->m_box;
}
