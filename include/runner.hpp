#pragma once
#include "./core.hpp"
#include <string>

namespace Stealth::Test {
    inline bool addTest(TestFunc func, const std::string& testName, std::string testCaseName) {
        tests[testName].emplace_back(std::move(func), std::move(testCaseName));
        return false;
    }

    // Default behavior is to print test name and then run it.
    constexpr auto displayTestNameDefault = [] (const std::string& testName) {
        std::cout << "Running Test: " << testName << std::endl;
    };

    constexpr auto runTestCaseDefault = [] (const std::string& testName, const Subtest& testCase) {
        std::cout << "\tRunning Subtest: " << testCase.name << std::endl;
        testCase();
    };

    inline void runTests(const std::function<void(const std::string&, const Subtest&)>& runTestCase = runTestCaseDefault, const std::function<void(const std::string&)>& displayTestName = displayTestNameDefault) {
        for (const auto& [test, subtests] : tests) {
            displayTestName(test);
            for (const auto& subtest : subtests)
                runTestCase(test, subtest);
        }
    }

} /* Stealth::Test */
