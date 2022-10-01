#include <iostream>
#include <fstream>

int main()
{
    const int width = 256;
    const int height = 256;

    std::ofstream image;
    image.open("image.ppm");

    // Render
    image << "P3\n"
          << width << " " << height << "\n255\n";

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            double r = double(x) / (width - 1);
            double g = double(y) / (height - 1);
            double b = 0.90;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            image << ir << " " << ig << " " << ib << "\n";
        }
    }
    image.close();
}
