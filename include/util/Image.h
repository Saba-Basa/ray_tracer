#ifndef UTIL_IMAGE_H
#define UTIL_IMAGE_H

#include "rt.h"
#include "util/Color.h"

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
    Image(size_t w, size_t h) : width(w), height(h), pixels(w * h) {}

    void setPixel(size_t x, size_t y, const Color<T>& c) {
        if (x < width && y < height)
            pixels[y * width + x] = c;
    }

    Color<T>& getPixel(size_t x, size_t y) {
        return pixels[y * width + x];
    }

    const Color<T>& getPixel(size_t x, size_t y) const {
        return pixels[y * width + x];
    }

    void savePPM(const std::string& filename) const;

private:
    size_t width, height;
    std::vector<Color<T>> pixels;
};

} // namespace rt

#endif