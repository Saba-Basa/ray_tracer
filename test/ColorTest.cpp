#include "Test.h"
#include "util/Color.h"

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

TEST_CASE(Color_ByteConversion) {
    rt::Color<float> c(1.0f, 0.5f, 0.0f);
    TestSuite::check(c.toByte(c.r()) == 255, "Full intensity converts to 255");
    TestSuite::check(c.toByte(c.g()) == 127, "Half intensity converts to ~127");
    TestSuite::check(c.toByte(c.b()) == 0, "Zero intensity converts to 0");
}

TEST_CASE(Color_AccessElements) {
    rt::Color<float> c(0.1f, 0.2f, 0.3f);

    c.r() = 0.4f;
    c.g() = 0.5f;
    c.b() = 0.6f;
    TestSuite::check(c.r() == 0.4f, "Modified r value");
    TestSuite::check(c.g() == 0.5f, "Modified g value");
    TestSuite::check(c.b() == 0.6f, "Modified b value");

    const rt::Color<float> cc(0.7f, 0.8f, 0.9f);
    TestSuite::check(cc.r() == 0.7f, "Const access r");
    TestSuite::check(cc.g() == 0.8f, "Const access g");
    TestSuite::check(cc.b() == 0.9f, "Const access b");
}