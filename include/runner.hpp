#pragma once
#include "./core.hpp"
#include <string>

namespace Stealth::Test {
    using DisplayTest = std::function<void(const std::string&)>;
    using RunTest = std::function<void(const Test&)>;

    // Default behavior is to print test name and then run it.
    const DisplayTest displayDefault = [] (const std::string& name) {
        std::cout << "Running Test: " << name << std::endl;
    };

    const RunTest runDefault = [] (const Test& test) {
        test();
    };

    inline void runTests(const RunTest& run = runDefault, const DisplayTest& display = displayDefault) {
        for (const auto& [name, test] : tests) {
            display(name);
            run(test);
        }
    }

    #define RUN_TESTS int main(int argc, char const *argv[]) { Stealth::Test::runTests(); }
} /* Stealth::Test */
