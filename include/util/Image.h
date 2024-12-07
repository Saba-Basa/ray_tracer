#ifndef UTIL_IMAGE_H
#define UTIL_IMAGE_H

#include "rt.h"
#include "util/Color.h"
#include <stdexcept>
#include <fstream>


//Image output and manipulation
/*
- Stores the final rendered pixels
- Handles image output (e.g., PPM format)
- Manages pixel access and modification
*/

namespace rt {

template<typename T>
class Image {
public:

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Constructors
    Image(size_t w, size_t h) : width(w), height(h), pixels(w * h) {
            if (w == 0 || h == 0) {
                throw std::invalid_argument("Image dimensions must be greater than zero");
            }
    }

    // Rule of five
    // copy/move constructors and assignment operators
    Image(const Image& other) = default;
    Image(Image&& other) noexcept = default;
    Image& operator=(const Image& other) = default;
    Image& operator=(Image&& other) noexcept = default;

    // Accessors
    size_t getWidth() const noexcept { return width; }
    size_t getHeight() const noexcept { return height; }
    size_t size() const noexcept { return pixels.size(); }


    void setPixel(size_t x, size_t y, const Color<T>& c) {
            validateCoordinates(x, y);
            pixels[y * width + x] = c;
        }

    Color<T>& getPixel(size_t x, size_t y) {
            validateCoordinates(x, y);
            return pixels[y * width + x];
        }

    const Color<T>& getPixel(size_t x, size_t y) const {
        validateCoordinates(x, y);
        return pixels[y * width + x];
    }

    void savePPM(const std::string& filename) const {
            std::ofstream file(filename, std::ios::binary);
            if (!file) {
                throw std::runtime_error("Failed to open file: " + filename);
            }

            // Write PPM header
            file << "P6\n" << width << " " << height << "\n255\n";

            // Write pixel data
            for (const auto& pixel : pixels) {
                uint8_t r = pixel.toByte(pixel.r());
                uint8_t g = pixel.toByte(pixel.g());
                uint8_t b = pixel.toByte(pixel.b());
                file.write(reinterpret_cast<const char*>(&r), 1);
                file.write(reinterpret_cast<const char*>(&g), 1);
                file.write(reinterpret_cast<const char*>(&b), 1);
            }
        }

    typename std::vector<Color<T>>::iterator begin() noexcept { return pixels.begin(); }
    typename std::vector<Color<T>>::iterator end() noexcept { return pixels.end(); }
    typename std::vector<Color<T>>::const_iterator begin() const noexcept { return pixels.begin(); }
    typename std::vector<Color<T>>::const_iterator end() const noexcept { return pixels.end(); }


protected:
    void validateCoordinates(size_t x, size_t y) const {
        if (x >= width || y >= height) {
            throw std::out_of_range("Pixel coordinates out of bounds");
        }
    }

private:
    size_t width, height;
    std::vector<Color<T>> pixels;
};

} // namespace rt

#endif