#include <iostream>
#include <fstream>
#include <chrono>

#include "utils.h"
#include "vec3.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

using std::cout;
using std::chrono::steady_clock;

color ray_color(const ray &r, const hittable &world, int depth)
{
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec))
    {
        point3 target = rec.point + rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.point, target - rec.point), world, depth - 1);
    }

    vec3 unit_direction = unit_vector(r.getDirection());
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
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    std::ofstream image;
    image.open("image.ppm");

    // World
    auto world = hittable_list();
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    camera cam;

    // Render
    image << "P3\n"
          << image_width << " " << image_height << "\n255\n";

    for (int y = image_height - 1; y > -1; --y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            color pixel_color(0, 0, 0);

            for (int sample_count = 0; sample_count < samples_per_pixel; ++sample_count)
            {
                auto u = (x + random_double()) / (image_width - 1);
                auto v = (y + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(image, pixel_color, samples_per_pixel);
        }
        cout << (float(image_height - y) / float(image_height)) * 100.0 << "%\n"
             << std::flush;
    }
    image.close();
    cout << "Done in " << std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now() - programStartTime).count() << "ms" << std::endl;
}
