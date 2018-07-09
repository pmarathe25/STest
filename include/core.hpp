#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Stealth::Test {
    using TestFunc = std::function<void(void)>;

    struct Subtest {
        Subtest(TestFunc func, std::string name) : func{std::move(func)}, name{std::move(name)} { }
        void operator()() const { func(); }
        const TestFunc func;
        const std::string name;
    };

    // A single test has many subtests.
    using Test = std::vector<Subtest>;
    // Keep track of all tests.
    static std::map<const std::string, Test> tests{};

    inline bool addTest(TestFunc func, const std::string& testName, std::string testCaseName) {
        tests[testName].emplace_back(std::move(func), std::move(testCaseName));
        return false;
    }

    #define SUBTEST_NAME(TEST, SUBTEST) TEST##_##SUBTEST
    // Tests
    #define STEST(TEST, SUBTEST) \
        void SUBTEST_NAME(TEST, SUBTEST)(); \
        namespace Stealth::Test { \
            [[maybe_unused]] static const bool _ST_Func_Result_##TEST##_##SUBTEST##_##discard = Stealth::Test::addTest(SUBTEST_NAME(TEST, SUBTEST), #TEST, #SUBTEST); \
        } \
        void SUBTEST_NAME(TEST, SUBTEST)()
} /* Stealth::Test */
