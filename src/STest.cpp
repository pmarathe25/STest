#include "STest/include/STest.hpp"

#include <unordered_set>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

namespace Stealth::Test {
    // Keep track of all tests.
    // TODO: Make this a vector of pairs to allow duplicate test names (in different namespaces for example).
    static std::vector<std::pair<const std::string, const TestFunc>> G_TESTS{};

    // Must have a return type so that we can invoke this in the global scope.
    // The side-effect of this function is to register the test.
    bool addTest(TestFunc func, const std::string& name) {
        G_TESTS.emplace_back(name, std::move(func));
        return true;
    }

    namespace {
        std::string pluralize(std::string item, int num) {
            return std::to_string(num) + " " + item + (num == 1 ? "" : "s");
        }
    } // anonymous

    Status runTests(int argc, const char* argv[], const std::string& filename) {
        std::unordered_set<std::string> failed{};
        int numPassed = 0;
        float totalMs = 0.f;

        std::cout << "[==========] Running " << pluralize("test", G_TESTS.size()) << " from " << filename << '\n';
        for (const auto& [name, test] : G_TESTS) {
            std::cout << "\n[RUNNING   ] " << name << "\n";
            bool passed = true;
            float ms = 0.f;
            // Run and time the test.
            try {
                auto startTime = std::chrono::steady_clock::now();
                test();
                auto endTime = std::chrono::steady_clock::now();
                ms = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1.0e6f;
                totalMs += ms;
            } catch (const std::exception& e) {
                std::cout << "\033[1;31m[ EXCEPTION] " << name << "\n\t" << e.what() << "\033[0m\n";
                passed = false;
            } catch (const TestFailedException&) {
                passed = false;
            }
            // Show test results.
            if (passed) {
                ++numPassed;
                std::cout << "\033[1;92m[        OK] " << name << " (" << ms << " ms)\033[0m\n";
            } else {
                std::cerr << "\033[1;31m[    FAILED] " << name << " (" << ms << " ms)\033[0m\n";
                failed.insert(name);
            }
        }
        // Print overall stats.
        std::cout << "\n[==========] Ran " << pluralize("test", G_TESTS.size()) << " (" << totalMs << " ms)\n";
        if (numPassed) {
            std::cout << "\033[1;92m[  PASSED  ] " << pluralize("test", numPassed) << "\033[0m\n";
        }
        if (!failed.empty()) {
            std::cout << "\033[1;31m[  FAILED  ] " << pluralize("test", failed.size()) << "\033[0m\n";
        }
        for (const std::string& fail : failed) {
            std::cout << "\033[1;31m[  FAILED  ]\t" << fail << "\033[0m\n";
        }
        std::cout << std::flush;
        std::cerr << std::flush;
        return (numPassed == G_TESTS.size()) ? Status::OK : Status::FAIL;
    }

} // Stealth::Test
