#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record
{
    point3 point;
    vec3 normal;
    double distance;
};

class hittable
{
public:
    virtual bool hit(const ray &r, double min_distance, double max_distance, hit_record &rec) const = 0;
};

#endif