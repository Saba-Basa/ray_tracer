#include "Test.h"
#include "math/Point.h"

using namespace test;

TEST_CASE(Point_DefaultConstructor) {
    math::Point<int> p;
    TestSuite::check(p.x() == 0, "Default constructor initializes x to 0");
    TestSuite::check(p.y() == 0, "Default constructor initializes y to 0");
    TestSuite::check(p.z() == 0, "Default constructor initializes z to 0");
}

TEST_CASE(Point_AccessElement){
    math::Point<int> p{1, 2, 3};
    p.x() = 4;
    p.y() = 5;
    p.z() = 6;
    TestSuite::check(p.x() == 4, "Modified x value");
    TestSuite::check(p.y() == 5, "Modified y value");
    TestSuite::check(p.z() == 6, "Modified z value");
}

TEST_CASE(Point_ConstAccessElement){
    const math::Point<int> p{7, 8, 9};
    TestSuite::check(p.x() == 7, "Const access x");
    TestSuite::check(p.y() == 8, "Const access y");
    TestSuite::check(p.z() == 9, "Const access z");
}