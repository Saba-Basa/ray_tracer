#include "Test.h"
#include "util/Color.h"
#include <limits>

using namespace test;

TEST_CASE(Color_DefaultConstructor) {
    rt::Color<float> c;
    TestSuite::check(c.r() == 0.0f, "Default constructor initializes r to 0");
    TestSuite::check(c.g() == 0.0f, "Default constructor initializes g to 0");
    TestSuite::check(c.b() == 0.0f, "Default constructor initializes b to 0");
}

TEST_CASE(Color_ValueConstructor) {
    rt::Color<float> c(1.0f, 0.5f, 0.0f);
    TestSuite::check(c.r() == 1.0f, "Constructor sets r correctly");
    TestSuite::check(c.g() == 0.5f, "Constructor sets g correctly");
    TestSuite::check(c.b() == 0.0f, "Constructor sets b correctly");
}

TEST_CASE(Color_ByteConversion_BasicValues) {
    rt::Color<float> c(1.0f, 0.5f, 0.0f);
    TestSuite::check(c.toByte(c.r()) == 255, "Full intensity converts to 255");
    TestSuite::check(c.toByte(c.g()) == 127, "Half intensity converts to ~127");
    TestSuite::check(c.toByte(c.b()) == 0, "Zero intensity converts to 0");
}

TEST_CASE(Color_ByteConversion_EdgeCases) {
    rt::Color<float> c;

    // Test negative values
    TestSuite::check(c.toByte(-1.0f) == 0, "Negative values clamp to 0");
    TestSuite::check(c.toByte(-0.1f) == 0, "Small negative values clamp to 0");

    // Test values above 1.0
    TestSuite::check(c.toByte(1.5f) == 255, "Values above 1.0 clamp to 255");
    TestSuite::check(c.toByte(2.0f) == 255, "Large values clamp to 255");

    // Test exact boundaries
    TestSuite::check(c.toByte(0.0f) == 0, "Zero converts exactly to 0");
    TestSuite::check(c.toByte(1.0f) == 255, "One converts exactly to 255");
}

TEST_CASE(Color_ByteConversion_Precision) {
    rt::Color<float> c;

    // Test small increments
    TestSuite::check(c.toByte(0.2f) == 51, "20% intensity converts correctly");
    TestSuite::check(c.toByte(0.4f) == 102, "40% intensity converts correctly");
    TestSuite::check(c.toByte(0.6f) == 153, "60% intensity converts correctly");
    TestSuite::check(c.toByte(0.8f) == 204, "80% intensity converts correctly");

    // Test precision at boundaries
    TestSuite::check(c.toByte(0.003921569f) == 1, "Smallest non-zero byte value");
    TestSuite::check(c.toByte(0.996078431f) == 254, "Largest non-max byte value");
}

TEST_CASE(Color_ByteConversion_Types) {
    // Test with different numeric types
    rt::Color<double> cd(0.5, 0.5, 0.5);
    TestSuite::check(cd.toByte(cd.r()) == 127, "Double type converts correctly");

    rt::Color<long double> cld(0.5L, 0.5L, 0.5L);
    TestSuite::check(cld.toByte(cld.r()) == 127, "Long double type converts correctly");
}

TEST_CASE(Color_AccessElements) {
    rt::Color<float> c(0.1f, 0.2f, 0.3f);

    // Test mutability
    c.r() = 0.4f;
    c.g() = 0.5f;
    c.b() = 0.6f;
    TestSuite::check(c.r() == 0.4f, "Modified r value");
    TestSuite::check(c.g() == 0.5f, "Modified g value");
    TestSuite::check(c.b() == 0.6f, "Modified b value");

    // Test const access
    const rt::Color<float> cc(0.7f, 0.8f, 0.9f);
    TestSuite::check(cc.r() == 0.7f, "Const access r");
    TestSuite::check(cc.g() == 0.8f, "Const access g");
    TestSuite::check(cc.b() == 0.9f, "Const access b");
}

TEST_CASE(Color_VectorOperations) {
    // Test vector operations inherited from Vec3
    rt::Color<float> c1(0.1f, 0.2f, 0.3f);
    rt::Color<float> c2(0.2f, 0.3f, 0.4f);

    // Addition
    rt::Color<float> sum = c1 + c2;
//    TestSuite::check(sum.r() == 0.3f, "Vector addition r");
//    TestSuite::check(sum.g() == 0.5f, "Vector addition g");
//    TestSuite::check(sum.b() == 0.7f, "Vector addition b");
//    std::cout << "c1.b(): " << c1.b() << ", c2.b(): " << c2.b() << ", sum.b(): " << sum.b() << std::endl;
    //inaccurate floating point comparison
    constexpr float epsilon = 1e-6f;
    TestSuite::check(std::abs(sum.r() - 0.3f) < epsilon, "Vector addition r");
    TestSuite::check(std::abs(sum.g() - 0.5f) < epsilon, "Vector addition g");
    TestSuite::check(std::abs(sum.b() - 0.7f) < epsilon, "Vector addition b");



    // Multiplication by scalar
    rt::Color<float> scaled = c1 * 2.0f;
    TestSuite::check(scaled.r() == 0.2f, "Scalar multiplication r");
    TestSuite::check(scaled.g() == 0.4f, "Scalar multiplication g");
    TestSuite::check(scaled.b() == 0.6f, "Scalar multiplication b");
}