#include <functional>
#include <iostream>

namespace Stealth::Test {
    // Defining tests
    using TestFunc = std::function<void(bool&)>;
    bool addTest(TestFunc func, const std::string& name);

    // Tests
    #define STEST(NAME) \
        void NAME(bool& __stest_passed); \
        namespace Stealth::Test { \
            [[maybe_unused]] const bool _ST_Func_Result_##NAME##_##discard = Stealth::Test::addTest(NAME, #NAME); \
        } \
        void NAME(bool& __stest_passed)

    // Checks
    #define LOG_MISMATCH(EXPECTED, VALUE) std::cerr << "\033[1;31m[     ERROR]\n\tAt " << __FILE__ << ":" << __LINE__ << ", " << "Value of: " << #VALUE << "\n\t  Actual: " << (VALUE) << "\n\tExpected: " << (EXPECTED) << "\033[0m" << std::endl;

    #define EXPECT_EQ(EXPECTED, VALUE) if (EXPECTED != VALUE) { LOG_MISMATCH(EXPECTED, VALUE); __stest_passed = false; }
    #define EXPECT_TRUE(CONDITION) EXPECT_EQ(true, CONDITION)
    #define EXPECT_FALSE(CONDITION) EXPECT_EQ(false, CONDITION)

    // Running tests
    enum class Status : int {
        OK = 0,
        FAIL = 1,
    };

    Status runTests(int argc, const char* argv[], const std::string& filename);

    #define RUN_STESTS(argc, argv) Stealth::Test::runTests(argc, argv, __FILE__)
} // Stealth::Test
