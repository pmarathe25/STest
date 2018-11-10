#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Stealth::Test {
    class IndentedError {
        public:
            template <typename T>
            std::ostream& operator<<(T&& val) {
                return std::cerr << "\t" << val;
            }
    };

    #define LOG_MISMATCH(EXPECTED, VALUE) std::cerr << "[     ERROR]\n" << __FILE__ << ":" << __LINE__ << " " << "Value of: " << #VALUE << "\n  Actual: " << (VALUE) << "\nExpected: " << (EXPECTED) << std::endl;

    // Keep track of all tests.
    using TestFunc = std::function<void(bool&)>;
    std::map<const std::string, TestFunc> tests{};

    // Must have a return type so that we can invoke this in the global scope.
    // The side-effect of this function is to register the test.
    inline bool addTest(TestFunc func, const std::string& name) {
        tests.emplace(name, std::move(func));
        return false;
    }

    // Tests
    #define STEST(NAME) \
        void NAME(bool& __stest_passed); \
        namespace Stealth::Test { \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest(NAME, #NAME); \
        } \
        void NAME(bool& __stest_passed)

    // Asserts and Expects
    #define EXPECT_EQ(EXPECTED, VALUE) if (EXPECTED != VALUE) { LOG_MISMATCH(EXPECTED, VALUE); __stest_passed = false; } std::cerr
    #define ASSERT_EQ(EXPECTED, VALUE) if (EXPECTED != VALUE) { LOG_MISMATCH(EXPECTED, VALUE); __stest_passed = false; return; }

    #define EXPECT_TRUE(CONDITION) EXPECT_EQ(true, CONDITION)
    #define ASSERT_TRUE(CONDITION) ASSERT_EQ(true, CONDITION)

    #define EXPECT_FALSE(CONDITION) EXPECT_EQ(false, CONDITION)
    #define ASSERT_FALSE(CONDITION) ASSERT_EQ(false, CONDITION)
} /* Stealth::Test */
