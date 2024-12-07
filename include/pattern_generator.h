#ifndef PATTERN_GENERATORS_H
#define PATTERN_GENERATORS_H

#include "util/Image.h"
#include "util/Color.h"
#include <memory>

namespace rt {

class PatternGenerator {
public:
    virtual ~PatternGenerator() = default;
    virtual void generate(Image<Float>& image) = 0;
};

class CheckerPattern : public PatternGenerator {
public:
    CheckerPattern(size_t squareSize, const Color<Float>& color1, const Color<Float>& color2);
    void generate(Image<Float>& image) override;

private:
    size_t squareSize_;
    Color<Float> color1_;
    Color<Float> color2_;
};

class DrosteCheckerPattern : public PatternGenerator {
public:
    DrosteCheckerPattern(float spiralTightness, float repetitions,
                        const Color<Float>& color1, const Color<Float>& color2);
    void generate(Image<Float>& image) override;

private:
    float spiralTightness_;
    float repetitions_;
    Color<Float> color1_;
    Color<Float> color2_;
};

} // namespace rt

#endif