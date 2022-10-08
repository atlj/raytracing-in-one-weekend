#include <iostream>
#include <fstream>
#include <chrono>

#include "utils.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"

using std::cout;
using std::chrono::steady_clock;

color ray_color(const ray &ray, const hittable &world)
{
    hit_record rec;
    if (world.hit(ray, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(ray.getDirection());
    auto distance = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - distance) * color(1.0, 1.0, 1.0) + distance * color(0.5, 0.7, 1.0);
}

int main()
{
    auto programStartTime = steady_clock::now();

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    std::ofstream image;
    image.open("image.ppm");

    // World
    auto world = hittable_list();
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

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

            color pixel_color = ray_color(r, world);
            write_color(image, pixel_color);
        }
        cout << (float(image_height - y) / float(image_height)) * 100.0 << "%\n"
             << std::flush;
    }
    image.close();
    cout << "Done in " << std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now() - programStartTime).count() << "ms" << std::endl;
}
