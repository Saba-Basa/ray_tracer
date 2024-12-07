#include "pattern_generator.h"
#include <cmath>

namespace rt {

// Checker Pattern Implementation
CheckerPattern::CheckerPattern(size_t squareSize, const Color<Float>& color1, const Color<Float>& color2)
    : squareSize_(squareSize), color1_(color1), color2_(color2) {}

void CheckerPattern::generate(Image<Float>& image) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            bool isColor1 = ((x / squareSize_) + (y / squareSize_)) % 2 == 0;
            image.setPixel(x, y, isColor1 ? color1_ : color2_);
        }
    }
}

// Droste Checker Pattern Implementation
DrosteCheckerPattern::DrosteCheckerPattern(float spiralTightness, float repetitions,
                                         const Color<Float>& color1, const Color<Float>& color2)
    : spiralTightness_(spiralTightness), repetitions_(repetitions),
      color1_(color1), color2_(color2) {}

void DrosteCheckerPattern::generate(Image<Float>& image) {
    size_t width = image.getWidth();
    size_t height = image.getHeight();
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            float dx = x - centerX;
            float dy = y - centerY;
            float radius = std::sqrt(dx * dx + dy * dy);
            float angle = std::atan2(dy, dx);

            // Avoid log(0)
            radius = std::max(radius, 0.1f);

            float logR = std::log(radius);
            float spiralSpace = logR - spiralTightness_ * angle;

            float checker1 = std::fmod(spiralSpace * repetitions_, 2.0f);
            float checker2 = std::fmod(angle * repetitions_ / M_PI, 2.0f);

            bool isColor1 = (checker1 < 1.0f) != (checker2 < 1.0f);
            image.setPixel(x, y, isColor1 ? color1_ : color2_);
        }
    }
}

} // namespace rt