#include "util/Color.h"
#include "util/Image.h"
#include <iostream>
#include <fstream>

// Implement savePPM method
template<typename T>
void rt::Image<T>::savePPM(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (const auto& pixel : pixels) {
        uint8_t r = pixel.toByte(pixel.r());
        uint8_t g = pixel.toByte(pixel.g());
        uint8_t b = pixel.toByte(pixel.b());
        ofs.write(reinterpret_cast<char*>(&r), 1);
        ofs.write(reinterpret_cast<char*>(&g), 1);
        ofs.write(reinterpret_cast<char*>(&b), 1);
    }
}

int main() {
    rt::Image<rt::Float> img(800, 600);

    for (size_t y = 0; y < 600; ++y) {
        for (size_t x = 0; x < 800; ++x) {
            bool isWhite = ((x / 50) + (y / 50)) % 2 == 0;
            rt::Color<rt::Float> color = isWhite ?
                rt::Color<rt::Float>(1.0f, 1.0f, 1.0f) :
                rt::Color<rt::Float>(0.2f, 0.3f, 0.8f);
            img.setPixel(x, y, color);
        }
    }

    img.savePPM("checker.ppm");
    return 0;
}