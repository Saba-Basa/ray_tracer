#include "Test.h"
#include "math/Vec3.h"

using namespace test;

TEST_CASE(Vec3_DefaultConstructor) {
    math::Vec3<int> v;
    TestSuite::check(v.x() == 0, "Default constructor initializes x to 0");
    TestSuite::check(v.y() == 0, "Default constructor initializes y to 0");
    TestSuite::check(v.z() == 0, "Default constructor initializes z to 0");
}

TEST_CASE(Vec3_InitializerListConstructor) {
    math::Vec3<int> v{1, 2, 3};
    TestSuite::check(v.x() == 1, "Initializer list sets x correctly");
    TestSuite::check(v.y() == 2, "Initializer list sets y correctly");
    TestSuite::check(v.z() == 3, "Initializer list sets z correctly");
}


TEST_CASE(Vec3_AccessElements) {
    math::Vec3<int> v{1, 2, 3};

    // Test non-const access (can modify)
    v.x() = 4;
    v.y() = 5;
    v.z() = 6;
    TestSuite::check(v.x() == 4, "Modified x value");
    TestSuite::check(v.y() == 5, "Modified y value");
    TestSuite::check(v.z() == 6, "Modified z value");

    // Test const access
    const math::Vec3<int> cv{7, 8, 9};
    TestSuite::check(cv.x() == 7, "Const access x");
    TestSuite::check(cv.y() == 8, "Const access y");
    TestSuite::check(cv.z() == 9, "Const access z");
}