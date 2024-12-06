#include "Test.h"
#include "util/Image.h"

using namespace test;

TEST_CASE(Image_Construction) {
    rt::Image<float> img(2, 2);
    rt::Color<float> black;

    TestSuite::check(img.getPixel(0, 0).r() == 0.0f, "Default pixel is black (r)");
    TestSuite::check(img.getPixel(0, 0).g() == 0.0f, "Default pixel is black (g)");
    TestSuite::check(img.getPixel(0, 0).b() == 0.0f, "Default pixel is black (b)");
}

TEST_CASE(Image_SetAndGetPixel) {
    rt::Image<float> img(2, 2);
    rt::Color<float> red(1.0f, 0.0f, 0.0f);

    img.setPixel(0, 1, red);
    TestSuite::check(img.getPixel(0, 1).r() == 1.0f, "Set/get red component");
    TestSuite::check(img.getPixel(0, 1).g() == 0.0f, "Set/get green component");
    TestSuite::check(img.getPixel(0, 1).b() == 0.0f, "Set/get blue component");
}

TEST_CASE(Image_BoundsChecking) {
    rt::Image<float> img(2, 2);
    rt::Color<float> red(1.0f, 0.0f, 0.0f);

    img.setPixel(2, 2, red);  // Out of bounds
    TestSuite::check(img.getPixel(0, 0).r() == 0.0f, "Out of bounds write is ignored");
}