#include <iostream>
#include <fstream>
#include <chrono>

#include "vec3.h"
#include "color.h"
#include "ray.h"

using std::cout;
using std::chrono::steady_clock;

point3 sphere_center = point3(0, 0, -1);

double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = r.getOrigin() - center;
    auto a = dot(r.getDirection(), r.getDirection());
    auto b = 2.0 * dot(oc, r.getDirection());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return -1;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

color ray_color(const ray &ray)
{
    auto distance = hit_sphere(sphere_center, 0.5, ray);
    if (distance > 0.0)
    {
        vec3 normal = unit_vector(ray.at(distance) - sphere_center);
        return (0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1));
    }
    vec3 unit_direction = unit_vector(ray.getDirection());
    distance = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - distance) * color(1.0, 1.0, 1.0) + distance * color(0.5, 0.7, 1.0);
}

int main()
{
    auto programStartTime = steady_clock::now();

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    std::ofstream image;
    image.open("image.ppm");

    // Render
    image << "P3\n"
          << image_width << " " << image_height << "\n255\n";

    for (int y = image_height - 1; y > -1; --y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            auto u = double(x) / (image_width - 1);
            auto v = double(y) / (image_height - 1);
            ray r = ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);

            color pixel_color = ray_color(r);
            write_color(image, pixel_color);
        }
        cout << (float(image_height - y) / float(image_height)) * 100.0 << "%\n"
             << std::flush;
    }
    image.close();
    cout << "Done in " << std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now() - programStartTime).count() << "ms" << std::endl;
}
