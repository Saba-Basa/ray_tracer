// HelloTest.cpp
#include "Test.h"

using namespace test;

TEST_CASE(HelloWorldTest) {
    TestSuite::check(true, "Hello World test passes");
}