#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Stealth::Test {
    void log(const std::string& message) {
        std::cerr << message << std::endl;
    }

    using TestFunc = std::function<void(void)>;

    struct Test {
        Test(TestFunc func = {}) : func{std::move(func)} { }
        void operator()() const { func(); }
        const TestFunc func;
    };

    // Keep track of all tests.
    std::map<const std::string, Test> tests{};

    // Must have a return type so that we can invoke this in the global scope.
    // The side-effect of this function is to register the test.
    inline bool addTest(TestFunc func, const std::string& name) {
        tests.emplace(name, std::move(func));
        return false;
    }

    // Tests
    #define STEST(NAME) \
        void NAME(); \
        namespace Stealth::Test { \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest(NAME, #NAME); \
        } \
        void NAME()

    // Asserts and Expects
    #define EXPECT_TRUE(CONDITION, MESSAGE) if (not (CONDITION)) log(#MESSAGE)
    #define ASSERT_TRUE(CONDITION, MESSAGE) if (not (CONDITION)) log(#MESSAGE); return;
} /* Stealth::Test */
