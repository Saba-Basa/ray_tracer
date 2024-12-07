#include "util/Color.h"
#include "util/Image.h"
#include <iostream>
#include <fstream>
#include <cmath>

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

// Function to determine if a point is in a checker based on logarithmic spiral coordinates
bool isCheckerDroste(float x, float y, float centerX, float centerY) {
    // Convert to polar coordinates relative to center
    float dx = x - centerX;
    float dy = y - centerY;
    float radius = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx);

    // Logarithmic spiral parameters
    float a = 0.1;  // Controls how tight the spiral is
    float b = 4.0;  // Controls number of checker repetitions

    // Convert to logarithmic spiral space
    float logR = std::log(radius);
    float spiralSpace = logR - a * angle;

    // Create checker pattern in spiral space
    float checker1 = std::fmod(spiralSpace * b, 2.0f);
    float checker2 = std::fmod(angle * b / M_PI, 2.0f);

    return (checker1 < 1.0f) != (checker2 < 1.0f);
}

int main() {
    const size_t width = 800;
    const size_t height = 800;
    rt::Image<rt::Float> img(width, height);

    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            bool isWhite = isCheckerDroste(x, y, centerX, centerY);

            // Create a gradient based on distance from center for more depth
            float dx = (x - centerX) / centerX;
            float dy = (y - centerY) / centerY;
            float distFactor = std::sqrt(dx * dx + dy * dy);
            distFactor = std::max(0.0f, 1.0f - distFactor * 0.5f);

            rt::Color<rt::Float> color;
            if (isWhite) {
                color = rt::Color<rt::Float>(
                    1.0f * distFactor,
                    1.0f * distFactor,
                    1.0f * distFactor
                );
            } else {
                color = rt::Color<rt::Float>(
                    0.0f * distFactor,
                    0.0f * distFactor,
                    0.0f * distFactor
                );
            }

            img.setPixel(x, y, color);
        }
    }


    img.savePPM("droste_checker.ppm");
    std::cout << "Created Droste effect checker pattern in 'droste_checker.ppm'" << std::endl;
    return 0;
}