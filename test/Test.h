// Test.h
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <iomanip>

namespace test {

class TestSuite {
private:
    static TestSuite& instance() {
        static TestSuite inst;
        return inst;
    }

    int totalTests = 0;
    int passedTests = 0;
    int currentTestAssertions = 0;
    int currentTestPassed = 0;
    std::vector<std::pair<std::string, std::function<void()>>> tests;

public:
    static void addTest(const std::string& name, std::function<void()> test) {
        instance().tests.push_back({name, test});
    }

    static void check(bool condition, const std::string& message = "") {
        instance().currentTestAssertions++;
        if (condition) {
            instance().currentTestPassed++;
            std::cout << "    ✓ " << message << "\n";
        } else {
            std::cerr << "    ✗ " << message << "\n";
        }
    }

    static void runAll() {
        std::cout << "\n=== Running Tests ===\n";

        for (const auto& [name, test] : instance().tests) {
            instance().currentTestAssertions = 0;
            instance().currentTestPassed = 0;

            std::cout << "\n➤ Test Case: " << name << "\n";
            test();

            // Update total counts
            instance().totalTests += instance().currentTestAssertions;
            instance().passedTests += instance().currentTestPassed;

            // Print test case summary
            std::cout << "   Result: " << instance().currentTestPassed
                      << "/" << instance().currentTestAssertions
                      << " assertions passed\n";
        }

        instance().summary();
    }

    static void summary() {
        std::cout << "\n=== Test Summary ===\n";
        std::cout << "Total Tests: " << instance().totalTests << "\n";
        std::cout << "Passed: " << instance().passedTests << "\n";
        std::cout << "Failed: " << (instance().totalTests - instance().passedTests) << "\n";

        float percentage = (instance().totalTests > 0)
            ? (100.0f * instance().passedTests / instance().totalTests)
            : 0.0f;

        std::cout << "Success Rate: " << std::fixed << std::setprecision(1)
                  << percentage << "%\n";

        if (instance().passedTests == instance().totalTests) {
            std::cout << "\n✨ All tests passed! ✨\n";
        } else {
            std::cout << "\n❌ Some tests failed.\n";
        }
    }
};

#define TEST_CASE(name) \
    void name##_impl(); \
    namespace { \
        struct name##_register { \
            name##_register() { \
                test::TestSuite::addTest(#name, name##_impl); \
            } \
        } name##_register_instance; \
    } \
    void name##_impl()

} // namespace test

#endif // TEST_H