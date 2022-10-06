#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    point3 center;
    double radius;

    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r){};

    virtual bool hit(const ray &r, double min_distance, double max_distance, hit_record &rec) const override;
};

bool sphere::hit(const ray &r, double min_distance, double max_distance, hit_record &rec) const
{
    vec3 centerToOrigin = r.getOrigin() - center;
    // a, b and c stands for ax_2 + bx + c = 0
    // discriminant = b_2 - 4ac
    // And don't forget if our discriminant is negative, we don't have any real roots so we pass the sphere
    // Our final equation is: direction_2*distance_2 + 2* direction*distance*(origin-center) + (origin-center)_2 - radius_2 = 0
    // This means a is direction_2, b is 2*direction*(origin-center) and c is (origin-center)_2 - radius_2
    auto a = r.getDirection().length_squared();
    auto half_b = dot(centerToOrigin, r.getDirection());
    auto c = centerToOrigin.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    auto square_root_discriminant = sqrt(discriminant);

    auto root = (-half_b - square_root_discriminant) / a;
    if (root < min_distance || max_distance < root)
    {
        root = (-half_b + square_root_discriminant) / a;
        if (root < min_distance || max_distance < root)
            return false;
    }

    rec.distance = root;
    rec.point = r.at(rec.distance);
    rec.normal = (rec.point - center) / radius;
    vec3 outward_normal_unit = (rec.point - center) / radius;
    rec.set_face_normal(r, outward_normal_unit);
}

#endif