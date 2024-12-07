#include "image_generator.h"
#include <stdexcept>
#include <cmath>

namespace rt {

ImageGenerator::ImageGenerator(size_t width, size_t height)
    : width_(width), height_(height), outputDir_("output"), filename_("image.ppm") {
    currentImage_ = std::make_unique<Image<Float>>(width, height);
}

void ImageGenerator::generateCheckerPattern(size_t squareSize, const Color<Float>& color1, const Color<Float>& color2) {
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            bool isColor1 = ((x / squareSize) + (y / squareSize)) % 2 == 0;
            currentImage_->setPixel(x, y, isColor1 ? color1 : color2);
        }
    }
}

void ImageGenerator::generateDrostePattern(float spiralTightness, float repetitions,
                                         const Color<Float>& color1, const Color<Float>& color2) {
    float centerX = width_ / 2.0f;
    float centerY = height_ / 2.0f;

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            float dx = x - centerX;
            float dy = y - centerY;
            float radius = std::sqrt(dx * dx + dy * dy);
            float angle = std::atan2(dy, dx);

            // Avoid log(0)
            radius = std::max(radius, 0.1f);

            float logR = std::log(radius);
            float spiralSpace = logR - spiralTightness * angle;

            float checker1 = std::fmod(spiralSpace * repetitions, 2.0f);
            float checker2 = std::fmod(angle * repetitions / M_PI, 2.0f);

            bool isColor1 = (checker1 < 1.0f) != (checker2 < 1.0f);
            currentImage_->setPixel(x, y, isColor1 ? color1 : color2);
        }
    }
}

void ImageGenerator::saveImage() {
    ensureOutputDirectory();
    std::filesystem::path fullPath = outputDir_ / filename_;
    currentImage_->savePPM(fullPath.string());
}

void ImageGenerator::ensureOutputDirectory() const {
    std::filesystem::create_directories(outputDir_);
}

} // namespace rt