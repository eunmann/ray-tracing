
#pragma once

#include "Hittable.hpp"
#include "HittableList.hpp"

class BoundingVolumeHierarchy : public Hittable {
public:
    BoundingVolumeHierarchy();

    BoundingVolumeHierarchy(const HittableList &hittable_list, float time_start, float time_end);

    BoundingVolumeHierarchy(const std::vector<std::shared_ptr<Hittable>> &src_objects,
                            std::size_t start, std::size_t end, float time_start, float time_end);

    [[nodiscard]] auto
    hit(const Ray &ray, float time_min, float time_max, HitRecord &hit_record) const -> bool override;

    [[nodiscard]] auto
    bounding_box(float time_start, float time_end, AxisAlignedBoundingBox &&output_box) const -> bool override;

    [[nodiscard]] auto left() const -> std::shared_ptr<Hittable>;

    [[nodiscard]] auto right() const -> std::shared_ptr<Hittable>;

    [[nodiscard]] auto box() const -> AxisAlignedBoundingBox;

private:
    std::shared_ptr<Hittable> m_left;
    std::shared_ptr<Hittable> m_right;
    AxisAlignedBoundingBox m_box;
};


