// TupleTest.cpp
#include "Test.h"
#include "math/Tuple.h"

using namespace test;

TEST_CASE(DefaultConstructor) {
    math::Tuple<3, int> t;
    TestSuite::check(t[0] == 0, "Default constructor initializes element 0 to 0");
    TestSuite::check(t[1] == 0, "Default constructor initializes element 1 to 0");
    TestSuite::check(t[2] == 0, "Default constructor initializes element 2 to 0");
}

TEST_CASE(InitializerListConstructor) {
    math::Tuple<3, int> t{1, 2, 3};
    TestSuite::check(t[0] == 1, "Initializer list sets element 0 correctly");
    TestSuite::check(t[1] == 2, "Initializer list sets element 1 correctly");
    TestSuite::check(t[2] == 3, "Initializer list sets element 2 correctly");
}

TEST_CASE(PartialInitializerList) {
    math::Tuple<3, int> t{1, 2};
    TestSuite::check(t[0] == 1, "Partial initializer list sets element 0");
    TestSuite::check(t[1] == 2, "Partial initializer list sets element 1");
    TestSuite::check(t[2] == 0, "Remaining elements are zero-initialized");
}