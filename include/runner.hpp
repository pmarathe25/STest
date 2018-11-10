#pragma once
#include "core.hpp"
#include <unordered_set>
#include <chrono>
#include <string>

namespace Stealth::Test {
    inline std::string runningTestsMessage(int numTests) {
        return std::to_string(numTests) + " test" + (numTests == 1 ? "" : "s");
    }

    inline void runTests(int argc, char const *argv[], std::string filename) {
        std::unordered_set<std::string> failed{};
        int numPassed = 0;
        float totalMs = 0.f;

        std::cout << "[==========] Running " << runningTestsMessage(tests.size()) << " from " << filename << '\n';
        for (const auto& [name, test] : tests) {
            std::cout << "\n[RUNNING   ] " << name << "\n";
            bool passed = true;
            float ms = 0.f;
            // Run and time the test.
            try {
                auto startTime = std::chrono::steady_clock::now();
                test(passed);
                auto endTime = std::chrono::steady_clock::now();
                ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1.0e6f;
                totalMs += ms;
            } catch (const std::exception& e) {
                std::cout << "[ EXCEPTION] " << name << "\n\t" << e.what() << '\n';
                passed = false;
            }
            // Show test results.
            if (passed) {
                ++numPassed;
                std::cout << "[        OK] " << name << " (" << ms << " ms)\n";
            } else {
                std::cout << "[    FAILED] " << name << " (" << ms << " ms)\n";
                failed.insert(name);
            }
        }
        // Print overall stats.
        std::cout << "\n[==========] Ran " << runningTestsMessage(tests.size()) << " (" << totalMs << " ms)\n";
        std::cout << "[  PASSED  ] " << runningTestsMessage(numPassed) << '\n';
        std::cout << "[  FAILED  ] " << runningTestsMessage(failed.size()) << '\n';
        for (const std::string& fail : failed) {
            std::cout << "[  FAILED  ]\t" << fail << '\n';
        }
        std::cout << std::flush;
    }

    #define RUN_STESTS(argc, argv) Stealth::Test::runTests(argc, argv, __FILE__)
} /* Stealth::Test */
