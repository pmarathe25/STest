#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Stealth::Test {
    using TestFunc = std::function<void(void)>;

    struct TestInfo {
        TestInfo(std::string test, std::string subtest) : test{std::move(test)}, subtest{std::move(subtest)} { }
        const std::string test;
        const std::string subtest;
    };

    struct Subtest {
        Subtest(TestFunc func, std::string name) : func{std::move(func)}, name{std::move(name)} { }
        void operator()() const { func(); }
        const TestFunc func;
        const std::string name;
    };

    // A single test has many subtests.
    using Test = std::vector<Subtest>;
    // Container for all tests.
    static std::map<const std::string, Test> tests{};

    // Test Case Helpers
    #define SUBTEST_NAME(TEST, SUBTEST) TEST##_##SUBTEST

    // Test Cases
    #define STEST(TEST, SUBTEST) \
    void SUBTEST_NAME(TEST, SUBTEST)(const Stealth::Test::TestInfo& info); \
    namespace Stealth::Test { static const bool TEST##_##SUBTEST##_##discard = Stealth::Test::addTest(std::bind(SUBTEST_NAME(TEST, SUBTEST), TestInfo{#TEST, #SUBTEST}), #TEST, #SUBTEST); } \
    void SUBTEST_NAME(TEST, SUBTEST)(const Stealth::Test::TestInfo& info)
} /* Stealth::Test */
