#include <iostream>
#include <fstream>

#include <chrono>

using std::cout;
using std::chrono::steady_clock;

int main()
{
    auto programStartTime = steady_clock::now();
    const int width = 256;
    const int height = 256;

    std::ofstream image;
    image.open("image.ppm");

    // Render
    image << "P3\n"
          << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double r = double(x) / (width - 1);
            double g = double(y) / (height - 1);
            double b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            image << ir << " " << ig << " " << ib << "\n";
        }
        cout << (float(y) / float(height - 1)) * 100.0 << "%\n"
             << std::flush;
    }
    image.close();
    cout << "Done in " << std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now() - programStartTime).count() << "ms" << std::endl;
}
