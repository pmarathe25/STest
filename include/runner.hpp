#pragma once
#include "./core.hpp"
#include <string>

namespace Stealth::Test {
    using DisplayTest = std::function<void(const std::string&)>;
    using RunSubtest = std::function<void(const Subtest&)>;

    // Default behavior is to print test name and then run it.
    const DisplayTest displayTestDefault = [] (const std::string& testName) {
        std::cout << "Running Test: " << testName << std::endl;
    };

    const RunSubtest runSubtestDefault = [] (const Subtest& subtest) {
        std::cout << "\tRunning Subtest: " << subtest.name << std::endl;
        subtest();
    };

    inline void runTests(const RunSubtest& runSubtest = runSubtestDefault, const DisplayTest& displayTest = displayTestDefault) {
        for (const auto& [test, subtests] : tests) {
            displayTest(test);
            for (const auto& subtest : subtests) {
                runSubtest(subtest);
            }
        }
    }

    #define RUN_TESTS int main(int argc, char const *argv[]) { Stealth::Test::runTests(); }
} /* Stealth::Test */
