#ifndef IMAGE_GENERATOR_H
#define IMAGE_GENERATOR_H

#include "util/Image.h"
#include "util/Color.h"
#include <string>
#include <filesystem>
#include <memory>

namespace rt {

class ImageGenerator {
public:
    ImageGenerator(size_t width, size_t height);

    // Basic setters
    void setOutputDirectory(const std::filesystem::path& dir) { outputDir_ = dir; }
    void setFilename(const std::string& name) { filename_ = name; }

    // Pattern generation methods
    void generateCheckerPattern(size_t squareSize, const Color<Float>& color1, const Color<Float>& color2);
    void generateDrostePattern(float spiralTightness, float repetitions, const Color<Float>& color1, const Color<Float>& color2);

    // Save current image
    void saveImage();

private:
    size_t width_;
    size_t height_;
    std::filesystem::path outputDir_;
    std::string filename_;
    std::unique_ptr<Image<Float>> currentImage_;

    void ensureOutputDirectory() const;
};

} // namespace rt

#endif