#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(
        const ray &r, double min_distance, double max_distance, hit_record &rec) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, double min_distance, double max_distance, hit_record &rec) const
{
    hit_record temp_rec;
    bool did_hit_anything = false;
    auto closest_so_far = max_distance;

    for (const auto &object : objects)
    {
        if (object->hit(r, min_distance, closest_so_far, temp_rec))
        {
            did_hit_anything = true;
            closest_so_far = temp_rec.distance;
            rec = temp_rec;
        }
    }

    return did_hit_anything;
}

#endif