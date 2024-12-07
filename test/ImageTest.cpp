#include "Test.h"
#include "util/Image.h"
#include <stdexcept>
#include <sstream>

using namespace test;

TEST_CASE(Image_Construction) {
    rt::Image<float> img(2, 2);
    rt::Color<float> black;

    TestSuite::check(img.getPixel(0, 0).r() == 0.0f, "Default pixel is black (r)");
    TestSuite::check(img.getPixel(0, 0).g() == 0.0f, "Default pixel is black (g)");
    TestSuite::check(img.getPixel(0, 0).b() == 0.0f, "Default pixel is black (b)");
}

TEST_CASE(Image_BasicConstruction) {
    rt::Image<float> img(2, 2);
    TestSuite::check(img.getWidth() == 2, "Width correctly set");
    TestSuite::check(img.getHeight() == 2, "Height correctly set");
    TestSuite::check(img.size() == 4, "Size correctly calculated");
}

TEST_CASE(Image_InvalidConstruction) {
    bool caught = false;
    try {
        rt::Image<float> img(0, 5);
    } catch (const std::invalid_argument& e) {
        caught = true;
        TestSuite::check(std::string(e.what()).find("zero") != std::string::npos,
            "Error message mentions zero");
    }
    TestSuite::check(caught, "Exception thrown for zero width");

    caught = false;
    try {
        rt::Image<float> img(5, 0);
    } catch (const std::invalid_argument& e) {
        caught = true;
    }
    TestSuite::check(caught, "Exception thrown for zero height");
}

TEST_CASE(Image_SetAndGetPixel) {
    rt::Image<float> img(2, 2);
    rt::Color<float> red(1.0f, 0.0f, 0.0f);

    img.setPixel(0, 1, red);
    TestSuite::check(img.getPixel(0, 1).r() == 1.0f, "Set/get red component");
    TestSuite::check(img.getPixel(0, 1).g() == 0.0f, "Set/get green component");
    TestSuite::check(img.getPixel(0, 1).b() == 0.0f, "Set/get blue component");
}

TEST_CASE(Image_Iterator) {
    rt::Image<float> img(2, 2);
    rt::Color<float> red(1.0f, 0.0f, 0.0f);

    // Test iterator writing
    for (auto& pixel : img) {
        pixel = red;
    }
    TestSuite::check(img.getPixel(0, 0).r() == 1.0f, "Iterator write successful");
    TestSuite::check(img.getPixel(1, 1).r() == 1.0f, "Iterator write successful");

    // Test const iterator reading
    const rt::Image<float>& const_img = img;
    size_t count = 0;
    for (const auto& pixel : const_img) {
        TestSuite::check(pixel.r() == 1.0f, "Const iterator read successful");
        count++;
    }
    TestSuite::check(count == 4, "Iterator covers all pixels");
}

TEST_CASE(Image_PPMOutput) {
    rt::Image<float> img(2, 2);
    rt::Color<float> red(1.0f, 0.0f, 0.0f);
    img.setPixel(0, 0, red);

    // Test file open failure
    bool caught = false;
    try {
        img.savePPM("/invalid/path/image.ppm");
    } catch (const std::runtime_error& e) {
        caught = true;
        TestSuite::check(std::string(e.what()).find("Failed to open") != std::string::npos,
            "Error message mentions file open failure");
    }
    TestSuite::check(caught, "Exception thrown for invalid file path");
}