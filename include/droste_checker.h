#ifndef DROSTE_CHECKER_H
#define DROSTE_CHECKER_H

#include "image_generator.h"
#include <cmath>

namespace rt {

class DrosteCheckerPattern : public Pattern {
public:
    DrosteCheckerPattern(float spiralTightness = 0.1f, float repetitions = 4.0f);

    Color<Float> getColor(float x, float y, float width, float height) const override;
    std::string getName() const override { return "droste_checker"; }

private:
    float spiralTightness_;
    float repetitions_;

    bool isCheckerDroste(float x, float y, float centerX, float centerY) const;
};

} // namespace rt

#endif